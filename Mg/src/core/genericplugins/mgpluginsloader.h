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
#ifndef MGPLUGINSLOADER_H_
#define MGPLUGINSLOADER_H_

//MG_INCLUDE_INFO:MgPluginsLoader

#include <QList>
#include <QString>

class MgPlugin;
class MgPluginsLoader
{
public:
	MgPluginsLoader();
	virtual ~MgPluginsLoader();

protected:
	void registerPlugin(const QString&, const QString&){}

private:
	virtual void * instantiatePlugin(const QString&, const QString&)=0;
	friend class MgPlugin;

};

#endif /* MGPLUGINSLOADER_H_ */
