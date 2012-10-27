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
#include "mgmainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <MgCore/MgGlobal>

#include <MgCore/MgTask>
#include <MgCore/MgThread>

#include "../widgets/mgtabwidget.h"
#include "../widgets/mgoutputpanebar.h"
#include "../task/mgtaskviewer.h"

struct MgMainWindowPrivate
{
	QMap<QString,QMenu*> rootMenus;
	QMap<QString,QMenu*> subMenus;
	QMenuBar * menuBar;
	QToolBar * toolBar;
	MgOutputPaneBar * outputPaneBar;
	MgTabWidget *tabWidget;
};


MgMainWindow::MgMainWindow(QWidget *parent)
    : QMainWindow(parent),d_ptr(new MgMainWindowPrivate)
{
//	d_ptr->menuBar  =  new QMenuBar(0);// mac os compatibility
//	setMenuBar(d_ptr->menuBar);
//	d_ptr->toolBar  =  new QToolBar(this);
//	addToolBar(Qt::TopToolBarArea,d_ptr->toolBar);


	QWidget * centralWidget = new QWidget(this);
	QVBoxLayout * layout = new QVBoxLayout;


	layout->setMargin(0);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);

	d_ptr->tabWidget = new MgTabWidget(Qt::Vertical,centralWidget);
	d_ptr->outputPaneBar = new MgOutputPaneBar(centralWidget);


	layout->addWidget(d_ptr->tabWidget);
	layout->addWidget(d_ptr->outputPaneBar);

	centralWidget->setLayout(layout);

	connect(d_ptr->outputPaneBar,SIGNAL(showRequest(QString)),
			d_ptr->tabWidget,SLOT(showTemporaryWidget(const QString &)));
	connect(d_ptr->outputPaneBar,SIGNAL(hideRequest(QString)),
			d_ptr->tabWidget,SLOT(hideTemporaryWidget(const QString &)));
	connect(d_ptr->tabWidget,SIGNAL(temporaryWidgetHidden(const QString&)),
			d_ptr->outputPaneBar,SLOT(untoggleButton(const QString&)));



	setCentralWidget(centralWidget);
}
MgMainWindow::~MgMainWindow()
{
//	d_ptr->menuBar->deleteLater();
	delete d_ptr;
}

//void MgMainWindow::addRootMenu(const QString menuName)
//{
//	if(!d_ptr->rootMenus.contains(menuName))
//		d_ptr->rootMenus.insert(menuName,d_ptr->menuBar->addMenu(menuName));
//}
//
//void MgMainWindow::addSubMenu(const QString menuName,const QString subMenuName)
//{
//	QMenu * parentMenu  =  d_ptr->rootMenus[menuName];
//	if(parentMenu == NULL)
//		parentMenu  =  d_ptr->subMenus[menuName];
//	if(parentMenu == NULL)
//		return ;
//	d_ptr->subMenus.insert(subMenuName,parentMenu->addMenu(subMenuName));
//
//}
//
//
//void MgMainWindow::addMenuAction(const QString parentMenuName, QAction* action
//		,QObject * receiver,const char * slotName)
//{
//	QMenu * parentMenu  =  d_ptr->rootMenus[parentMenuName];
//	if(parentMenu == NULL)
//		parentMenu  =  d_ptr->subMenus[parentMenuName];
//	if(parentMenu == NULL)
//		return ;
//
//
//	parentMenu->addAction(action);
//	connect(action,SIGNAL(triggered()),receiver,slotName);
//}
//void MgMainWindow::addMenuSeparator(const QString menuName)
//{
//	QMenu * parentMenu  =  d_ptr->rootMenus[menuName];
//	if(parentMenu == NULL)
//		parentMenu  =  d_ptr->subMenus[menuName];
//	if(parentMenu == NULL)
//		return ;
//	parentMenu->addSeparator();
//}
//
//
//
//void MgMainWindow::addToolBarAction(QAction* action,QObject * receiver,const char * slotName)
//{
//	d_ptr->toolBar->addAction(action);
//	connect(action,SIGNAL(triggered()),receiver,slotName);
//}
//void MgMainWindow::addToolBarSeparator()
//{
//	d_ptr->toolBar->addSeparator();
//}

void MgMainWindow::addOutputPane(const QString & name,QWidget * widget,const char * closeSignal)
{
	d_ptr->outputPaneBar->addPane(name);
	d_ptr->tabWidget->registerTemporaryWidget(name,widget,closeSignal);
}

void MgMainWindow::addOutputPaneWidget(QWidget * widget)
{
	d_ptr->outputPaneBar->addWidget(widget);
}

int MgMainWindow::addSidebarWidget(const QString & name,const QIcon & icon,QWidget *w,bool enabled)
{
	d_ptr->tabWidget->appendTab(w,icon,name);
	setSidebarWidgetEnabled(d_ptr->tabWidget->tabCount()-1,enabled);
	return d_ptr->tabWidget->tabCount()-1;
}

void MgMainWindow::setSidebarWidgetEnabled(int i,bool enable)
{
	d_ptr->tabWidget->setTabEnabled(i,enable);
}

void MgMainWindow::setCurrentWidget(int index)
{
	d_ptr->tabWidget->setCurrentIndex(index);
}
void MgMainWindow::addTaskObserver(MgTask* task)
{
	MgTaskViewer * taskViewer = new MgTaskViewer(task);
	d_ptr->tabWidget->registerTemporaryWidget(task->taskName(),taskViewer,SIGNAL(taskStarted()),0);
}
void MgMainWindow::addTaskObserver(MgThread* task)
{
	MgTaskViewer * taskViewer = new MgTaskViewer(task);
	d_ptr->tabWidget->registerTemporaryWidget(task->taskName(),taskViewer,SIGNAL(taskStarted()),0);
}
void MgMainWindow::unobserveTask(MgTask* /* task*/)
{
	//TODO
}
void MgMainWindow::unobserveTask(MgThread* /* task*/)
{
	//TODO
}
