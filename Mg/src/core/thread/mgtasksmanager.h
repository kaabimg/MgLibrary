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
#ifndef MGTASKSMANAGER_H_
#define MGTASKSMANAGER_H_

#include <QObject>

class MgTask;
class QThreadPool;


#define MG_START_TASK(task) MgTasksManager::instance()->startTask(task)


class MgTasksManager : public QObject
{
	Q_OBJECT
public:
	virtual ~MgTasksManager();
	static MgTasksManager * instance();

public slots:
	void startTask(MgTask *);

private:
	MgTasksManager(QObject * parent=0);
	static MgTasksManager *  m_globalInstance;
	QThreadPool * m_threadPool;
};

#endif /* MGTASKSMANAGER_H_ */
