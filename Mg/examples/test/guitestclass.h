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
#ifndef GUITESTCLASS_H_
#define GUITESTCLASS_H_
#include <QMainWindow>

class QTextEdit;
class QPushButton;

class GuiTestClass : public QMainWindow
{
	Q_OBJECT
public:
	GuiTestClass(QWidget * =0);
	virtual ~GuiTestClass();


	Q_INVOKABLE QTextEdit * textEdit()const;
	Q_INVOKABLE void addText(const QString &);

public Q_SLOTS:
	void onButton1Clicked();
	void onButton2Clicked();
	void onActionTriggered();

private:
	QTextEdit * m_textEdit;
	QPushButton * m_button1, *m_button2;


};

#endif /* GUITESTCLASS_H_ */
