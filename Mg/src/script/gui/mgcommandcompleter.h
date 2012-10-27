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
#ifndef MGCOMMANDCOMPLETER_H_
#define MGCOMMANDCOMPLETER_H_

#include <QStringList>

class MgScriptEngine;
class MgScriptEngineObjectInfo;



class MgCommandCompleter
{
public:
	struct CompletionResult
	{
		QString prefix;
		QStringList completion;
	};

	MgCommandCompleter(const MgScriptEngine *);
	virtual ~MgCommandCompleter();
	CompletionResult completionOf(const QString & ,int);

private:
	const MgScriptEngine * m_scriptEngine;
	MgScriptEngineObjectInfo * m_objectInfo;
};

#endif /* MGCOMMANDCOMPLETER_H_ */
