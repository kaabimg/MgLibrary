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
#ifndef MGFADEWIDGET_H_
#define MGFADEWIDGET_H_

//MG_INCLUDE_INFO:MgFadeWidget

#include <QtGui/QWidget>
#include <MgCore/MgGlobal>

MG_USE_PRIVATE_CLASS(MgFadeWidget);

class MgFadeWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor fadeColor READ fadeColor WRITE setFadeColor)
    Q_PROPERTY(int alpha READ alpha WRITE setAlpha)
public:

    MgFadeWidget(QWidget *);
    virtual ~MgFadeWidget();
    QColor fadeColor() const;
    void setFadeColor(const QColor &newColor);

    int alpha()const;
    void setAlpha(int);

protected:
    void paintEvent(QPaintEvent *event);
    void setWidget(QWidget *);

private:

    MG_PRIVATE_CLASS(MgFadeWidget);

};

#endif /* MGFADEWIDGET_H_ */
