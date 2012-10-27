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
#include "mgnavigationbar.h"
#include <QAction>
#include <QStyle>
#include <QVBoxLayout>

MgNavigationBar::MgNavigationBar(NavigationType type,QWidget * parent)
	: QToolBar(parent)
{
	QWidget * spacer = new QWidget(this);
	spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	if(type == Forward)
	{
		addWidget(spacer);
		addAction(style()->standardPixmap(QStyle::SP_ArrowForward),"",this,SIGNAL(forwardRequest()));
	}
	else if(type == Backward)
	{
		addAction(style()->standardPixmap(QStyle::SP_ArrowBack),"",this,SIGNAL(backwardRequest()));
		addWidget(spacer);
	}
	else
	{
		addAction(style()->standardPixmap(QStyle::SP_ArrowBack),"",this,SIGNAL(backwardRequest()));
		addAction(style()->standardPixmap(QStyle::SP_ArrowForward),"",this,SIGNAL(forwardRequest()));
		addWidget(spacer);
	}

	setMaximumHeight(50);
	setStyleSheet(" background-color: rgb(40,40,40);");
}

MgNavigationBar::~MgNavigationBar(){}


MgWidgetWithNavigationBar::MgWidgetWithNavigationBar(
		QWidget * emW,
		MgNavigationBar::NavigationType type,
		QWidget * parent): QWidget(parent)
{
	QVBoxLayout * layout = new QVBoxLayout;
	layout->setMargin(0);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	setLayout(layout);
	m_navigationBar = new MgNavigationBar(type,this);
	emW->setParent(this);
	layout->addWidget(m_navigationBar);
	layout->addWidget(emW);
}
MgNavigationBar * MgWidgetWithNavigationBar::navigationBar()const
{
	return m_navigationBar;
}
