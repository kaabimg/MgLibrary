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
#include "mgpushbutton.h"

#include <QtGui/QAction>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainterPath>
#include <QtGui/QPainter>
#include <QtCore/QEvent>
#include <QtCore/QRect>
#include "mgstylehelper.h"

MgPushButton::MgPushButton(QWidget *parent ):QPushButton(parent), m_hovered(false),m_pressed(false), m_opacity(.6),
m_roundness(0)
{

}
MgPushButton::MgPushButton(QAction * action,QWidget *parent ):QPushButton(parent), m_hovered(false),m_pressed(false)
, m_opacity(.6),m_roundness(0)
{
	setText(action->text());
	setIcon(action->icon());
	setToolTip(action->toolTip());

}


void MgPushButton::paintEvent(QPaintEvent * pe)
{

	Q_UNUSED(pe);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	//test for state changes
	QColor button_color;
	if(this->isEnabled())
	{
		m_hovered ? button_color = MgStyleHelper::mgHighlightColor : button_color = MgStyleHelper::mgBaseColor;

		if(m_pressed)
		{
			button_color = MgStyleHelper::mgBaseColor.darker(250);
		}
	}
	else
	{
		button_color = QColor(50, 50, 50);
	}

	QRect button_rect = this->geometry();

	//outline
	painter.setPen(QPen(QBrush(Qt::black), 2.0));
	QPainterPath outline;
	outline.addRoundedRect(0, 0, button_rect.width(), button_rect.height(), m_roundness, m_roundness);
	painter.setOpacity(m_opacity);
	painter.drawPath(outline);

	//gradient
	QLinearGradient gradient(0, 0, 0, button_rect.height());
	gradient.setSpread(QGradient::ReflectSpread);
	gradient.setColorAt(0.0, button_color);
	gradient.setColorAt(0.4, button_color.lighter(50));
	gradient.setColorAt(0.6, button_color.lighter(50));
	gradient.setColorAt(1.0, button_color);

	QBrush brush(gradient);
	painter.setBrush(brush);
	painter.setPen(QPen(QBrush(button_color), 2.0));

	//main button
	QPainterPath painter_path;
	painter_path.addRoundedRect(1, 1, button_rect.width() - 2, button_rect.height() - 2, m_roundness, m_roundness);
	painter.setClipPath(painter_path);

	painter.setOpacity(m_opacity);
	painter.drawRoundedRect(1, 1, button_rect.width() - 2, button_rect.height() - 2, m_roundness, m_roundness);

	//glass highlight
	painter.setBrush(QBrush(MgStyleHelper::mgHighlightColor));
	painter.setPen(QPen(QBrush(Qt::white), 0.01));
	painter.setOpacity(0.30);
	painter.drawRect(1, 1, button_rect.width() - 2, (button_rect.height() / 2) - 2);

	//text
	QString text = this->text();
	if(!text.isNull())
	{
		QFont font = this->font();
		painter.setFont(font);
		painter.setPen(Qt::white);
		painter.setOpacity(1.0);
		painter.drawText(0, 0, button_rect.width(), button_rect.height(), Qt::AlignCenter, text);
	}

	//icon
	QIcon icon = this->icon();
	if(!icon.isNull())
	{
		QSize icon_size = this->iconSize();
		QRect icon_position = this->calculateIconPosition(button_rect, icon_size);
		painter.setOpacity(1.0);
		painter.drawPixmap(icon_position, QPixmap(icon.pixmap(icon_size)));
	}
}

void MgPushButton::enterEvent(QEvent * e)
{
	m_hovered = true;
	this->repaint();
	QPushButton::enterEvent(e);
}
void MgPushButton::leaveEvent(QEvent * e)
{
	m_hovered = false;
	this->repaint();
	QPushButton::leaveEvent(e);
}

void MgPushButton::mousePressEvent(QMouseEvent * e)
{
	m_pressed = true;
	this->repaint();
	QPushButton::mousePressEvent(e);
}
void MgPushButton::mouseReleaseEvent(QMouseEvent * e)
{

	m_pressed = false;
	this->repaint();

	QPushButton::mouseReleaseEvent(e);
}


QRect MgPushButton::calculateIconPosition(QRect button_rect, QSize icon_size)
{
	int x = (button_rect.width() - icon_size.width()) / 2;
	int y = (button_rect.height() - icon_size.height()) / 2;
	int width = icon_size.width();
	int height = icon_size.height();

	QRect icon_position;
	icon_position.setX(x);
	icon_position.setY(y);
	icon_position.setWidth(width);
	icon_position.setHeight(height);

	return icon_position;
}
