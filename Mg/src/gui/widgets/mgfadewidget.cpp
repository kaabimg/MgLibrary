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
#include "mgfadewidget.h"

#include <QtGui/QPainter>

struct MgFadeWidgetPrivate
{
	MgFadeWidgetPrivate()
	{
		fadeColor = Qt::white;
		currentAlpha = 0;
	}
    QColor fadeColor;
    int currentAlpha;
    int duration;
};


MgFadeWidget::MgFadeWidget(QWidget * parent)
    : QWidget( parent),d_ptr(new MgFadeWidgetPrivate)
{
	setWidget(parent);
	 setAttribute(Qt::WA_DeleteOnClose);
}
MgFadeWidget::~MgFadeWidget()
{
	delete d_ptr;
}

void MgFadeWidget::setWidget(QWidget * w)
{
	d_ptr->fadeColor =  w->palette().window().color();
	d_ptr->currentAlpha = 0;
	if(size()!=w->size())
		resize(w->size());

}

QColor MgFadeWidget::fadeColor() const { return d_ptr->fadeColor; }
void MgFadeWidget::setFadeColor(const QColor &newColor) { d_ptr->fadeColor = newColor; }

int MgFadeWidget::alpha()const
{
	return d_ptr->currentAlpha;
}

void MgFadeWidget::setAlpha(int newAlpha)
{
	d_ptr->currentAlpha = newAlpha;
	update();
}


void MgFadeWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    QColor semiTransparentColor = d_ptr->fadeColor;
    semiTransparentColor.setAlpha(d_ptr->currentAlpha);
    painter.fillRect(rect(), semiTransparentColor);
}
