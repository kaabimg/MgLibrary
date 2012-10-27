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
#ifndef MGQOBJECTTREEINFO_H_
#define MGQOBJECTTREEINFO_H_

//MG_INCLUDE_INFO:MgQObjectTreeInfo

#include <QSplitter>
class QListView;
class MgQObjectTreeView;
class MgQObjectTreeInfo : public QSplitter
{
	Q_OBJECT
public:
	MgQObjectTreeInfo(QObject *,QWidget *  =0);
	virtual ~MgQObjectTreeInfo();


private Q_SLOTS:
	void showObjectInfo(QObject *);

private:
	QListView * m_listView;
	MgQObjectTreeView * m_objectTreeView;
};

#endif /* MGQOBJECTTREEINFO_H_ */
