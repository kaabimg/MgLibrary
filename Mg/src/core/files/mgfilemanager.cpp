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
#include "mgfilemanager.h"
#include <QFileSystemWatcher>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QHash>
#include <QMutex>
#include <QMutexLocker>


struct MgFileManagerPrivate
{
	MgFileManagerPrivate():isWatched(false){}
	QString path;
	bool isWatched;
	QString errorString;

	static void watchFile(const QString & fileName)
	{
		QMutexLocker locker(&accessMutex);
		if(watchedFilesCounter.contains(fileName))
		{
			watchedFilesCounter[fileName]++;
		}
		else
		{
			watchedFilesCounter.insert(fileName,1);
			fileSystemWatcher.addPath(fileName);

		}
	}
	static void unwatchFile(const QString &fileName)
	{
		QMutexLocker locker(&accessMutex);
		if(watchedFilesCounter.contains(fileName))
		{
			watchedFilesCounter[fileName]--;
			if(!watchedFilesCounter[fileName])
				fileSystemWatcher.removePath(fileName);
		}
	}
	static bool isFileWatched(const QString &fileName)
	{
		QMutexLocker locker(&accessMutex);
		return watchedFilesCounter.contains(fileName);
	}

	static QFileSystemWatcher fileSystemWatcher;
	static QHash<QString,int> watchedFilesCounter;
	static QMutex accessMutex;
};
QFileSystemWatcher MgFileManagerPrivate::fileSystemWatcher;
QHash<QString,int> MgFileManagerPrivate::watchedFilesCounter;
QMutex MgFileManagerPrivate::accessMutex;




//===========================================================================================


MgFileManager::MgFileManager(const QString & path,QObject * parent):QObject(parent),d_ptr(new MgFileManagerPrivate)
{
	setPath(path);

}

MgFileManager::~MgFileManager()
{
	setFileWatched(false);
	delete d_ptr;
}
QString MgFileManager::fileName()const
{
	QFileInfo fileInfo(d_ptr->path);
	return fileInfo.fileName();
}
QString MgFileManager::path()const
{
	return d_ptr->path;
}
void MgFileManager::setPath(const QString & path)
{
	setFileWatched(false);
	d_ptr->path =path;
}

QString MgFileManager::parentDirectory()const
{
	QFileInfo fileInfo(d_ptr->path);
	return fileInfo.absoluteDir().absolutePath();
}

QString MgFileManager::errorString()
{
	return d_ptr->errorString;
}

bool MgFileManager::exists()const
{
	return QFile::exists(d_ptr->path);
}

bool MgFileManager::save(const QString & data)
{
	QFile me(d_ptr->path);
	if(me.open(QIODevice::WriteOnly))
	{
		me.write(data.toLatin1());
		me.close();
		return true;
	}
	d_ptr->errorString="Can't open "+d_ptr->path;
	return false;
}

void MgFileManager::setFileWatched(bool watch)
{
	if(watch)
	{
		if(!d_ptr->isWatched)
		{
			d_ptr->watchFile(d_ptr->path);
			connect(&(d_ptr->fileSystemWatcher),SIGNAL(fileChanged(const QString &)),
					this,SLOT(onFileSystemFileChanged(const QString &)));
		}
	}
	else
		if(d_ptr->isWatched)
		{
			d_ptr->unwatchFile(d_ptr->path);
			disconnect(&(d_ptr->fileSystemWatcher),SIGNAL(fileChanged(const QString &)),
					this,SLOT(onFileSystemFileChanged(const QString &)));
		}
}

QDateTime MgFileManager::lastModified()const
{
	QFileInfo info(d_ptr->path);
	return info.lastModified();
}

bool MgFileManager::isWatched()const
{
	return d_ptr->isWatched;
}

void MgFileManager::onFileSystemFileChanged(const QString & path)
{
	if(path == d_ptr->path)
		Q_EMIT fileChanged();
}

QString MgFileManager::readContent(bool * openOk)const
{
	QFile me(d_ptr->path);
	if(me.open(QIODevice::ReadOnly))
	{
		QString data = me.readAll();
		me.close();
		return data;
	}
	if(openOk)
		(*openOk)=false;
	return "";
}
