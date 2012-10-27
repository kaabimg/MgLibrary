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
#include "mgmessagesemitter.h"

MgMessagesEmitter::MgMessagesEmitter()
{
	m_emitter = new MgMessagesSignalsEmitter;

}

MgMessagesEmitter::~MgMessagesEmitter()
{
	delete m_emitter;
}

void MgMessagesEmitter::informationMessage(const QString & msg)
{
	m_emitter->emitMessage(msg,Information);
}
void MgMessagesEmitter::warningMessage(const QString & msg)
{
	m_emitter->emitMessage(msg,Warning);
}
void MgMessagesEmitter::errorMessage(const QString & msg)
{
	m_emitter->emitMessage(msg,Error);
}
void MgMessagesSignalsEmitter::emitMessage(
		const QString & msg,
		MgMessagesEmitter::MessageType type)
{
	switch (type)
	{
		case MgMessagesEmitter::Information:
			Q_EMIT informationMessage(msg);
			break;
		case MgMessagesEmitter::Warning:
			Q_EMIT warningMessage(msg);
			break;
		case MgMessagesEmitter::Error:
		{
			Q_EMIT errorMessage(msg);
			break;
		}
		default:
			break;
	}
}
