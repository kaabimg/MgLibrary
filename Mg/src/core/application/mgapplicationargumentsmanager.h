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
#ifndef MGAPPLICATIONARGUMENTSMANAGER_H_
#define MGAPPLICATIONARGUMENTSMANAGER_H_

//MG_INCLUDE_INFO:MgApplicationArgumentsManager


#include <QStringList>
#include <QHash>

class MgApplicationArgumentsManager
{
public:
	MgApplicationArgumentsManager(const QStringList &);

	bool containsOption(const QString & option)const;
	int optionArgumentsSize(const QString & option);
	QStringList optionArguments(const QString & option)const;
	QStringList options()const;

private:
	QHash<QString,QStringList> m_options;
};

#endif /* MGAPPLICATIONARGUMENTSMANAGER_H_ */
