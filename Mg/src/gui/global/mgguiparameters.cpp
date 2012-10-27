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
#include "mgguiparameters.h"


bool MgGuiParameters::animationsEnabled = true;

int MgGuiParameters::transparenceAnimationsDuration = 500;
int MgGuiParameters::slideAnimationsDuration = 1000;


float MgGuiParameters::fontSize = 8.5;
int MgGuiParameters::iconSize = 32;


QColor MgGuiParameters::baseColor = Qt::black;
QColor MgGuiParameters::hoverColor = Qt::transparent;
QColor MgGuiParameters::highlightColor = Qt::white;
QColor MgGuiParameters::borderColor = Qt::white;

QColor MgGuiParameters::listViewBaseColor ("#FFFFF0");
QColor MgGuiParameters::listViewHoverColor ("#F5F5F5");
QColor MgGuiParameters::listViewHighlightColor ("#E6E6FA");
QColor MgGuiParameters::listViewborderColor ( 255, 255, 255, 40);
QColor MgGuiParameters::listViewActiveTextColor (Qt::black);
QColor MgGuiParameters::listViewPassiveTextColor (Qt::darkGray);
float MgGuiParameters::listFontSize = 10;
