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
#include "mgscriptengineobjectsinfowidget.h"
#include "../core/mgscriptengineobjectinfo.h"
#include "../core/mgscriptengine.h"

#include <QTreeWidgetItem>

MgScriptEngineObjectsInfoWidget::MgScriptEngineObjectsInfoWidget(MgScriptEngine * scriptEngine,QWidget * parent)
	: QTreeWidget(parent),m_scriptEngine(scriptEngine)
{
	setColumnCount(3);
	setHeaderLabels(QStringList()
			<<"Registered object properties and slots"
			<<"Access mode"
			<<"Notify signal");
	connect(m_scriptEngine,SIGNAL(objectRegistered()),this,SLOT(updateContent()));
	updateContent();
	resizeColumnToContents(0);
	resizeColumnToContents(1);
	resizeColumnToContents(2);
}

MgScriptEngineObjectsInfoWidget::~MgScriptEngineObjectsInfoWidget(){}



QTreeWidgetItem  * MgScriptEngineObjectsInfoWidget::createObjectInfoItem(const QObject * obj)
{
	QTreeWidgetItem * mainItem =new QTreeWidgetItem();
	mainItem->setText(0,obj->objectName());

	QTreeWidgetItem * propertiesItem =new QTreeWidgetItem();
	propertiesItem->setText(0,"Properties");
	QString infoStr;
	MgScriptEngineObjectInfo info;
	QString notifySignal;
	QTreeWidgetItem * subItem;
	foreach(const QString & property,info.exportedPropertiesOf(obj))
	{
		subItem = new QTreeWidgetItem();

		infoStr = property+" : "+info.typeOf(obj,property);
		subItem->setText(0,infoStr);
		infoStr = (info.isPropertyWritable(obj,property) ? "Read/Write" : "Read only" );
		subItem->setText(1,infoStr);
		infoStr = (notifySignal =info.notifySignalOf(obj,property)).isEmpty() ?
					"No notify Signal" : notifySignal;
		subItem->setText(2,infoStr);
		propertiesItem->addChild(subItem);
	}
	if(propertiesItem->childCount())
		mainItem->addChild(propertiesItem);
	else
		delete propertiesItem;

	QTreeWidgetItem * slotsItem =new QTreeWidgetItem();
	slotsItem->setText(0,"Slots");
	foreach(const QString & expSlot,info.exportedSlotsOf(obj))
	{
		subItem = new QTreeWidgetItem();
		infoStr = info.slotInfoOf(obj,expSlot);
		if(infoStr.endsWith(": "))
			infoStr += "void";
		subItem->setText(0,infoStr);
		subItem->setText(1,"Write");
		slotsItem->addChild(subItem);
	}
	if(slotsItem->childCount())
		mainItem->addChild(slotsItem);
	else
		delete slotsItem;
	return mainItem;
}

void MgScriptEngineObjectsInfoWidget::updateContent()
{
	clear();
	foreach(const QObject * obj,m_scriptEngine->registerdObjects())
		invisibleRootItem()->addChild(createObjectInfoItem(obj));
}
