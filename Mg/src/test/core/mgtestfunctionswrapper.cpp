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
#include "mgtestfunctionswrapper.h"

#include <QTest>
#include <QDebug>


MgTestFunctionsWrapper::MgTestFunctionsWrapper(QObject * parent)
	:QObject(parent)
{
	setObjectName("test_functions_wrapper");
}


void MgTestFunctionsWrapper::sleep(int ms)
{
	QTest::qSleep(ms);
}

void MgTestFunctionsWrapper::wait(int ms)
{
	QTest::qWait(ms);
}
void MgTestFunctionsWrapper::verify(bool cond,const QString & text)
{
	qDebug()<<text<<cond;
}
void MgTestFunctionsWrapper::mouseRightClick(QWidget * w)
{
	QTest::mouseClick(w,Qt::RightButton);
}
void MgTestFunctionsWrapper::mouseLeftClick(QWidget * w)
{
	QTest::mouseClick(w,Qt::LeftButton);
}
void MgTestFunctionsWrapper::mouseDoubleClick(QWidget * w)
{
	QTest::mouseDClick(w,Qt::LeftButton);
}
