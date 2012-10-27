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
#ifndef MGCOMMANDLINE_H_
#define MGCOMMANDLINE_H_

//MG_INCLUDE_INFO:MgCommandLine

#include <QLineEdit>
class QStringListModel;
class MgScriptEngine;
class QPushButton;


class MgCommandLine : public QLineEdit
{
	Q_OBJECT
public:
	MgCommandLine(QWidget * parent = 0);
	virtual ~MgCommandLine();

	MgScriptEngine * scriptEngine()const{return m_scriptEngine;}
	void setScriptEngine(MgScriptEngine * scriptEngine);
protected Q_SLOTS:
	void updateCompletion();
	void insertText(const QString &);
protected:
	void focusInEvent(QFocusEvent *);
	void keyPressEvent(QKeyEvent * );

private:
	QStringListModel * m_completionModel;
	MgScriptEngine * m_scriptEngine;
	QCompleter* m_completer;
	QString m_prefix;
};

class MgCommandLineWidget : public QWidget
{
	Q_OBJECT
public:
	MgCommandLineWidget(QWidget * parent = 0);
	virtual ~MgCommandLineWidget();
	MgScriptEngine * scriptEngine()const;
	void setScriptEngine(MgScriptEngine * scriptEngine);
	void setExecButtonIcon(const QIcon &);
private:
	MgCommandLine * m_commandLine;
	QPushButton * m_execButton;

};



#endif /* MGCOMMANDLINE_H_ */
