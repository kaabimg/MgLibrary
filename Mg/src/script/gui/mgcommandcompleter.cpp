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
#include "mgcommandcompleter.h"
#include "../core/mgscriptengine.h"
#include "../core/mgscriptengineobjectinfo.h"
#include <QDebug>

MgCommandCompleter::MgCommandCompleter(const MgScriptEngine * scriptEngine)
{
	m_scriptEngine = scriptEngine;
	m_objectInfo = new MgScriptEngineObjectInfo;
}

MgCommandCompleter::~MgCommandCompleter()
{
	delete m_objectInfo;
}


MgCommandCompleter::CompletionResult MgCommandCompleter::completionOf(const QString & command,int index)
{
//	qDebug()<<"==========================";
	CompletionResult completion;
	bool isText = false;
	QStringList objects;
	QString currentObject;
	bool newObject = true;
	for(int i =0 ;i < index;++i)
	{
		if(command[i] == '\'')
			isText = !isText;


		if(!isText && (command[i] == '.'
				|| command[i] == '('
				|| command[i] == ')'
				|| command[i] == ','
				|| command[i] == '=')
				)
		{
			if(!currentObject.isEmpty())
			{
				objects<<currentObject.trimmed();
				currentObject.clear();
			}
			newObject = (command[i] == '(' || command[i] == ',' || command[i] == '=');
		}
		else
			currentObject+= command[i];
	}
	currentObject = currentObject.trimmed();
	completion.prefix = currentObject;

//	qDebug()<<"currentObject"<<currentObject;
	QStringList completionStringList;

	if(objects.isEmpty() || newObject )
	{
		QStringList objects = m_scriptEngine->registeredObjectsNames();
		if(!currentObject.isEmpty())
		{
			foreach(const QString & obj,objects)
			{
				if(obj.startsWith(currentObject,Qt::CaseInsensitive))
					completionStringList<<obj;
			}
			completion.completion = completionStringList;
		}
		else
		{
			completion.completion = objects;
		}
	}
	else
	{
		completion.completion =
				 m_scriptEngine->exportedPropertiesOf(objects.last(),currentObject,Qt::CaseInsensitive)
				 +
				 m_scriptEngine->exportedSlotsOf(objects.last(),currentObject,Qt::CaseInsensitive)
				 ;
	}

//	qDebug()<<completion.prefix;
//	qDebug()<<completion.completion;

	return completion;
}
