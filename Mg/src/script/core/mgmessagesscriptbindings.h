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
#ifndef MGMESSAGESSCRIPTBINDINGS_H_
#define MGMESSAGESSCRIPTBINDINGS_H_

//MG_INCLUDE_INFO:MgMessagesScriptBindings


#include <MgCore/MgMessagesEmitter>
#include "mgscriptengine.h"

class MgMessagesScriptBindings : public QObject, public MgMessagesEmitter
{
	Q_OBJECT
	Q_CLASSINFO("MG_SLOTS",""
			"informationMessage,"
			"warningMessage,"
			"errorMessage")
public:
	MgMessagesScriptBindings(MgScriptEngine * scriptEngine)
	{
		setObjectName("mgMsgManager");
		scriptEngine->registerObject(this);

	}
	~MgMessagesScriptBindings(){}


public Q_SLOTS:
	void informationMessage(const QString & msg)
	{
		MgMessagesEmitter::informationMessage(msg);
	}
	void warningMessage(const QString & msg)
	{
		MgMessagesEmitter::warningMessage(msg);
	}
	void errorMessage(const QString & msg)
	{
		MgMessagesEmitter::errorMessage(msg);
	}


};

#endif /* MGMESSAGESSCRIPTBINDINGS_H_ */
