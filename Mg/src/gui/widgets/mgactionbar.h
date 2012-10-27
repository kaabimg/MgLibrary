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
#ifndef MGACTIONBAR_H_
#define MGACTIONBAR_H_


//MG_INCLUDE_INFO:MgActionBar

#include <QtGui/QWidget>
#include <QtCore/QHash>
#include <QtCore/QSize>
#include <QtCore/QString>



class MgToolButton;
class QPaintEvent;
class QAction;
class QBoxLayout;

class MgActionBar : public QWidget
{
    Q_OBJECT

public:
    MgActionBar(Qt::Orientations orientation,QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

    void insertAction(int index, QAction *action);
    void addAction(QAction *action);
    void removeAction(const QString &);


    QSize minimumSizeHint() const;

private:

    QHash<QString,MgToolButton*> m_toolButtons;
    QBoxLayout *m_actionsLayout;
    Qt::Orientations m_orientation;

};
#endif /* MGACTIONBAR_H_ */
