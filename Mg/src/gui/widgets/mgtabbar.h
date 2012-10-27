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
#ifndef MGTABBAR_H_
#define MGTABBAR_H_


//MG_INCLUDE_INFO:MgTabBar

#include <QtGui/QWidget>
#include <QtCore/QSize>
#include <QtGui/QIcon>
#include <QtCore/QString>
#include <MgCore/MgGlobal>

class QPaintEvent;
class QPainter;
class QMouseEvent;
class QEvent;


MG_USE_PRIVATE_CLASS(MgTabBar);

class MgTabBar : public QWidget
{
    Q_OBJECT

public:
    explicit MgTabBar(Qt::Orientations orientation,QWidget *parent = 0);
    explicit MgTabBar(Qt::Orientations orientation,const QSize & elementSize,QWidget *parent = 0);
    ~MgTabBar();

    bool event(QEvent *event);

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    bool validIndex(int index) const ;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setTabEnabled(int index, bool enable);
    bool isTabEnabled(int index) const;

    void insertTab(int index, const QIcon &icon, const QString &label) ;
    void setEnabled(int index, bool enabled);

    void removeTab(int index) ;

    void setCurrentIndex(int index);
    int currentIndex() const;


    void setTabToolTip(int index, QString toolTip);
    QString tabToolTip(int index) const ;

    QIcon tabIcon(int index) const;
    QString tabText(int index) const;
    int count() const ;
    QRect tabRect(int index) const;

signals:
    void currentChanged(int);

protected slots:
    void emitCurrentIndex();

private:

   QSize tabSizeHint(bool minimum = false) const;
   void paintTab(QPainter *painter, int tabIndex) const;
   void create();

   MG_PRIVATE_CLASS(MgTabBar)

};

#endif /* MGTABBAR_H_ */
