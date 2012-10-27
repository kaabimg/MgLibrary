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
#ifndef MGOBJECTPROPERTIESMANAGER_H_
#define MGOBJECTPROPERTIESMANAGER_H_

//MG_INCLUDE_INFO:MgObjectPropertiesManager

#include <QList>
#include <QObject>
#include <QVariant>
#include <MgCore/MgGlobal>

class QtTreePropertyBrowser;
class QtVariantPropertyManager;
class QtVariantProperty;
class QtProperty;

MG_USE_PRIVATE_CLASS(MgObjectPropertiesManager)


class MgObjectPropertiesManager : public QObject
{
	Q_OBJECT
public:
	MgObjectPropertiesManager(QtVariantPropertyManager *,QtTreePropertyBrowser *,QObject * parent=0);
	virtual ~MgObjectPropertiesManager();
	QtVariantPropertyManager * propertiesManager()const;

public Q_SLOTS:
	void setcontrolledObject(QObject *);

private:
	MG_PRIVATE_CLASS(MgObjectPropertiesManager)

	void watchProperty(QObject * obj,const QString & name);
	void setPropertyAttribute(QtVariantProperty *, QObject *, int);
private Q_SLOTS:
	void onPropertyChanged(const QString& name);
	void onPropertyChanged(QtProperty*,const QVariant&);
	void reloadPropertiesAttributes();

};

#endif /* MGOBJECTPROPERTIESMANAGER_H_ */
