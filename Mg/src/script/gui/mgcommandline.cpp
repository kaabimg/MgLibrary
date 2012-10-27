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
#include "mgcommandline.h"
#include <QPalette>
#include <qcompleter.h>
#include <QAbstractItemView>
#include <QDebug>
#include <QStringListModel>
#include <QKeyEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QDebug>

#include "../core/mgscriptengine.h"
#include "mgcommandcompleter.h"

MgCommandLine::MgCommandLine(QWidget * parent)
:QLineEdit(parent),m_scriptEngine(0)
{
	setStyleSheet(" "
			"QLineEdit {"
			"border: 1px solid darkgray;"
			"border-radius: 2px;"
			"padding: 0 8px;"
			"background: rgb(45,45,45);"
			"color: rgb(210,210,210);"
			"selection-background-color: darkgray;"
			"}");

	m_completionModel = new  QStringListModel(this);
	m_completionModel->setStringList(QStringList());
	m_completer = new QCompleter(m_completionModel,this);
	m_completer->setCompletionMode(QCompleter::PopupCompletion);
	setCompleter(m_completer);
	disconnect(m_completer, 0, this, 0);
    connect(m_completer, SIGNAL(activated(QString)),this,SLOT(insertText(QString)));
	QPalette p = m_completer->popup()->palette();
	p.setColor(QPalette::Base,QColor(45,45,45));
	p.setColor(QPalette::Text,QColor(210,210,210));
	m_completer->popup()->setPalette(p);
	m_completer->popup()->setWindowOpacity(.8);
	connect(this,SIGNAL(textChanged(QString)),this,SLOT(updateCompletion()));
}

MgCommandLine::~MgCommandLine()
{

}

void MgCommandLine::setScriptEngine(MgScriptEngine * scriptEngine)
{
	m_scriptEngine = scriptEngine;
}

void MgCommandLine::keyPressEvent(QKeyEvent * e)
{
	if(e->key() == Qt::Key_Escape )
		clear();
	else if((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return ) && m_scriptEngine && m_completer->popup()->isVisible())
	{
		insertText(m_completer->popup()->currentIndex().data().toString());
		m_completer->popup()->hide();
	}
	else if((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return ) && m_scriptEngine)
	{
		m_scriptEngine->execCommand(text());
		clear();
	}
	else if(e->key() == Qt::Key_Space && e->modifiers().testFlag(Qt::ControlModifier))
	{
		if(!m_completer->popup()->isVisible())
		{
			MgCommandCompleter completer(m_scriptEngine);
			MgCommandCompleter::CompletionResult result = completer.completionOf(text(),cursorPosition());

			m_completer->setCompletionPrefix("");
			m_prefix = result.prefix;
			m_completionModel->setStringList(result.completion);
			m_completer->complete();
		}
		else
		{
			m_completer->popup()->hide();
		}

	}
	else
		QLineEdit::keyPressEvent(e);
}
void MgCommandLine::focusInEvent(QFocusEvent *e)
{
	QLineEdit::focusInEvent(e);
	disconnect(m_completer, 0, this, 0);
	connect(m_completer, SIGNAL(activated(QString)),this,SLOT(insertText(QString)));
}

void MgCommandLine::insertText(const QString & newText)
{

	QString myText(text());
	int pos(cursorPosition()-m_prefix.size());
	myText.remove(pos,m_prefix.size());
	myText.insert(pos,newText);
	setText(myText);
	m_prefix.clear();
}

void MgCommandLine::updateCompletion()
{
	if(!m_scriptEngine)
		return;


	if(!m_completer->popup()->isVisible())
		return;

	MgCommandCompleter completer(m_scriptEngine);
	MgCommandCompleter::CompletionResult result = completer.completionOf(text(),cursorPosition());

	m_completer->setCompletionPrefix("");
	m_prefix = result.prefix;
	m_completionModel->setStringList(result.completion);
	m_completer->complete();
}



//=========================================================================================



MgCommandLineWidget::MgCommandLineWidget(QWidget * parent):QWidget(parent)
{
	m_commandLine = new MgCommandLine(this);
	m_execButton = new QPushButton(this);
	m_execButton->setIcon(style()->standardPixmap(QStyle::SP_MediaPlay));
	m_execButton->setAutoFillBackground(true);
	QPalette p = m_execButton->palette();
	p.setColor(m_execButton->backgroundRole(),Qt::black);
	m_execButton->setPalette(p);

	m_execButton->setToolTip("Execute cached program");
	QHBoxLayout * layout = new QHBoxLayout;

	layout->addWidget(m_commandLine);
	layout->addWidget(m_execButton);
	layout->setMargin(0);
	layout->setContentsMargins(0,0,0,0);
	layout->setSpacing(0);
	setLayout(layout);

}
void MgCommandLineWidget::setExecButtonIcon(const QIcon & icon)
{
	m_execButton->setIcon(icon);
}


MgCommandLineWidget::~MgCommandLineWidget(){}


MgScriptEngine * MgCommandLineWidget::scriptEngine()const
{
	return m_commandLine->scriptEngine();
}
void MgCommandLineWidget::setScriptEngine(MgScriptEngine * scriptEngine)
{
	if(m_commandLine->scriptEngine())
		disconnect(m_execButton,SIGNAL(pressed()),m_commandLine->scriptEngine(),SLOT(execCachedProgram()));
	m_commandLine->setScriptEngine(scriptEngine);
	connect(m_execButton,SIGNAL(pressed()),scriptEngine,SLOT(execCachedProgram()));
}


