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
#ifndef MGGUIPARAMETERS_H_
#define MGGUIPARAMETERS_H_
#include <QtGui/QColor>



class MgGuiParameters
{
public:

	static bool animationsEnabled;
	static int transparenceAnimationsDuration ;
	static int slideAnimationsDuration;

	static float fontSize ;
	static int iconSize ;



	static QColor baseColor;
	static QColor hoverColor;
	static QColor highlightColor;
	static QColor borderColor;

	static QColor listViewBaseColor;
	static QColor listViewHoverColor;
	static QColor listViewHighlightColor;
	static QColor listViewborderColor;
	static QColor listViewActiveTextColor;
	static QColor listViewPassiveTextColor;
	static float listFontSize;

};




#endif /* MGGUIPARAMETERS_H_ */
