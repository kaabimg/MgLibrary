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
#include "mgapplicationargumentsmanager.h"
#include "../log/mgapplicationlogmanager.h"
#include <QStringList>

MgApplicationArgumentsManager::MgApplicationArgumentsManager(const QStringList & args)
{
	QString currentOption;
	QStringList currentOptionArgs;
	foreach(const QString & arg,args)
	{
		if(arg.startsWith('-'))
		{
			if(!currentOption.isEmpty())
			{
				m_options.insert(currentOption,currentOptionArgs);
			}
			currentOption = arg;
			currentOptionArgs.clear();
		}
		else
			currentOptionArgs<<arg;
	}
	if(!currentOption.isEmpty())
	{
		m_options.insert(currentOption,currentOptionArgs);
	}

}

QStringList MgApplicationArgumentsManager::options()const
{
	return m_options.keys();
}

bool MgApplicationArgumentsManager::containsOption(const QString & option)const
{
	return m_options.contains(option);
}
QStringList MgApplicationArgumentsManager::optionArguments(const QString & option)const
{
	return m_options.value(option);
}

int MgApplicationArgumentsManager::optionArgumentsSize(const QString & option)
{
	if(!m_options.contains(option))
		return -1;
	return m_options.value(option).size();
}

