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
#include "mgqobjecttreeinfo.h"

#include "mgqobjecttreeview.h"
#include "../core/mgqobjectinfo.h"
#include <QStringListModel>
#include <QListView>

MgQObjectTreeInfo::MgQObjectTreeInfo(QObject * object,QWidget * parent) : QSplitter(parent)
{
	m_objectTreeView = new MgQObjectTreeView(object,this);
	m_listView = new QListView(this);
	addWidget(m_objectTreeView);
	addWidget(m_listView);
	connect(m_objectTreeView,SIGNAL(objectSelected(QObject*)),this,SLOT(showObjectInfo(QObject*)));
}

MgQObjectTreeInfo::~MgQObjectTreeInfo(){}

void MgQObjectTreeInfo::showObjectInfo(QObject * newObject)
{
	QStringListModel * model = new QStringListModel;
	QStringList info = MgQObjectInfo::slotsSignatures(newObject);
	info.append("\n\n");
	info.append(MgQObjectInfo::staticPropertiesValues(newObject));


	model->setStringList(info);
	m_listView->setModel(model);
}
