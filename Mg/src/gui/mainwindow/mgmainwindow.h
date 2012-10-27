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
#ifndef MGMAINWINDOW_H
#define MGMAINWINDOW_H

//MG_INCLUDE_INFO:MgMainWindow

#include <QtGui/QMainWindow>
#include <QIcon>
#include <QMap>
#include <MgCore/MgGlobal>

class QMenu;
class QMenuBar;
class QToolBar;
class QAction;
class MgTask;
class MgThread;

MG_USE_PRIVATE_CLASS(MgMainWindow)

class MgMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MgMainWindow(QWidget *parent = 0);
    ~MgMainWindow();


public Q_SLOTS:

	void addOutputPane(const QString & name,QWidget * widget,const char * closeSignal =0);
	void addOutputPaneWidget(QWidget * widget);
	int addSidebarWidget(const QString &,const QIcon & ,QWidget *,bool enabled=true);
	void setSidebarWidgetEnabled(int ,bool);
	void setCurrentWidget(int);



	void addTaskObserver(MgTask*);
	void addTaskObserver(MgThread*);

	void unobserveTask(MgTask*);
	void unobserveTask(MgThread*);

private:
	Q_DISABLE_COPY(MgMainWindow)
	MG_PRIVATE_CLASS(MgMainWindow)
};


#endif // MGMAINWINDOW_H
