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
#ifndef MGNAVIGATIONBAR_H_
#define MGNAVIGATIONBAR_H_

//MG_INCLUDE_INFO:MgNavigationBar

#include <QToolBar>

class MgNavigationBar : public QToolBar
{
	Q_OBJECT
public:
	enum NavigationType{Backward,Forward,BackwardAndForward};
	MgNavigationBar(NavigationType,QWidget * =0);
	virtual ~MgNavigationBar();

Q_SIGNALS:
	void backwardRequest();
	void forwardRequest();

};

class MgWidgetWithNavigationBar : public QWidget
{
	Q_OBJECT
public:

	MgWidgetWithNavigationBar(QWidget * emW,MgNavigationBar::NavigationType,QWidget * parent=0);
	MgNavigationBar * navigationBar()const;

private:
	MgNavigationBar * m_navigationBar;
};

#endif /* MGNAVIGATIONBAR_H_ */
