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
** along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
** 
****************************************************************************/
#include "guitestclass.h"
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>

GuiTestClass::GuiTestClass(QWidget * parent):QMainWindow(parent)
{
	m_button1 = new QPushButton("button1",this);
	m_button1->setObjectName("button1");
	m_button2 = new QPushButton("button2",this);
	m_button2->setObjectName("button2");

	m_textEdit = new QTextEdit(this);
	m_textEdit->setObjectName("textEdit");

	QVBoxLayout  * buttonLayout = new QVBoxLayout();
	buttonLayout->setObjectName("buttonsLayout");

	buttonLayout->addWidget(m_button1);
	buttonLayout->addWidget(m_button2);

	QHBoxLayout  * mainLayout = new QHBoxLayout();
	mainLayout->setObjectName("mainLayout");

	QWidget * centralWidget = new QWidget(this);
	centralWidget->setObjectName("centralWidget");

	mainLayout->addWidget(m_textEdit);
	mainLayout->addLayout(buttonLayout);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);

	setObjectName("mainWindow");

	connect(m_button1,SIGNAL(clicked()),this,SLOT(onButton1Clicked()));
	connect(m_button2,SIGNAL(clicked()),this,SLOT(onButton1Clicked()));

	menuBar()->setObjectName("menuBar");
	QMenu * menu1 = menuBar()->addMenu("menu1");

	menu1->setObjectName("menu1");
	menu1->addAction("action1_1",this,SLOT(onActionTriggered()))->setObjectName("action1_1");
	menu1->addAction("action1_2",this,SLOT(onActionTriggered()))->setObjectName("action1_2");
	menu1->addAction("action1_3",this,SLOT(onActionTriggered()))->setObjectName("action1_3");

	QMenu * menu2 = menuBar()->addMenu("menu2");
	menu2->setObjectName("menu2");
	menu2->addAction("action2_1",this,SLOT(onActionTriggered()))->setObjectName("action2_1");
	menu2->addAction("action2_2",this,SLOT(onActionTriggered()))->setObjectName("action2_2");
	menu2->addAction("action2_3",this,SLOT(onActionTriggered()))->setObjectName("action2_3");

	QMenu * menu3 = menuBar()->addMenu("menu3");
	menu3->setObjectName("menu3");
	menu3->addAction("action3_1",this,SLOT(onActionTriggered()))->setObjectName("action3_1");
	menu3->addAction("action3_2",this,SLOT(onActionTriggered()))->setObjectName("action3_2");
	menu3->addAction("action3_3",this,SLOT(onActionTriggered()))->setObjectName("action3_3");
}

GuiTestClass::~GuiTestClass(){}


QTextEdit * GuiTestClass::textEdit()const
{
	return m_textEdit;
}


void GuiTestClass::addText(const QString & text)
{
	m_textEdit->append(text);
}

void GuiTestClass::onButton1Clicked()
{
	addText("Text from button 1");
}
void GuiTestClass::onButton2Clicked()
{
	addText("Text from button 2");
}
void GuiTestClass::onActionTriggered()
{
	addText(qobject_cast<QAction*>(sender())->text());
}
