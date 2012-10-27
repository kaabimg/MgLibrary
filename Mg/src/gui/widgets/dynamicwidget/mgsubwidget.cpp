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
#include "mgsubwidget.h"

#include <QVBoxLayout>
#include <QToolBar>
#include <QIcon>
#include <QStyle>

struct MgSubWidgetPrivate
{
	QVBoxLayout * layout;
	QToolBar * toolBar;
	QWidget * widget;
};

MgSubWidget::MgSubWidget(QWidget * widget, QWidget*parent) :
		QWidget(parent),d_ptr(new MgSubWidgetPrivate)
{
	d_ptr->layout = new QVBoxLayout;
	d_ptr->toolBar = new QToolBar(this);
	d_ptr->toolBar->setFixedHeight(25);
	d_ptr->toolBar->setStyleSheet("background-color: qlineargradient"
			"(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(75,75,75), stop:1 rgb(55,55,55))");

	widget->setParent(this);
	d_ptr->widget = widget;

	d_ptr->layout->setMargin(0);
	d_ptr->layout->setContentsMargins(0,0,0,0);
	d_ptr->layout->setSpacing(0);

	d_ptr->layout->addWidget(d_ptr->toolBar);
	d_ptr->layout->addWidget(widget);

	setLayout(d_ptr->layout);


	QWidget* spacer = new QWidget(this);
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	d_ptr->toolBar->addWidget(spacer);

	d_ptr->toolBar->addAction(style()->standardIcon(QStyle::SP_DialogCloseButton),"close",this,SLOT(onClose()));

	setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	setBaseSize(800,300);


}

MgSubWidget::~MgSubWidget()
{
	delete d_ptr;
}

QToolBar * MgSubWidget::toolBar()
{
	return d_ptr->toolBar;
}


QWidget * MgSubWidget::contentWidget()const
{
	return d_ptr->widget;
}

void MgSubWidget::onClose()
{
	Q_EMIT closeRequest();
}


