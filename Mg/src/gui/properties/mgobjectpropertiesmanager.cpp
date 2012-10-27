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
#include "mgobjectpropertiesmanager.h"
#include "mgpropertywatcher.h"

#include <QMap>
#include <QtVariantProperty>
#include <QtVariantPropertyManager>
#include <QtTreePropertyBrowser>
#include <QMetaClassInfo>

#include <QDebug>

struct MgObjectPropertiesManagerPrivate
{
	QObject * controlledObject;
	QMap<QString,QString> userNamesMap;
	QMap<QString,QtVariantProperty *> exposableProperies;
	QtVariantPropertyManager * propertiesManager;
	QtTreePropertyBrowser *browser;
};



MgObjectPropertiesManager::MgObjectPropertiesManager(QtVariantPropertyManager* manager,
		QtTreePropertyBrowser *browser ,QObject * parent)
	:QObject(parent),d_ptr(new MgObjectPropertiesManagerPrivate)
{
	d_ptr->controlledObject = 0;
	d_ptr->propertiesManager = manager;
	d_ptr->browser = browser;
	connect(d_ptr->propertiesManager,SIGNAL(valueChanged(QtProperty *,QVariant)),
			this,SLOT(onPropertyChanged(QtProperty *,QVariant)));
}

MgObjectPropertiesManager::~MgObjectPropertiesManager(){}

QtVariantPropertyManager * MgObjectPropertiesManager::propertiesManager()const
{
	return d_ptr->propertiesManager;
}


void MgObjectPropertiesManager::setcontrolledObject(QObject * obj)
{
	int classInfoIndex = obj->metaObject()->indexOfClassInfo("MG_PROPERTIES");
	if(classInfoIndex == -1)
		return;

	if(obj->metaObject()->indexOfSignal("metaClassInfoChanged()") != -1)
		connect(obj,SIGNAL(metaClassInfoChanged()),this,SLOT(reloadPropertiesAttributes()));

	QString ediatableProperties = obj->metaObject()->classInfo(classInfoIndex).value();
	QStringList ediatablePropertiesNames = ediatableProperties.split(',');
	for (int i = 0; i < ediatablePropertiesNames.size(); ++i)
		ediatablePropertiesNames[i] = ediatablePropertiesNames[i].trimmed();


	d_ptr->controlledObject = obj;
	QVariant value;
	QtVariantProperty * property;
	foreach(const QString & name , ediatablePropertiesNames)
	{
		value = obj->property(name.toLatin1().constData());
		if(!value.isValid())
			continue;

		QString userName(name);
		int userNameIndex = obj->metaObject()->indexOfClassInfo((name+"_uname").toLatin1().constData());
		if(userNameIndex!=-1)
			userName = obj->metaObject()->classInfo(userNameIndex).value();

		d_ptr->userNamesMap.insert(userName,name);

		property = d_ptr->propertiesManager->addProperty(value.type(),userName);
		if(property)
		{
			property->setValue(value);
			d_ptr->exposableProperies.insert(name,property);
			setPropertyAttribute(property,obj,value.type());
			watchProperty(obj,name);
			d_ptr->browser->addProperty(property);
		}

	}
}


void MgObjectPropertiesManager::setPropertyAttribute(
		QtVariantProperty * property, QObject * obj, int type)
{
	QString propertyInfoId = d_ptr->userNamesMap[property->propertyName()]+"_info";
	QString propertyInfo;
	if(obj->dynamicPropertyNames().contains(propertyInfoId.toLatin1()))
		propertyInfo = obj->property(propertyInfoId.toLatin1().constData()).toString();
	else
	{
		int index = obj->metaObject()->indexOfClassInfo(propertyInfoId.toLatin1().constData());
		if(index != -1)
			propertyInfo = obj->metaObject()->classInfo(index).value();
	}
	if(propertyInfo.isEmpty())
		return;
	bool ok;
	switch (type)
	{
		case QVariant::Int:
		{
			QStringList info = propertyInfo.split(',');
			if(info.size() != 3)
				return;
			QString minStr = info[0].trimmed();
			QString maxStr = info[1].trimmed();
			QString stepStr = info[2].trimmed();
			int min,max,step;
			min = minStr.toInt(&ok);
			if(ok)
				property->setAttribute("minimum",min);
			max = maxStr.toInt(&ok);
			if(ok)
				property->setAttribute("maximum",max);
			step = stepStr.toInt(&ok);
			if(ok)
				property->setAttribute("singleStep",step);
			break;
		}
		case QVariant::Double:
		{
			QStringList info = propertyInfo.split(',');
			if(info.size() < 3)
				return;
			QString minStr = info[0].trimmed();
			QString maxStr = info[1].trimmed();
			QString stepStr = info[2].trimmed();
			double min,max,step;
			min = minStr.toDouble(&ok);
			if(ok)
				property->setAttribute("minimum",min);
			max = maxStr.toDouble(&ok);
			if(ok)
				property->setAttribute("maximum",max);
			step = stepStr.toDouble(&ok);
			if(ok)
				property->setAttribute("singleStep",step);

			if(info.size()>=4)
			{
				QString decimals = info.at(3);

				int d = decimals.toInt(&ok);
				if(ok)
					property->setAttribute("decimals",d);
			}

			break;
		}
		case QVariant::String:
		{
			property->setAttribute("regExp",propertyInfo);
			break;
		}
		case QVariant::Date:
			break;
		case QVariant::PointF:
			break;
		case QVariant::Size:
			break;
		case QVariant::SizeF:
			break;
		case QVariant::Rect:
			break;
		case QVariant::RectF:
			break;
		default:
			break;
	}
}

void MgObjectPropertiesManager::reloadPropertiesAttributes()
{
	foreach(QtProperty * property,d_ptr->propertiesManager->properties())
		setPropertyAttribute(
				dynamic_cast<QtVariantProperty*>(property),
				d_ptr->controlledObject,
				dynamic_cast<QtVariantProperty*>(property)->propertyType());
}

void MgObjectPropertiesManager::watchProperty(QObject * obj,const QString & name)
{
	if(!MgPropertyWatcher::hasNotifySignal(obj,name))
		return;
	MgPropertyWatcher * watcher = new MgPropertyWatcher(this);
	watcher->init(d_ptr->controlledObject,name);
	connect(watcher,SIGNAL(propertyChanged(QString)),this,SLOT(onPropertyChanged(QString)));
}
void MgObjectPropertiesManager::onPropertyChanged(const QString& name)
{
	d_ptr->exposableProperies[name]->setValue
	(d_ptr->controlledObject->property(name.toLatin1().constData()));
}

void MgObjectPropertiesManager::onPropertyChanged(QtProperty* property,const QVariant& value)
{
	d_ptr->controlledObject->setProperty(
			d_ptr->userNamesMap.value(property->propertyName()).toLatin1().constData(),
			value
			);
}
