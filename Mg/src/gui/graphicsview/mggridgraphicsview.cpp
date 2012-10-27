/*************************************************************************
** 
** Copyright 2011 Mohamed-Ghaïth KAABI (mohamedghaith.kaabi@gmail.com)
** This file is part of MgLibrary.
** 
** MgLibrary is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** any later version.
** 
** MgLibrary is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with MgLibrary.  If not, see <http://www.gnu.org/licenses/>.
** 
****************************************************************************/
#include "mggridgraphicsview.h"

#include "mgrectgraphicsobject.h"
#include "mgviewgridlayout.h"

#include <math.h>

#include <QGraphicsWidget>
#include <QGraphicsDropShadowEffect>
#include <QStateMachine>
#include <QSignalTransition>
#include <QListWidget>
#include <QLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>

/**************************************************************************************************
 **************************************************************************************************/
MgGridGraphicsView::MgGridGraphicsView(QWidget *parent)
    : QGraphicsView(parent),
    m_currentZoomLevel(1.0)
{
    setOptimizationFlag(QGraphicsView::DontSavePainterState);
    setCacheMode(QGraphicsView::CacheBackground);
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setScene(new QGraphicsScene);


    m_itemsContainer = new QGraphicsWidget;
    m_itemsContainer->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    m_layout = new MgViewGridLayout(Qt::Vertical, 10);

    m_layout->setScene(scene());
    m_layout->setHorizontalSpacing(ITEM_WIDTH + 15);
    m_layout->setVerticalSpacing(ITEM_HEIGHT + 15);
    m_layout->setContentsMargins(20, 20, 20, 20);
    m_itemsContainer->setLayout(m_layout);
    scene()->addItem(m_itemsContainer);

}

/**************************************************************************************************
 **************************************************************************************************/
MgGridGraphicsView::~MgGridGraphicsView()
{
	clear();
}
//////////////////////////////////////////////////////////////////////////////////////////

void MgGridGraphicsView::addItem(MgRectGraphicsObject * obj)
{
	m_layout->add(obj);
	connect(obj,SIGNAL(selected(bool,bool)),this,SLOT(updateSelection(bool,bool)));

}
void MgGridGraphicsView::relayout()
{
	m_layout->relayout();
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->delta() > 0)
            zoomIn();
        else
            zoomOut();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    updateLayout();
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::updateLayout()
{
    QSizeF effectiveSize = mapToScene(rect()).boundingRect().size();

    int length;
    if (m_layout->flowDirection() == Qt::Vertical)
        length = (effectiveSize.width() - 40) / m_layout->horizontalSpacing();
    else
        length = (effectiveSize.height() - 40) / m_layout->verticalSpacing();

    m_layout->setLayoutLength(qMax(1,length));
}

void  MgGridGraphicsView::clear()
{
	m_selectedItems.clear();
	m_layout->clearItems();
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::zoomIn()
{
    setZoom(m_currentZoomLevel * ZOOM_IN_FACTOR);
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::zoomOut()
{
    setZoom(m_currentZoomLevel * ZOOM_OUT_FACTOR);
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::resetZoom()
{
    setZoom(1.0);
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::zoomFit()
{
    qreal ratio = qreal(width()) / qreal(height());
    int rows = sqrt(m_layout->count() / ratio) + 1;

    qreal fitFactor = height() / m_layout->verticalSpacing() / rows;
    qreal margin = 40 * fitFactor;
    fitFactor = (height() - margin) / m_layout->verticalSpacing() / rows;

    fitFactor = qMax(qMin(fitFactor, ZOOM_MAX), ZOOM_MIN);
    setZoom(fitFactor);
}

/**************************************************************************************************
 **************************************************************************************************/
void MgGridGraphicsView::setZoom(qreal z)
{
    if (m_currentZoomLevel == z || z > ZOOM_MAX || z < ZOOM_MIN)
        return;

    m_currentZoomLevel = z;
    setTransform(QTransform().scale(m_currentZoomLevel, m_currentZoomLevel));
    updateLayout();
    emit zoomLevelChanged(m_currentZoomLevel);
}


void MgGridGraphicsView::updateSelection(bool isSelected,bool multi)
{
	if(isSelected)
	{
		if(!multi)
		{
			foreach(MgRectGraphicsObject * obj,m_selectedItems)
			{
				obj->setItemSelected(false);
				obj->update();
			}
			m_selectedItems.clear();
			m_selectedItems.insert(qobject_cast<MgRectGraphicsObject*>(sender()));;
		}
		m_selectedItems.insert(qobject_cast<MgRectGraphicsObject*>(sender()));
	}
	else
	{
		if(multi)
			m_selectedItems.remove(qobject_cast<MgRectGraphicsObject*>(sender()));
		else
		{
			foreach(MgRectGraphicsObject * obj,m_selectedItems)
			{
				obj->setItemSelected(false);
				obj->update();
			}
			m_selectedItems.clear();
		}
	}
}



