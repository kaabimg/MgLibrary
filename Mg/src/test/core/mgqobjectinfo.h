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
#ifndef MGQOBJECTINFO_H_
#define MGQOBJECTINFO_H_

//MG_INCLUDE_INFO:MgQObjectInfo

#include <QObject>
#include <QStringList>
#include <QMetaMethod>
class MgQObjectInfo
{
public:
	MgQObjectInfo(){}
	virtual ~MgQObjectInfo(){}


	static QStringList slotsSignatures(QObject * object)
	{
		QStringList methods;
		QString result;
		for (int i = 0; i < object->metaObject()->methodCount(); ++i)
		{
			if(object->metaObject()->method(i).access()==QMetaMethod::Public)
			{
				result=QString(object->metaObject()->method(i).typeName()).isEmpty() ? "void" :
						object->metaObject()->method(i).typeName() ;
				result+=" ";
				result+=object->metaObject()->method(i).signature();
				methods.append( result);
			}
		}
		return methods;
	}


	static QStringList staticPropertiesValues(QObject * object)
	{
		QStringList properies;
		QString property,value;

		for (int i = 0; i < object->metaObject()->propertyCount(); ++i)
		{
			property = object->metaObject()->property(i).typeName();
			property += " ";
			property += object->metaObject()->property(i).name();

			value = object->metaObject()->property(i).read(object).toString();
			if( !value.isEmpty())
				property += " : "+value +";";
			else
				property +=";";
			properies.append(property);

		}
		return properies;
	}



};

#endif /* MGQOBJECTINFO_H_ */
