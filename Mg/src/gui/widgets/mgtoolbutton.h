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
#ifndef MGTOOLBUTTON_H_
#define MGTOOLBUTTON_H_

//MG_INCLUDE_INFO:MgToolButton

#include <QtGui/QToolButton>

class MgToolButton : public QToolButton
{
    Q_OBJECT

    Q_PROPERTY(float fader READ fader WRITE setFader)

public:
    MgToolButton(Qt::Orientations orientation,QWidget *parent = 0);
    MgToolButton(Qt::Orientations orientation,QAction * action,QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);
    bool event(QEvent *e);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;


    float fader() { return m_fader; }
    void setFader(float value) { m_fader = value; update(); }

    void forceVisible(bool visible);

private slots:
    void actionChanged();

private:
    bool m_hasForceVisible;
    float m_fader;
    Qt::Orientations m_orientation;
};


#endif /* MGTOOLBUTTON_H_ */
