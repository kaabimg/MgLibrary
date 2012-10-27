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
#include "mgscriptengineobjectinfo.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaClassInfo>
#include <QMetaMethod>

QStringList MgScriptEngineObjectInfo::exportedPropertiesOf(const QObject * obj)
{
	QStringList properties;
	int classInfoIndex = obj->metaObject()->indexOfClassInfo("MG_PROPERTIES");
	if(classInfoIndex == -1)
		return QStringList();


	QString ediatableProperties = obj->metaObject()->classInfo(classInfoIndex).value();
	properties = ediatableProperties.split(',');
	for (int i = 0; i < properties.size(); ++i)
		properties[i] = properties[i].trimmed();
	return properties;
}

QStringList MgScriptEngineObjectInfo::exportedPropertiesOf(
		const QObject * obj,
		const QString & prefix,
		Qt::CaseSensitivity cs)
{
	QStringList properties;
	foreach(const QString & property, exportedPropertiesOf(obj))
	{
		if(property.startsWith(prefix,cs))
			properties<<property;
	}
	return properties;
}


QMetaProperty lookForProperty(const QMetaObject * obj,const QString & property)
{
	QMetaProperty mp;
	for (int i = 0; i < obj->propertyCount(); ++i)
	{
		mp  =obj->property(i);
		if(mp.name() == property)
			return mp;
	}
	return QMetaProperty();
}

QMetaMethod lookForSlot(const QMetaObject * obj,const QString & slotName)
{
	QMetaMethod mm;
	QString sig;
	for (int i = 0; i < obj->methodCount(); ++i)
	{
		mm  =obj->method(i);
		sig = mm.signature();
		int index = sig.indexOf('(');
		sig.remove(index,sig.size()-index);
		if(sig == slotName)
			return mm;
	}
	return QMetaMethod();
}

QString MgScriptEngineObjectInfo::notifySignalOf(
		const QObject * obj,
		const QString & property)
{
	QString info;
	QMetaProperty p = lookForProperty(obj->metaObject(),property);
	return p.notifySignal().signature();
}

QString MgScriptEngineObjectInfo::typeOf(const QObject * obj,const QString & property)
{
	QString info;
	QMetaProperty p = lookForProperty(obj->metaObject(),property);
	return p.typeName();
}

bool MgScriptEngineObjectInfo::isPropertyWritable(
		const QObject * obj,
		const QString & property)
{
	QString info;
	QMetaProperty p = lookForProperty(obj->metaObject(),property);
	if(p.isValid())
		return p.isWritable();
	return false;
}
QStringList MgScriptEngineObjectInfo::exportedSlotsOf(const QObject * obj)
{
	QStringList expSlots;
	int classInfoIndex = obj->metaObject()->indexOfClassInfo("MG_SLOTS");
	if(classInfoIndex == -1)
		return QStringList();
	QString exportedSlots = obj->metaObject()->classInfo(classInfoIndex).value();
	expSlots = exportedSlots.split(',');
	for (int i = 0; i < expSlots.size(); ++i)
		expSlots[i] = expSlots[i].trimmed();
	return expSlots;
}


QStringList MgScriptEngineObjectInfo::exportedSlotsOf(
		const QObject * obj,
		const QString & prefix,
		Qt::CaseSensitivity cs)
{
	QStringList _slots;
	foreach(const QString & slot, exportedSlotsOf(obj))
	{
		if(slot.startsWith(prefix,cs))
			_slots<<slot;
	}
	return _slots;
}

QString MgScriptEngineObjectInfo::slotInfoOf(const QObject * obj,const QString & slotName)
{
	QMetaMethod mm= lookForSlot(obj->metaObject(),slotName);
	QString	signature = mm.signature();
	QString	returnType = mm.typeName();
	return signature+" : "+returnType;

}

