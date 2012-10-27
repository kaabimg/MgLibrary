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
#include "mgstylehelper.h"


#include <QtGui/QPainter>
#include <QtGlobal>

QColor MgStyleHelper::mgBaseColor = Qt::black;
QColor MgStyleHelper::mgHighlightColor= Qt::white;
QColor MgStyleHelper::mgShadowColor = Qt::transparent;
QColor MgStyleHelper::mgContourColor = Qt::gray;


void MgStyleHelper::drawRoundRect(QPainter& painter,const QRect & rect)
{

	painter.drawRoundedRect(rect,20,20,Qt::RelativeSize);

}


void MgStyleHelper::drawGlassEffect(QPainter * painter,const QRect & rect)
{

	painter->save();
	QLinearGradient grad(rect.topLeft(), rect.topRight());
	grad.setColorAt(0, QColor(255, 255, 255, 140));
	grad.setColorAt(1, QColor(255, 255, 255, 210));
	painter->fillRect(rect.adjusted(0, 0, 0, -1), grad);
	painter->restore();

	//shadows
	painter->setPen(QColor(0, 0, 0, 110));
	painter->drawLine(rect.topLeft() + QPoint(1,-1), rect.topRight() - QPoint(0,1));
	painter->drawLine(rect.bottomLeft(), rect.bottomRight());
	painter->setPen(QColor(0, 0, 0, 40));
	painter->drawLine(rect.topLeft(), rect.bottomLeft());

	//highlights
	painter->setPen(QColor(255, 255, 255, 50));
	painter->drawLine(rect.topLeft() + QPoint(0, -2), rect.topRight() - QPoint(0,2));
	painter->drawLine(rect.bottomLeft() + QPoint(0, 1), rect.bottomRight() + QPoint(0,1));
	painter->setPen(QColor(255, 255, 255, 40));
	painter->drawLine(rect.topLeft() + QPoint(0, 0), rect.topRight());
	painter->drawLine(rect.topRight() + QPoint(0, 1), rect.bottomRight() - QPoint(0, 1));
	painter->drawLine(rect.bottomLeft() + QPoint(0,-1), rect.bottomRight()-QPoint(0,1));


}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


void MgStyleHelper::mgDrawHorizontalGradiant(QPainter * painter , const QRect & rect,const QColor & baseColor
		,int beginAlpha ,int endAlpha )
{
	QLinearGradient linearGrad((rect.topLeft().x()+rect.topRight().x())/2, rect.topLeft().y(),
			(rect.bottomLeft().x()+rect.bottomRight().x())/2, rect.bottomRight().y()

	);

	QColor color(baseColor);
	color.setAlpha(beginAlpha);
	linearGrad.setColorAt(0, color);
	color.setAlpha(endAlpha);
	linearGrad.setColorAt(1, color);
	painter->fillRect(rect,linearGrad);


}
void MgStyleHelper::mgDrawVericalGradiant(QPainter * painter , const QRect & rect,const QColor & baseColor
		,int beginAlpha ,int endAlpha )
{

	QLinearGradient linearGrad(rect.topLeft().x(), (rect.topLeft().y()+rect.bottomLeft().y())/2,
			rect.topRight().x(), (rect.topLeft().y()+rect.bottomLeft().y())/2

	);

	QColor color(baseColor);
	color.setAlpha(beginAlpha);
	linearGrad.setColorAt(0, color);
	color.setAlpha(endAlpha);
	linearGrad.setColorAt(1, color);
	painter->fillRect(rect,linearGrad);
}





