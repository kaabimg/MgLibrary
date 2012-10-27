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
#include "mgstylesheets.h"

#define TO_STRING(a) #a

QString MgStyleSheets::tabWidget()
{
	return  "QTabWidget::pane {"
			"border-top: 2px solid rgb(180,180,180);"
			"position: absolute;"
			"top: -0.8em;"
			"padding-top: 0.8em;"
			"}"

			"QTabWidget::tab-bar {alignment: center;}"

			"QTabBar::tab {color: white;"
			"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(116, 116, 118), stop:1 rgb(59, 57, 60));"
			"border: 2px solid rgb(180,180,180);"
			"border-radius: 4px;"
			"padding: 4px;"
			"margin-left: 0.25em;"
			"margin-right: 0.25em;}"

			"QTabBar::tab:selected, QTabBar::tab:hover {"
			"color: black;"
			"background: rgb(180,180,180);"
			"}"

			"QTabBar::tab:hover {border-color: rgb(75,75,75);}"
//			"QTabBar {"+ horizontalBarBackgroundGradient()+";}"
	;
}

QString MgStyleSheets::tabBar()
{
	return 	"QTabBar::tab {"
			"color: white;"
			"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(116, 116, 118), stop:1 rgb(59, 57, 60));"
//			"border: 2px solid rgb(180,180,180);"
			"border-radius: 4px;"
//			"padding: 4px;"
			"margin-left: 0.75em;"
			"margin-right: 0.75em;"
			"}"
			"QTabBar::tab:selected, QTabBar::tab:hover {"
			"color: black;"
			"background: rgb(150,150,150,100);"
			"border: 2px solid rgb(0,0,0);"
			"border-radius: 4px;"
			"}"
			"QTabBar::tab:hover {border-color: rgb(75,75,75);}"
			"QTabBar {"+ horizontalBarBackgroundGradient()+";}"
			;
}

QString MgStyleSheets::toolBar()
{
	return QString("QToolBar{%1;}").arg(horizontalBarBackgroundGradient());
}



QString MgStyleSheets::pushButton()
{
	return  "QPushButton {"
			" background-color: rgb(75,75,75,150); color: white;"
			"border-width: 2px;"
			"border-radius: 10px;"
			"border-width: 1px;"
			"border-style: solid;"
			"border-color: beige;"
			"min-width: 10em;"
			"padding: 6px;"
			"} "
			"QPushButton::hover {background-color: rgb(75,75,75,100); }"
			"QPushButton:checked {background-color: rgb(55,55,55); } "
			"QPushButton:pressed {background-color: rgb(55,55,55);} "
			;
}


QString MgStyleSheets::toolBox()
{
	return "QToolBox::tab {"
			+horizontalBarBackgroundGradient()+";"
//			"border-radius: 5px;"
            "color: white;"
     	 	"}"
     	 	"QToolBox::tab:selected {"
			"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0,0,0,50), stop:1 rgb(0,0,0,120))"
     	 	"}"
     	 	"QToolBox{background-color: rgb(75,75,75)}"
			;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString MgStyleSheets::verticalBarBackgroundGradient()
{
	return "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(0,0,0,170), stop:1 rgb(0,0,0,250))";
}
QString MgStyleSheets::horizontalBarBackgroundGradient()
{
	return "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(0,0,0,170), stop:1 rgb(0,0,0,250))";
}



