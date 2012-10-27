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
#ifndef MGCOMMANDPROMPT_H_
#define MGCOMMANDPROMPT_H_

//MG_INCLUDE_INFO:MgCommandPrompt

#include <QTextEdit>
#include <QString>
#include <QList>
#include <QPalette>

class MgScriptEngine;


/*************************************************************************************************************/
class MgCommandPrompt : public QTextEdit
{
    Q_OBJECT
    Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QString userTextColor READ userTextColor WRITE setUserTextColor)
    Q_PROPERTY(QString systemReturnTextColor READ systemReturnTextColor WRITE setSystemReturnTextColor)

    enum MgCommandPromptOperation{CommandRequest,CompletionRequest};

    struct Command
    {
    	QString userCommand;
    	QString systemResponse;
    };
public:
    MgCommandPrompt(QWidget *parent = 0);
    virtual ~MgCommandPrompt();


    QString backgroundColor()const{return m_backgroundColor.name();}
	void setBackgroundColor(const QString &);

	QString userTextColor()const{return m_userTextColor.name();}
	void setUserTextColor(const QString &);

	QString systemReturnTextColor()const{return m_systemReturnTextColor.name();}
	void setSystemReturnTextColor(const QString &);

	MgScriptEngine * scriptEngine()const{return m_scriptEngine;}
	void setScriptEngine(MgScriptEngine * scriptEngine);

public Q_SLOTS:
	void reset();

	void setStyle(const QString & userColor,const QString & systemColor,const QString & backgroundColor,qreal opacity=1.)
	{
		setUserTextColor(userColor);
		setSystemReturnTextColor(systemColor);
		setBackgroundColor(backgroundColor);
		setWindowOpacity(opacity);
	}
protected:
	void keyPressEvent(QKeyEvent * e);
	void displayCommand(Command *);
	void onEnterKey();
	void onTabKey();

	void onPreviousCommand();
	void onNextCommand();

	QString currentCommand()const;
	void setCurrentCommand(const QString&);

	void execCommand(const QString &);
	void execCompletionRequest(const QString &);

	void clearCurrentLine();

protected Q_SLOTS:
	void addCommand(const QString &,const QString &);

private:
	QList<Command * > m_commands;
	int m_commandsEndCursorPosition,m_commandsIndex;
	QChar m_newLineChar;
	QColor m_userTextColor,m_systemReturnTextColor,m_backgroundColor;
	MgScriptEngine * m_scriptEngine;
};

#endif /* MGCOMMANDPROMPT_H_ */
