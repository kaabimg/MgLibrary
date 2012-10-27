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
#ifndef MGAPPLICATIONMONITOR_H_
#define MGAPPLICATIONMONITOR_H_

//MG_INCLUDE_INFO:MgApplicationMonitor

#include <QObject>
#include <QSet>
#include <QHash>
#include <QString>
#include <QEvent>
#include <MgCore/MgMessagesEmitter>
class MgScriptEngine;

class MgApplicationMonitor : public QObject, public MgMessagesEmitter
{
	Q_OBJECT
public:
	MgApplicationMonitor();
	virtual ~MgApplicationMonitor();
	void setRootObject(QObject *);
	MgScriptEngine * scriptEngine()const;

public Q_SLOTS:
	void registerObject(QObject*);

Q_SIGNALS:
	void childAdded(QObject*,QObject*);
	void childRemoved(QObject*,QObject*);
	void registerRequest(QObject *);


	void eventMessage(const QString&,const QString&,const QString&);


protected:
	bool eventFilter(QObject*,QEvent*);
	void monitorEvent(QObject*,QEvent*);
	void clear();
	void registerWrapper();
	void initEventsStrings();

private:
	QObject * m_root;
	QString m_objectNameSeparator;
	MgScriptEngine * m_scriptEngine;
	QSet<QObject*> m_registedObjects;
	QHash<QEvent::Type,QString> m_eventsToString;
};

#endif /* MGAPPLICATIONMONITOR_H_ */
