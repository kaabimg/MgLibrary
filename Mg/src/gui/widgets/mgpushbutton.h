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
#ifndef MGPUSHBUTTON_H_
#define MGPUSHBUTTON_H_


//MG_INCLUDE_INFO:MgPushButton

#include <QtGui/QPushButton>

class QAction;
class QEvent;
class QMouseEvent;


class MgPushButton : public QPushButton
{
	Q_OBJECT
public:
	MgPushButton(QWidget *parent = 0);
	MgPushButton(QAction * action,QWidget *parent = 0);

protected:
   void paintEvent(QPaintEvent * pe);

   void enterEvent(QEvent * e);
   void leaveEvent(QEvent * e);

   void mousePressEvent(QMouseEvent * e);
   void mouseReleaseEvent(QMouseEvent * e);

private:
   QRect calculateIconPosition(QRect button_rect, QSize icon_size);

private:
   bool m_hovered;
   bool m_pressed;
   qreal m_opacity;
   int m_roundness;

};

#endif /* MGPUSHBUTTON_H_ */
