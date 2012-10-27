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
#ifndef MGLOCKABLEOBJECT_H_
#define MGLOCKABLEOBJECT_H_
//MG_INCLUDE_INFO:MgLockableObject

#include <QReadWriteLock>
class MgLockableObject
{
public:
	MgLockableObject(){}
	virtual ~MgLockableObject(){}
	void unlock()
	{
		m_lock.unlock();
	}

	void lockForRead()
	{
		m_lock.lockForRead();
	}
	void lockForWrite()
	{
		m_lock.lockForWrite();
	}
private:
	QReadWriteLock m_lock;
};

class MgLockableObjectLocker
{
public:
	enum LockMode{Read,Write};
	MgLockableObjectLocker(MgLockableObject * obj ,LockMode mode):m_obj(obj)
	{
		if(mode == Read)
			obj->lockForRead();
		else
			obj->lockForWrite();
	}
	~MgLockableObjectLocker()
	{
		m_obj->unlock();
	}
private:
	MgLockableObject * m_obj;
};

#endif /* MGLOCKABLEOBJECT_H_ */
