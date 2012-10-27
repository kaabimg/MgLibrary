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
#ifndef MGPLUGIN_H_
#define MGPLUGIN_H_

//MG_INCLUDE_INFO:MgPlugin

#include <QString>
#include "mgpluginsloader.h"
#include "mgclassescollection.h"
//TODO
#define MG_PLU

class MgPlugin
{
public:
	MgPlugin(const QString & baseClassName,const QString & className,MgPluginsLoader*pluginsLoader)
	:m_baseClassName(baseClassName),m_className(className),m_pluginsLoader(pluginsLoader) {}
	~MgPlugin(){}

	QString className()const{return m_className;}
	QString baseClassName()const{return m_baseClassName;}

	template<class T*>
	T * instance()
	{
		return dynamic_cast<T*>(m_pluginsLoader->instantiatePlugin(m_className,m_baseClassName));
	}

private:
	QString m_baseClassName,m_className;
	MgPluginsLoader* m_pluginsLoader;
};

#endif /* MGPLUGIN_H_ */
