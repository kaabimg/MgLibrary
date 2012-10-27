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
#ifndef MGTABWIDGET_H_
#define MGTABWIDGET_H_

//MG_INCLUDE_INFO:MgTabWidget

#include <QtGui/QWidget>
#include <MgCore/MgGlobal>


MG_USE_PRIVATE_CLASS(MgTabWidget);

class MgTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MgTabWidget(Qt::Orientations tabOrientation,QWidget *parent = 0);
    explicit MgTabWidget(Qt::Orientations orientation,const QSize & elementSize,QWidget *parent = 0);
    ~MgTabWidget();
    void insertTab(int index, QWidget *tab, const QIcon &icon, const QString &label);
    int appendTab(QWidget *tab, const QIcon &icon, const QString &label);
    void removeTab(int index);
    int tabCount()const;


    void setBackgroundBrush(const QBrush &brush);
    void addCornerWidget(QWidget *widget);
    void insertCornerWidget(int pos, QWidget *widget);
    int cornerWidgetCount() const;
    void setTabToolTip(int index, const QString &toolTip);

    int currentIndex() const;

    void setTabEnabled(int index, bool enable);
    bool isTabEnabled(int index) const;

public Q_SLOTS:
    void registerTemporaryWidget(const QString &,QWidget*,const char * closeSignal);
    void registerTemporaryWidget(const QString &,QWidget*,const char * showSignal,const char * closeSignal);

    void showTemporaryWidget(const QString &);
    void hideTemporaryWidget(const QString &);


Q_SIGNALS:
    void currentChanged(int index);
    void temporaryWidgetShown(const QString&);
    void temporaryWidgetHidden(const QString&);


public slots:
    void setCurrentIndex(int index);
    void setSelectionWidgetHidden(bool hidden);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void showWidget(int index);

private:
    void create();
    MG_PRIVATE_CLASS(MgTabWidget);
};

#endif /* MGTABWIDGET_H_ */
