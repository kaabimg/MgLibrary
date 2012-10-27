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
#include <QApplication>

//========================

#include <MgGui/MgObjectPropertiesEditor>

#include "testobject.h"

//================================================================================

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TestObject obj;

	MgObjectPropertiesEditor editor;
	editor.setObject(&obj);
	editor.show();

	return a.exec();
}
