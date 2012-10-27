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
#ifndef MGMESSAGESEMITTER_H_
#define MGMESSAGESEMITTER_H_

//MG_INCLUDE_INFO:MgMessagesEmitter


#include <QObject>

class MgMessagesSignalsEmitter;

class MgMessagesEmitter
{
public:
	enum MessageType{Information,Warning,Error};
	MgMessagesEmitter();
	virtual ~MgMessagesEmitter();

	void informationMessage(const QString &);
	void warningMessage(const QString &);
	void errorMessage(const QString &);

	MgMessagesSignalsEmitter * messagesSignalsEmitter()const
	{
		return m_emitter;
	}
protected:
	MgMessagesSignalsEmitter * m_emitter;
};

///////

class MgMessagesSignalsEmitter : public QObject
{
	Q_OBJECT
public:
	MgMessagesSignalsEmitter(){}

public Q_SLOTS:
	void emitMessage(const QString & ,MgMessagesEmitter::MessageType);
Q_SIGNALS:
	void informationMessage(const QString &);
	void warningMessage(const QString &);
	void errorMessage(const QString &);

};

#endif /* MGMESSAGESEMITTER_H_ */
