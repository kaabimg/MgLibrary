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
#ifndef MGDYNAMICWIDGET_H_
#define MGDYNAMICWIDGET_H_


//MG_INCLUDE_INFO:MgDynamicWidget

#include <QWidget>
#include <MgCore/MgGlobal>

class MgSubWidget;

MG_USE_PRIVATE_CLASS(MgDynamicWidget)

class MgDynamicWidget : public QWidget
{
	Q_OBJECT
public:
	MgDynamicWidget(QWidget * parent=0);
	virtual ~MgDynamicWidget();

public Q_SLOTS:
	void setCentralWidget(QWidget *);

     void registerTemporaryWidget(const QString &,QWidget*,const char * closeSignal);
     void registerTemporaryWidget(const QString &,QWidget*,const char * showSignal,const char * closeSignal);//for task viewing

    void showTemporaryWidget(const QString &);
    void hideTemporaryWidget(const QString &);

Q_SIGNALS:
	void widgetShown(const QString &);
	void widgetHidden(const QString &);

protected Q_SLOTS:
	void onCloseRequest();
	void onSubWidgetCloseRequest();

    void autoShowRequest();
    void autoCloseRequest();


private:
	MG_PRIVATE_CLASS(MgDynamicWidget)
	Q_DISABLE_COPY(MgDynamicWidget)

};

#endif /* MGDYNAMICWIDGET_H_ */
