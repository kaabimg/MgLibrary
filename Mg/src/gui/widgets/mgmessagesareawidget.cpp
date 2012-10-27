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
#include "mgmessagesareawidget.h"

#include <MgCore/MgMessagesEmitter>

#include <QTableWidgetItem>
#include <QStyle>
#include <QHeaderView>
#include <QResizeEvent>



MgMessagesAreaWidget::MgMessagesAreaWidget(QWidget * parent):
	QTableWidget(parent),m_totalMessages(0)
{
	setColumnCount(1);
	horizontalHeader()->setVisible(false);
	verticalHeader()->setVisible(false);
	QPalette p = palette();
	p.setColor(QPalette::Base,QColor(75,75,75));
	setPalette(p);

}

MgMessagesAreaWidget::~MgMessagesAreaWidget() {}

void MgMessagesAreaWidget::registerSender(MgMessagesEmitter * emitter)
{
	registerEmitter(emitter->messagesSignalsEmitter());
}

void MgMessagesAreaWidget::registerEmitter(QObject * obj)
{
	connect(obj,SIGNAL(informationMessage(QString)),this,SLOT(informationMessage(QString)));
	connect(obj,SIGNAL(warningMessage(QString)),this,SLOT(warningMessage(QString)));
	connect(obj,SIGNAL(errorMessage(QString)),this,SLOT(errorMessage(QString)));
}


void MgMessagesAreaWidget::addMessage(const QIcon & icon,const QString & msg)
{
	QTableWidgetItem * item = new QTableWidgetItem;
	item->setText(msg);
	item->setIcon(icon);
	item->setTextColor(Qt::white);
	setRowCount(m_totalMessages+1);
	setItem(m_totalMessages,0,item);
	m_totalMessages++;
}

void MgMessagesAreaWidget::resizeEvent(QResizeEvent * e)
{
	QTableWidget::resizeEvent(e);
	setColumnWidth(0,e->size().width());
}

void MgMessagesAreaWidget::informationMessage(const QString& msg)
{
	addMessage(style()->standardPixmap(QStyle::SP_MessageBoxInformation),msg);
}
void MgMessagesAreaWidget::warningMessage(const QString& msg)
{
	addMessage(style()->standardPixmap(QStyle::SP_MessageBoxWarning),msg);
}
void MgMessagesAreaWidget::errorMessage(const QString& msg)
{
	addMessage(style()->standardPixmap(QStyle::SP_MessageBoxCritical),msg);
}
