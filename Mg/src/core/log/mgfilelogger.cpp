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
#include "mgfilelogger.h"
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QTime>
MgFileLogger::MgFileLogger(QString fileName):m_logFileName(fileName)
{
	m_logFile  = new QFile(m_logFileName);
	if(m_logFile->exists())
	{
		m_logFile->remove();
		if(m_logFile->open(QIODevice::WriteOnly))
			m_logFile->close();
	}
}

MgFileLogger::~MgFileLogger()
{
	// TODO Auto-generated destructor stub
}

void MgFileLogger::log(const QString msg,MgLogMessageType type)
{
	if(!m_logFile->open(QIODevice::WriteOnly| QIODevice::Text |QIODevice::Append))
	{
		qDebug()<<"failed to open log file"<<m_logFile->fileName();
		return;
	}
	m_logFile->seek(m_logFile->size()-1);
	QByteArray logMessage;
	switch (type)
	{
		case Information:logMessage.append("information : "+msg+"\n");break;
		case Warning    :logMessage.append("warning     : "+msg+"\n");break;
		case Error      :logMessage.append("error       : "+msg+"\n");break;
	}

	if(writeDate())
		logMessage.prepend(QDate::currentDate().toString().toAscii()+"/"
				+QTime::currentTime().toString().toAscii()+" : ");


	m_logFile->write(logMessage);
	m_logFile->close();

}
