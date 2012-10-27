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
#include "mgdynamicwidget.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QHash>
#include <QDebug>
#include "mgsubwidget.h"


typedef QPair<QWidget*,QWidget*> TemporaryWidget;


struct MgDynamicWidgetPrivate
{
	QSplitter * splitter;
	QVBoxLayout * layout;
	QHash<QString,TemporaryWidget> widgetsTable;
	QHash<QWidget*,QString> widgetsNames;
	QHash<MgSubWidget*,QString> subWidgetsNames;
	QHash<QWidget*,QWidget*> autoWidgetsTable;//for task view widgets

};


MgDynamicWidget::MgDynamicWidget(QWidget * parent):QWidget(parent),d_ptr(new MgDynamicWidgetPrivate)
{
	d_ptr->splitter = new QSplitter(this);
	d_ptr->splitter->setOrientation(Qt::Vertical);
	d_ptr->layout = new QVBoxLayout;

	d_ptr->layout->setContentsMargins(0,0,0,0);
	d_ptr->layout->setMargin(0);
	d_ptr->layout->setSpacing(0);
	d_ptr->layout->addWidget(d_ptr->splitter);

	setLayout(d_ptr->layout);


	d_ptr->splitter->setStyleSheet(
			"QSplitter::handle:horizontal {width: 1px;}"
			"QSplitter::handle:vertical {height: 1px; }"
			);


}

MgDynamicWidget::~MgDynamicWidget()
{

	foreach(TemporaryWidget ww,d_ptr->widgetsTable)
	{
		if(!ww.second->parent())
			delete ww.second;
	}

	delete d_ptr;
}

void MgDynamicWidget::setCentralWidget(QWidget * w)
{
	d_ptr->splitter->addWidget(w);
}

void MgDynamicWidget::registerTemporaryWidget(const QString & name,QWidget* widget,const char * closeSignal)
{
	if(!d_ptr->widgetsTable.contains(name))
	{
		MgSubWidget * subWidget  = new MgSubWidget(widget);
		d_ptr->widgetsTable.insert(name,TemporaryWidget(widget,subWidget));
		d_ptr->widgetsNames.insert(widget,name);
		d_ptr->subWidgetsNames.insert(subWidget,name);
		connect(subWidget,SIGNAL(closeRequest()),this,SLOT(onSubWidgetCloseRequest()));

		if(closeSignal != NULL)
		{
			connect(widget,closeSignal,this,SLOT(closeRequest()));
		}
//		subWidget->setVisible(false);

	}
}

void MgDynamicWidget::registerTemporaryWidget(const QString & name,QWidget*widget,const char * showSignal,const char * closeSignal)
{

	if(!d_ptr->widgetsTable.contains(name))
	{
		MgSubWidget * subWidget  = new MgSubWidget(widget);
		d_ptr->widgetsTable.insert(name,TemporaryWidget(widget,subWidget));
		d_ptr->widgetsNames.insert(widget,name);
		d_ptr->autoWidgetsTable.insert(widget,subWidget);
		d_ptr->subWidgetsNames.insert(subWidget,name);
		connect(subWidget,SIGNAL(closeRequest()),this,SLOT(onSubWidgetCloseRequest()));

		connect(widget,showSignal,this,SLOT(autoShowRequest()));
		if(closeSignal != NULL)
		{
			connect(widget,closeSignal,this,SLOT(closeRequest()));
		}
		if(closeSignal)
			connect(widget,closeSignal,this,SLOT(autoCloseRequest()));
//		subWidget->setVisible(false);

	}
}

void MgDynamicWidget::autoShowRequest()
{
	d_ptr->splitter->addWidget(d_ptr->autoWidgetsTable.value(
			qobject_cast<QWidget*>(sender())));
}
void MgDynamicWidget::autoCloseRequest()
{
	d_ptr->autoWidgetsTable.value(
				qobject_cast<QWidget*>(sender()))->setParent(NULL);

	d_ptr->autoWidgetsTable.value(
				qobject_cast<QWidget*>(sender()))->deleteLater();
}



void MgDynamicWidget::onCloseRequest()
{
	QString name = d_ptr->widgetsNames.value(qobject_cast<QWidget*>(sender()));
	hideTemporaryWidget(name);
}

void MgDynamicWidget::onSubWidgetCloseRequest()
{
	QString name = d_ptr->subWidgetsNames.value(qobject_cast<MgSubWidget*>(sender()));
	hideTemporaryWidget(name);
}

void MgDynamicWidget::showTemporaryWidget(const QString & name)
{
	if(d_ptr->widgetsTable.contains(name))
	{
		if(d_ptr->splitter->indexOf(d_ptr->widgetsTable[name].second)==-1)
		{
			d_ptr->widgetsTable[name].second->setVisible(true);
			d_ptr->splitter->addWidget(d_ptr->widgetsTable[name].second);
			Q_EMIT widgetShown(name);
		}
	}
}
void MgDynamicWidget::hideTemporaryWidget(const QString & name)
{
	if(d_ptr->widgetsTable.contains(name))
	{
		if(d_ptr->splitter->indexOf(d_ptr->widgetsTable[name].second)!=-1)
		{
			d_ptr->widgetsTable[name].second->setParent(NULL);
			Q_EMIT widgetHidden(name);
		}
	}
}



