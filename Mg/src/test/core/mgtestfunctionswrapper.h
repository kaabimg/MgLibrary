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
#ifndef MGTESTFUNCTIONSWRAPPER_H_
#define MGTESTFUNCTIONSWRAPPER_H_

//MG_INCLUDE_INFO:MgTestFunctionsWrapper

#include <QObject>
class QTextEdit;
class QLineEdit;
class MgTestFunctionsWrapper : public QObject
{
	Q_OBJECT
public:
	MgTestFunctionsWrapper(QObject * =0);

public Q_SLOTS:

	void sleep(int ms);
	void wait(int ms);
	void verify(bool,const QString &);
	void mouseRightClick(QWidget *);
	void mouseLeftClick(QWidget *);
	void mouseDoubleClick(QWidget *);
};

#endif /* MGTESTFUNCTIONSWRAPPER_H_ */
