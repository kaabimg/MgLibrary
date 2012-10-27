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
#ifndef MGCLASSESCOLLECTION_H_
#define MGCLASSESCOLLECTION_H_

#include <QHash>
#include <QDebug>
#include <QObject>

#define MG_INSTANTIABLE(Type) \
	public:\
	static void * instance(){return new Type;}\
	private:\


#define MG_REGISTER_INSTANTIABLE_TYPE(Type) \
	MgClassesCollection::registerType(#Type,Type::instance)

#define MG_CREATE_INSTANTIABLE_OBJECT(Type) \
	dynamic_cast<Type*>(MgClassesCollection::createInstance(#Type))

#define MG_CREATE_INSTANTIABLE_QOBJECT(Type) \
	qobject_cast<Type*>(MgClassesCollection::createInstance(#Type))

class MgClassesCollection
{
public:
	static void * createInstance(const char * typeName)
	{
		void *(*instantiationFunction)();
		instantiationFunction = m_instantiaters[typeName];
		if(instantiationFunction == NULL)
		{
			qDebug()<<"Instantiation function of type : "<<typeName<<" not found !! Check if "<<typeName<<" is registered or not.";
			return 0;
		}
		return instantiationFunction();
	}
	static void registerType(const QString & typeName,void *(*instantiationFunction)())
	{
		m_instantiaters.insert(typeName,instantiationFunction);
	}

private:
	static QHash<QString,void *(*)()> m_instantiaters;
	MgClassesCollection(){}
	~MgClassesCollection(){}

};

QHash<QString,void *(*)()> MgClassesCollection::m_instantiaters;

#endif /* MGCLASSESCOLLECTION_H_ */
