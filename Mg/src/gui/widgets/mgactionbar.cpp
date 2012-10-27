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
#include "mgactionbar.h"

#include  <QtGui/QPaintEvent>
#include  <QtGui/QAction>
#include  <QtGui/QVBoxLayout>
#include <QtGui/QPainter>

#include "mgutils.h"
#include "mgtoolbutton.h"


MgActionBar::MgActionBar(Qt::Orientations orientation,QWidget *parent)
    : QWidget(parent),m_orientation(orientation)
{

	if(orientation == Qt::Vertical)
		m_actionsLayout = new QVBoxLayout;
	else
		m_actionsLayout = new QHBoxLayout;

	m_actionsLayout->setMargin(0);
	m_actionsLayout->setSpacing(0);
    setLayout(m_actionsLayout);


}


void MgActionBar::insertAction(int index, QAction *action)
{
	if(action == NULL)
		return;
	if(action->text().isEmpty())
		return;

    MgToolButton *toolButton = new MgToolButton(m_orientation,this);

    toolButton->setDefaultAction(action);
    connect(action, SIGNAL(changed()), toolButton, SLOT(actionChanged()));
    m_toolButtons.insert(action->text(),toolButton);

    if(m_orientation==Qt::Vertical)
    {
    	toolButton->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    	m_actionsLayout->insertWidget(index, toolButton,Qt::AlignTop);
    }
    else
    {
    	toolButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    	m_actionsLayout->insertWidget(index, toolButton,Qt::AlignRight);
    }
}

void MgActionBar::addAction(QAction *action)
{
	if(action == NULL)
		return;
	if(action->text().isEmpty())
		return;
    MgToolButton *toolButton = new MgToolButton(m_orientation,this);
    toolButton->setDefaultAction(action);
    connect(action, SIGNAL(changed()), toolButton, SLOT(actionChanged()));

    m_toolButtons.insert(action->text(),toolButton);
    if(m_orientation==Qt::Vertical)
    {
    	toolButton->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    	m_actionsLayout->addWidget(toolButton,Qt::AlignTop);
    }
    else
    {
    	toolButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    	m_actionsLayout->addWidget( toolButton,Qt::AlignRight);
    }
}

void  MgActionBar::removeAction(const QString & text)
{
	m_actionsLayout->removeWidget(m_toolButtons.take(text));
}

QSize MgActionBar::minimumSizeHint() const
{
    return sizeHint();
}


void MgActionBar::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
	Q_UNUSED(event);
//    QColor light = MgGuiHelpers::sidebarHighlight();
//    QColor dark = MgGuiHelpers::sidebarShadow;
//    painter.setPen(dark);
//    painter.drawLine(rect().topLeft(), rect().topRight());
//    painter.setPen(light);
//    painter.drawLine(rect().topLeft() + QPoint(1,1), rect().topRight() + QPoint(0,1));



    QPainter painter(this);

    QRect rect = style()->visualRect(layoutDirection(), geometry(), this->rect());

    if(m_orientation == Qt::Vertical)
    	MgGuiHelpers::verticalGradient(&painter, rect, rect);
    else
    	MgGuiHelpers::horizontalGradient(&painter, rect, rect);


    painter.setPen(MgGuiHelpers::borderColor());
    painter.drawLine(rect.topRight(), rect.bottomRight());

    QColor light = MgGuiHelpers::sidebarHighlight();

    painter.setPen(light);
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}


