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
#ifndef MGTASKVIEWER_H_
#define MGTASKVIEWER_H_

//MG_INCLUDE_INFO:MgTaskViewer

#include <QWidget>
#include <MgGlobal>

class MgTask;
class MgThread;

MG_USE_PRIVATE_CLASS(MgTaskViewer)


class MgTaskViewer : public QWidget
{
	Q_OBJECT
public:
	MgTaskViewer(MgTask * task,QWidget * parent=0);
	MgTaskViewer(MgThread * task,QWidget * parent=0);
	virtual ~MgTaskViewer();


Q_SIGNALS:
	void taskStarted();
	void taskFinished();

private Q_SLOTS:


	void onTaskStarted();
	void onTaskFinished();

private:
	MG_PRIVATE_CLASS(MgTaskViewer)
};

#endif /* MGTASKVIEWER_H_ */
