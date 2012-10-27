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
#include "mgfoldingextraarea.h"

#include "mglinesnumbersextraarea.h"
#include "mgbasetextedit.h"

#include <QPainter>
#include <QCursor>
#include <QTextBlock>
#include <QPixmap>

MgFoldingExtraArea::MgFoldingExtraArea(MgBaseTextEdit *edit)
: QWidget(edit),m_editor(edit),m_lastActiveBlock(-1) , m_isHighlighing(false)
{
	setMouseTracking(true);
	m_currentArea = NULL;

}

QSize MgFoldingExtraArea::sizeHint() const
{
	return QSize(m_editor->foldingAreaWidth(), 0);
}

void MgFoldingExtraArea::paintEvent(QPaintEvent * )
{
	QPainter painter(this);
//	painter.save();
	painter.fillRect(rect(),Qt::lightGray);

	m_drawnMarkers.clear();
	for (int i = 0; i < m_topFoldingAreas.size(); ++i)
		drawFoldingAreaMarker(&painter,m_topFoldingAreas[i]);

	if(m_currentArea)
		drawFoldingAreaLimiters(&painter,*m_currentArea);

}
void MgFoldingExtraArea::mousePressEvent(QMouseEvent *)
{
	if(!m_currentArea)
		return;
	m_currentArea->isExpanded = !m_currentArea->isExpanded;
	Q_EMIT foldingRequest(m_currentArea->begin,m_currentArea->end-1,m_currentArea->isExpanded);
}
void MgFoldingExtraArea::mouseMoveEvent(QMouseEvent * e)
{
	if(setCurrentFoldingBlock(e->pos()))
	{
		Q_EMIT highlightBlockRequest(m_currentArea->begin-1,m_currentArea->end-1);
		m_isHighlighing = true;
	}
	else
	{
		if(m_isHighlighing)
		{
			Q_EMIT unHighlightRequest();
			m_isHighlighing = false;
		}
	}
	update();
}

void MgFoldingExtraArea::setCurrentFoldingArea(int block)
{
	if(block == m_lastActiveBlock)
		return;
	m_lastActiveBlock = block;
	FoldingArea * old = m_currentArea;
	m_currentArea = lookAreaContaining(block+1);

	if(old != m_currentArea)//update is needed even if m_currentArea is null
		 update();
}


bool MgFoldingExtraArea::setCurrentFoldingBlock(const QPoint& pos)
{
	QTextBlock block = m_editor->cursorForPosition(QPoint(0,pos.y())).block();
	if(!block.isValid())
		return false;
	m_currentArea = lookAreaContaining(block.blockNumber()+1);

	if(m_currentArea)
		return true;
	else
		return false;
}


void MgFoldingExtraArea::leaveEvent(QEvent *)
{
	Q_EMIT unHighlightRequest();
	m_isHighlighing = false;
	m_currentArea =  NULL;
	update();
	int tmpBlockNumber = m_lastActiveBlock;
	m_lastActiveBlock = -1;//to foce update
	setCurrentFoldingArea(tmpBlockNumber);

}

void MgFoldingExtraArea::clearFoldingAreas()
{
	m_topFoldingAreas.clear();
}
void MgFoldingExtraArea::addFoldingArea(int begin,int end)
{
	FoldingArea area(begin,end);
	for (int i = 0; i < m_topFoldingAreas.size(); ++i)
		if(m_topFoldingAreas[i].contains(area))
		{
			m_topFoldingAreas[i].addSubFoldingArea(area);
			return;
		}
	m_topFoldingAreas<<area;
}

MgFoldingExtraArea::FoldingArea * MgFoldingExtraArea::lookAreaContaining(int line)
{
	FoldingArea * area(NULL);
	for (int i = 0; i < m_topFoldingAreas.size(); ++i)
		if(m_topFoldingAreas[i].contains(line))
		{
			area = &m_topFoldingAreas[i];
			continue;
		}

	if(area)
		return area->findLine(line);

	return area;
}

QRect MgFoldingExtraArea::rectFromLine(int line)const
{
	QTextBlock block = m_editor->document()->findBlockByNumber(line-1);
	if(!block.isValid())
		return QRect();

	qreal top = m_editor->blockBoundingGeometry(block).translated(m_editor->contentOffset()).top();
	qreal bottom = m_editor->blockBoundingGeometry(block).translated(m_editor->contentOffset()).bottom();

	int w(width());

	QPoint topLeft(0,top);
	return QRect(topLeft,QSize(w,bottom-top));
}


void MgFoldingExtraArea::drawFoldingMarker(QPainter *painter,const QRect &r,bool expanded) const
{
	QRect rect(r);
	static const  QColor color(40,40,40,100);

	int dw = rect.width()/6;
	int dh = rect.height()/6;

	QPolygonF points;
	if (expanded)
	{
		// down arrow
		points<<QPoint(rect.topLeft().x()+dw,rect.topLeft().y()+dh);
		points<<QPoint(rect.topRight().x()-dw,rect.topLeft().y()+dh);
		points<<QPoint(rect.bottomLeft().x()+rect.width()/2,rect.bottomLeft().y()-dh);
	}
	else
	{
		// right arrow
		points<<QPoint(rect.topLeft().x()+dw,rect.topLeft().y()+dh);
		points<<QPoint(rect.bottomLeft().x()+dw,rect.bottomLeft().y()-dh);
		points<<QPoint(rect.topRight().x()-dw,rect.topLeft().y()+(rect.height()/2));
	}

	QPainterPath painterPath;
	painterPath.addPolygon(points);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->fillPath(painterPath,color);

}
void MgFoldingExtraArea::drawFoldingAreaMarker(QPainter * painter,const FoldingArea & area)
{
	QRect r = rectFromLine(area.begin);
	if(r.isNull())
		return;
	if(!m_drawnMarkers.contains(area.begin))
	{
		m_drawnMarkers.insert(area.begin);
		drawFoldingMarker(painter,r,area.isExpanded);
	}

	if(!area.isExpanded)
		return;
	for (int i = 0; i < area.subFoldingAreas.size(); ++i)
		drawFoldingAreaMarker(painter,area.subFoldingAreas[i]);
}



void MgFoldingExtraArea::drawFoldingAreaLimiters(QPainter * painter,const FoldingArea & area)
{
	QRect top(rectFromLine(area.begin));
	QRect bottom(rectFromLine(area.end));

	if(top.isNull()||bottom.isNull())
		return;


	QRect r;
	if(area.isExpanded)
	{
		r.setTopLeft(top.topLeft());
		r.setBottomRight(bottom.bottomRight());
	}
	else
		r = top;
	r.adjust(1,0,-2,0);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);

    QColor c (200,40,0,75);

    QLinearGradient grad(r.topLeft(), r.topRight());
    grad.setColorAt(0, c.lighter(110));
    grad.setColorAt(1, c.lighter(130));
    painter->fillRect(r, grad);

    QColor contourColor(40,40,40);
    QPen pen;
    pen.setColor(contourColor);
    pen.setWidth(1);
    painter->setPen(pen);

    painter->drawLine(r.topLeft() + QPoint(1, 0), r.topRight() -  QPoint(1, 0));
    painter->drawLine(r.bottomLeft() + QPoint(1, 0), r.bottomRight() -  QPoint(1, 0));

    painter->drawLine(r.topRight() + QPoint(0, 1 ), r.bottomRight() - QPoint(0, 1));
    painter->drawLine(r.topLeft() + QPoint(0, 1 ), r.bottomLeft() - QPoint(0, 1));

    painter->restore();
}
