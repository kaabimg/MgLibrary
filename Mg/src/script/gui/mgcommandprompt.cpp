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
#include "mgcommandprompt.h"

#include "mgcommandprompt.h"
#include <QDebug>
#include <QKeyEvent>
#include <QtGlobal>
#include <QPalette>
#include "../core/mgscriptengine.h"

MgCommandPrompt::MgCommandPrompt(QWidget *parent)
    : QTextEdit(parent),m_commandsEndCursorPosition(1),m_commandsIndex(-1),m_newLineChar('>'),
      m_userTextColor("black"),m_systemReturnTextColor("green"),m_backgroundColor("white"),
      m_scriptEngine(0)
{
	setAutoFillBackground(true);
	insertPlainText(m_newLineChar);
	setAcceptRichText(false);
	setReadOnly(true);
	setBackgroundColor("black");
	setUserTextColor("white");
	setSystemReturnTextColor("green");

}

MgCommandPrompt::~MgCommandPrompt(){}

void MgCommandPrompt::setScriptEngine(MgScriptEngine * scriptEngine)
{
	if(m_scriptEngine)
		disconnect(m_scriptEngine,SIGNAL(commandExecuted(QString,QString)),this,SLOT(addCommand(QString,QString)));
	m_scriptEngine = scriptEngine;
	connect(m_scriptEngine,SIGNAL(commandExecuted(QString,QString)),this,SLOT(addCommand(QString,QString)));

}

/**********************************************************************/

void MgCommandPrompt::clearCurrentLine()
{
	QTextCursor cursor=textCursor();
	cursor.setPosition(m_commandsEndCursorPosition);
	setTextCursor(cursor);

	int sizeToDelete=document()->characterCount()-1-m_commandsEndCursorPosition;
	for(int i=0;i<sizeToDelete;i++)
		cursor.deleteChar();
}


void MgCommandPrompt::keyPressEvent(QKeyEvent * e)
{

	switch (e->key())
	{
		case Qt::Key_Up:onPreviousCommand();break;
		case Qt::Key_Down:onNextCommand();break;
		case Qt::Key_Delete:if(textCursor().position()>=m_commandsEndCursorPosition)QTextEdit::keyPressEvent(e);break;
		case Qt::Key_Backspace:if(textCursor().position()>m_commandsEndCursorPosition)QTextEdit::keyPressEvent(e);break;
		case Qt::Key_Left:if(textCursor().position()>m_commandsEndCursorPosition)QTextEdit::keyPressEvent(e);break;

		case Qt::Key_Enter:onEnterKey();break;
		case Qt::Key_Return:onEnterKey();break;
		case Qt::Key_Tab:onTabKey();break;


		default:
			QTextEdit::keyPressEvent(e);
			break;
	}
}

void MgCommandPrompt::execCommand(const QString & command)
{
	if(!m_scriptEngine)
	{
		addCommand(currentCommand(),"Warning : no script engine connected to the command prompt !!");
		return;
	}
	m_scriptEngine->execCommand(command);
}

void MgCommandPrompt::execCompletionRequest(const QString & command)
{
	if(!m_scriptEngine)
	{
		addCommand(currentCommand(),"Warning : no script engine connected to the command prompt !!");
		return;
	}

	setReadOnly(true);
	QStringList completion = m_scriptEngine->commandCompletion(command);

	if(!completion.size())
	{
		setReadOnly(false);
		return;
	}
	if(completion.size()==1)
	{
		if(currentCommand().contains('.'))
		{
			QString completionString = completion.first();
			if(completionString.startsWith('('))
			{
				completionString.remove('(');
				completionString.remove(')');
				completionString = completionString.split(' ').last();
			}
			setCurrentCommand(currentCommand().split('.').first()+'.'+completionString);
		}
		else
			setCurrentCommand(completion.first());

		setReadOnly(false);
	}
	else
	{
		QString ccmd = currentCommand();
		addCommand(currentCommand(),"\t"+completion.join("\n\t"));
		setCurrentCommand(ccmd);
		setReadOnly(false);
	}
}


void MgCommandPrompt::onEnterKey()
{
	if(currentCommand().size()==0)
		return;
	setReadOnly(true);
	execCommand(currentCommand());
}


void MgCommandPrompt::onPreviousCommand()
{
	if(m_commands.isEmpty())
		return;
	m_commandsIndex = qMax(0,m_commandsIndex-1);


	QTextCursor cursor=textCursor();
	cursor.setPosition(m_commandsEndCursorPosition);
	setTextCursor(cursor);

	int sizeToDelete=document()->characterCount()-1-m_commandsEndCursorPosition;
	for(int i=0;i<sizeToDelete;i++)
		cursor.deleteChar();

	insertPlainText(m_commands[m_commandsIndex]->userCommand);


}
void MgCommandPrompt::onNextCommand()
{
	if(m_commands.isEmpty())
		return;

	m_commandsIndex = qMin(m_commands.size(),m_commandsIndex+1);

	QTextCursor cursor=textCursor();
	cursor.setPosition(m_commandsEndCursorPosition);
	setTextCursor(cursor);

	int sizeToDelete=document()->characterCount()-1-m_commandsEndCursorPosition;
	for(int i=0;i<sizeToDelete;i++)
		cursor.deleteChar();

	if(m_commandsIndex==m_commands.size())
		return;
	insertPlainText(m_commands[m_commandsIndex]->userCommand);

}


void MgCommandPrompt::onTabKey()
{
	if(textCursor().position()<m_commandsEndCursorPosition)
		return;

	execCompletionRequest(currentCommand());
}

QString MgCommandPrompt::currentCommand()const
{
	return toPlainText().right(document()->characterCount()-1-m_commandsEndCursorPosition);
}

void MgCommandPrompt::setCurrentCommand(const QString& cmd)
{
	QTextCursor cursor=textCursor();
	cursor.setPosition(m_commandsEndCursorPosition);
	setTextCursor(cursor);

	int sizeToDelete=document()->characterCount()-1-m_commandsEndCursorPosition;
	for(int i=0;i<sizeToDelete;i++)
		cursor.deleteChar();
	insertPlainText(cmd);
	cursor.setPosition(document()->characterCount()-1);
	setTextCursor(cursor);
}

/**********************************************************************/


void MgCommandPrompt::addCommand(const QString & userCommand,const QString & systemResponse)
{
	Command * cmd = new Command;
	m_commands<<cmd;
	m_commandsIndex =  m_commands.size();
	cmd->userCommand = userCommand;
	cmd->systemResponse=systemResponse;

	setTextColor(m_userTextColor);
	insertPlainText(userCommand);
	setTextColor(m_systemReturnTextColor);
	if(cmd->systemResponse=="undefined")
		insertPlainText("\n");
	else
		insertPlainText("\n"+cmd->systemResponse+"\n");
	setTextColor(m_userTextColor);
	insertPlainText(m_newLineChar);
}
void MgCommandPrompt::displayCommand(Command *cmd)
{
	setTextColor(m_userTextColor);
	insertPlainText(m_newLineChar+cmd->userCommand);
	setTextColor(m_systemReturnTextColor);
	if(cmd->systemResponse=="undefined")
		insertPlainText("\n");
	else
		insertPlainText("\n"+cmd->systemResponse+"\n");
	setTextColor(m_userTextColor);
}

/***********************************************************************************************************/

void MgCommandPrompt::setBackgroundColor(const QString & colorName)
{
	m_backgroundColor = colorName;
	setPalette(QPalette(m_backgroundColor));
}

void MgCommandPrompt::setUserTextColor(const QString &colorName)
{
	m_userTextColor=colorName;
}
void MgCommandPrompt::setSystemReturnTextColor(const QString &colorName)
{
	m_systemReturnTextColor=colorName;
}
void MgCommandPrompt::reset()
{
	clear();
	for (int i = 0; i < m_commands.size(); ++i)
		displayCommand(m_commands[i]);
//	insertPlainText(m_newLineChar);
	m_commandsEndCursorPosition = textCursor().position();
}
