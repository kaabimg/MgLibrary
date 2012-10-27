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
#include "mgpropertywatcher.h"
#include <QMetaObject>
#include <QMetaProperty>



void MgPropertyWatcher::init(QObject * obj,const QString & propertyName)
{
	m_propertyName = propertyName;

	const QMetaObject * metaObject = obj->metaObject();
	QMetaProperty property;
	bool found =false;
	for (int i = 0; i < metaObject->propertyCount(); ++i)
	{
		if(metaObject->property(i).name() == propertyName)
		{
			property = metaObject->property(i);
			found = true;
		}
	}
	if(!found)
		return ;
	const char * signalDef =  (QString("2")+property.notifySignal().signature())
			.toLatin1().constData();
	connect(obj,qFlagLocation(signalDef),this,SLOT(onPropertyChanged()));
}

void MgPropertyWatcher::onPropertyChanged()
{
	Q_EMIT propertyChanged(m_propertyName);
}

bool MgPropertyWatcher::hasNotifySignal(QObject * obj,const QString & propertyName)
{
	const QMetaObject * metaObject = obj->metaObject();
	QMetaProperty property;
	bool found =false;
	for (int i = 0; i < metaObject->propertyCount(); ++i)
	{
		if(metaObject->property(i).name() == propertyName)
		{
			property = metaObject->property(i);
			found = true;
		}
	}
	if(!found)
		return false;

	return property.hasNotifySignal();
}
