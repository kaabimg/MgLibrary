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
#include "mgqobjecttreemodel.h"

MgQObjectTreeModel::MgQObjectTreeModel(QObject * root,QObject * parent)
:QAbstractItemModel(parent),m_rootObject(root)
{

}
MgQObjectTreeModel::~MgQObjectTreeModel(){}


QVariant MgQObjectTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	QObject * object = static_cast<QObject*>(index.internalPointer());

	switch (index.column())
	{
	case 0:
		return object->objectName().isEmpty() ? "Unknown" : object->objectName();
		break;
	case 1:
		return object->property("hierarchical_name").toString().isEmpty() ?
				"Unknown" :  object->property("hierarchical_name");
		break;
	case 2:
		return object->metaObject()->className();
		break;
	default:
		return QVariant();
		break;
	}
	return QVariant();
}

Qt::ItemFlags MgQObjectTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
QVariant MgQObjectTreeModel::headerData(int section, Qt::Orientation orientation,int role ) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch (section)
		{
			case 0:
				return "Name";
				break;
			case 1:
				return "Hierarchical name";
				break;
			case 2:
				return "Type";
				break;
			default:
				return QVariant();
				break;
		}
	}
	return QVariant();
}


QModelIndex MgQObjectTreeModel::index(int row, int column,const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	if (!parent.isValid())
		return createIndex(row, column, m_rootObject);

	QObject *childItem = static_cast<QObject*>(parent.internalPointer())->children()[row];
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}
QModelIndex MgQObjectTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	QObject *childItem = static_cast<QObject*>(index.internalPointer());
	QObject *parentItem = childItem->parent();

	if (childItem == m_rootObject)
		return QModelIndex();
	if (parentItem == m_rootObject)
		return createIndex(0, 0, m_rootObject);

	return createIndex(parentItem->parent()->children().indexOf(parentItem), 0, parentItem);
}
int MgQObjectTreeModel::rowCount(const QModelIndex &parent) const
{
	QObject *parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		return 1;//root
	else
		parentItem = static_cast<QObject*>(parent.internalPointer());

	return parentItem->children().size();
}
int MgQObjectTreeModel::columnCount(const QModelIndex &) const
{
	return 3;
}
