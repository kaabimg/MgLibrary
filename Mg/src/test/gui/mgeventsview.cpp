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
#include "mgeventsview.h"

MgEventsView::MgEventsView(QWidget * parent):QTableWidget(parent)
{
	setColumnCount(3);
	QStringList labels;
	labels<<"Type"<<"Name"<<"Event";
	setHorizontalHeaderLabels(labels);
}

MgEventsView::~MgEventsView()
{

}

void MgEventsView::addEvent(const QString & type,const QString & name,const QString & event)
{
	setRowCount(rowCount()+1);

	QTableWidgetItem * item = new QTableWidgetItem;
	item->setText(type);
	setItem(rowCount()-1,0,item);

	item = new QTableWidgetItem;
	item->setText(name);
	setItem(rowCount()-1,1,item);

	item = new QTableWidgetItem;
	item->setText(event);
	setItem(rowCount()-1,2,item);
}
