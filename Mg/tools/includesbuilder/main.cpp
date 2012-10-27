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
#include <QApplication>
#include <QString>
#include <QFile>
#include <QDir>
#include <QPair>

#include <QDebug>

void createIcludes(const QDir & sourceDirectory,QDir & desitnationDirectory);
void createIncludeFile(const QString & sourceFilePath,const QString & includeFilePath);

typedef QPair<QString,QString> SrcIncludePair;



QMap<QString,QString>  srcIncludePairs;
QStringList srcFolders;
QStringList includeFolders;

void buidScrIncludePairs()
{
	srcFolders<<"core"<<"gui"<<"3d"<<"multimedia"<<"declarative"<<"script"<<"test";
	includeFolders<<"MgCore"<<"MgGui"<<"Mg3D"<<"MgMultimedia"<<"MgDeclarative"<<"MgScript"<<"MgTest";
	for (int i = 0; i <srcFolders.size() ; ++i)
		srcIncludePairs.insert(srcFolders[i],includeFolders[i]);
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	QFileInfo bin(a.arguments().first());
	QDir mgLibDir = bin.absoluteDir();
	mgLibDir.cdUp();
	mgLibDir.cdUp();


	QDir includeDir(mgLibDir);

	includeDir.mkdir("include");

	mgLibDir.cd("src");
	includeDir.cd("include");

	buidScrIncludePairs();


	if(a.argc() == 1)
	{
		for (int i = 0; i <srcFolders.size() ; ++i)
		{
			includeDir.mkdir(includeFolders[i]);
			QDir source(mgLibDir.absolutePath()+QDir::separator()+srcFolders[i]);
			QDir destination(includeDir.absolutePath()+QDir::separator()+includeFolders[i]);
			createIcludes(source,destination);
		}
	}
	else
	{
		QString src = a.arguments()[1];
		includeDir.mkdir(srcIncludePairs[src]);
		QDir source(mgLibDir.absolutePath()+QDir::separator()+src);
		QDir destination(includeDir.absolutePath()+QDir::separator()+srcIncludePairs[src]);
		createIcludes(source,destination);
	}
	return 0;
}


void createIcludes(const QDir & sourceDirectory,QDir & desitnationDirectory)
{
	QFileInfoList includeFiles = sourceDirectory.entryInfoList(QStringList()<<"*.h"<<"*.hpp",QDir::Files);
	foreach(const QFileInfo & includeFile,includeFiles)
		createIncludeFile(includeFile.absoluteFilePath(),desitnationDirectory.absolutePath());

	QFileInfoList subFolders = sourceDirectory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	foreach(const QFileInfo & subFolder, subFolders)
		createIcludes(QDir(subFolder.absoluteFilePath()),desitnationDirectory);
}


void createIncludeFile(const QString & sourceFilePath,const QString & includeFileDirPath)
{
	QFile sourceFile(sourceFilePath);
	if(!sourceFile.open(QFile::ReadOnly|QFile::Text))
	{
		qDebug()<<"Can't open source file"<<sourceFilePath;
		return;
	}

	bool includeInfoFound(false);
	QString includeInfo;
	QString line;
	while(!sourceFile.atEnd())
	{
		line = sourceFile.readLine();
		line = line.trimmed();
		if(line.startsWith("//MG_INCLUDE_INFO"))
		{
			if(line.contains(':'))
			{
				includeInfo = line.split(':').last().trimmed();
				includeInfoFound  =true;
				sourceFile.close();
				break;
			}
			sourceFile.close();
			break;
		}
	}

	if(includeInfoFound)
	{
		QFile includeFile ( includeFileDirPath + QDir::separator() + includeInfo);
		if(!includeFile.open(QFile::WriteOnly| QFile::Text))
		{
			qDebug()<<"Can't open"<< includeFileDirPath + QDir::separator() + includeInfo;
			return;
		}

		QDir includeFileDir (includeFileDirPath);
		QString relativePathToSource = includeFileDir.relativeFilePath(sourceFilePath);

		includeFile.write(qPrintable("#include \""+relativePathToSource+"\""));
		includeFile.close();
	}
	else
		qDebug()<<"No relevant include info found in "+sourceFilePath;

}


