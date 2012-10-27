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
#ifndef MGAPPLICATIONLOGMANAGER_H_
#define MGAPPLICATIONLOGMANAGER_H_

//MG_INCLUDE_INFO:MgApplicationLogManager

#include <QObject>
#include <QString>
#include <QList>
#include "mgabstractlogger.h"


#define MG_INSTALL_LOGGER(logger) MgApplicationLogManager::instance()->installLogger(logger)
#define MG_UNINSTALL_LOGGER(logger) MgApplicationLogManager::instance()->uninstallLogger(logger)
#define MG_LOG(...) MgApplicationLogManager::instance()->log(__VA_ARGS__)


class MgApplicationLogManager : public QObject
{
	Q_OBJECT
public:
	virtual ~MgApplicationLogManager(){}
	static MgApplicationLogManager * instance();

	void log(const QString,MgAbstractLogger::MgLogMessageType type=MgAbstractLogger::Information);

public:
	void installLogger(MgAbstractLogger *);
	void uninstallLogger(MgAbstractLogger *);

private:
	MgApplicationLogManager(QObject * parent=0):QObject(parent){}
	static MgApplicationLogManager * m_globalInstance;
	QList<MgAbstractLogger*> m_loggers;
signals:
	void propagateLog(const QString,MgAbstractLogger::MgLogMessageType);
};

#endif /* MGAPPLICATIONLOGMANAGER_H_ */
