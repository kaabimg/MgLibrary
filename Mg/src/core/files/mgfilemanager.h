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
#ifndef MGFILEMANAGER_H_
#define MGFILEMANAGER_H_

//MG_INCLUDE_INFO:MgFileManager

#include <QObject>
#include <QDateTime>

#include "../mgglobalmacros.h"

MG_USE_PRIVATE_CLASS(MgFileManager)

class MgFileManager : public QObject
{
	Q_OBJECT
public:
	MgFileManager(const QString & path,QObject * parent=0);
	virtual ~MgFileManager();

	QString path()const;
	void setPath(const QString &);
	QString fileName()const;
	QString parentDirectory()const;

	bool exists()const;

	bool save(const QString & data);

	void setFileWatched(bool);
	bool isWatched()const;

	QDateTime lastModified()const;

	QString readContent(bool * ok = NULL)const;
	QString errorString();

Q_SIGNALS:
	void fileChanged();

private:

	Q_SLOT void onFileSystemFileChanged(const QString &);

	MG_PRIVATE_CLASS(MgFileManager)
	Q_DISABLE_COPY(MgFileManager)


};

#endif /* MGFILEMANAGER_H_ */
