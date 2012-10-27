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
#ifndef MGSTYLEHELPER_H_
#define MGSTYLEHELPER_H_


#include <QtCore/QRect>
#include <QtGui/QColor>

class QPainter;

struct MgStyleHelper
{

	static QColor mgBaseColor;
	static QColor mgHighlightColor;
	static QColor mgShadowColor;
	static QColor mgContourColor;
///////////////////////////////


	static void drawRoundRect(QPainter& , const QRect &);
	static void drawGlassEffect(QPainter * , const QRect &);
//////////////////////////////////////////////////////////////////////////////////////////////////////////


	static void mgDrawHorizontalGradiant(QPainter * , const QRect &,const QColor &,int beginAlpha = 120,int endAlpha = 250);
	static void mgDrawVericalGradiant(QPainter * , const QRect &,const QColor &,int beginAlpha = 120,int endAlpha = 250);
};

#endif /* MGSTYLEHELPER_H_ */
