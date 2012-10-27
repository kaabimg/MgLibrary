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
#ifndef MGOBJECTSSET_H_
#define MGOBJECTSSET_H_
#include <QtCore/QHash>
#include <QtCore/QString>

template<class T>
class MgObjectsSet
{
public:
	MgObjectsSet(bool del=false):m_delete(del){	}
	virtual ~MgObjectsSet()
	{
		if(m_delete)
			qDeleteAll(m_objects);
	}

	void add(const QString& id,const T * obj)
	{
		if(!m_objects.contains(id))
			m_objects.insert(id,obj);
	}
	bool contains(const QString& id){return m_objects.contains(id);}
	T * object(const QString& id){return m_objects[id];}


private:
	bool m_delete;
	QHash<QString,T*> m_objects;

};



#endif /* MGOBJECTSSET_H_ */
