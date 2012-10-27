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
#ifndef MGTASK_H_
#define MGTASK_H_

//MG_INCLUDE_INFO:MgTask

#include <QRunnable>
#include <QObject>
#include <QMutex>
#include "../messages/mgmessagesemitter.h"

class MgTask : public QObject, public QRunnable, public MgMessagesEmitter
{
	Q_OBJECT

public:
	MgTask(QObject * parent =0):QObject(parent),m_isStopped(false),m_isStoppable(false){}
	virtual ~MgTask(){}


	Q_SLOT void stop();
	bool isStopped();
	bool supportsStop(){return m_isStoppable;}
	QString taskName()const
	{
		return m_taskName;
	}

Q_SIGNALS:
	void started();
	void finished();
	void progress(int);
protected:
	virtual void task()=0;
	void run();
	void setStoppable(bool s){m_isStoppable = s;}
	void setTaskName(const QString & name)
	{
		m_taskName = name;
	}

private:
	QMutex m_accesMutex;
	bool m_isStopped,m_isStoppable;
	QString m_taskName;
};

#endif /* MGTASK_H_ */
