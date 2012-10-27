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
#ifndef MGABSTRACTLOGGER_H_
#define MGABSTRACTLOGGER_H_

//MG_INCLUDE_INFO:MgAbstractLogger

#include <QString>
class MgAbstractLogger
{
public:
	enum MgLogMessageType{Information,Warning,Error};

	MgAbstractLogger():m_writeDate(false){}
	virtual ~MgAbstractLogger(){}


	bool writeDate(){return m_writeDate;}
	void setWriteDate(bool wd){m_writeDate = wd;}

protected :

	virtual void log(const QString,MgAbstractLogger::MgLogMessageType)=0;
	friend class MgApplicationLogManager;
private:
	bool m_writeDate;
};

#endif /* MGABSTRACTLOGGER_H_ */
