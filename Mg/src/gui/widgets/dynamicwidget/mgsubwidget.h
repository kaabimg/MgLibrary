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
#ifndef MGSUBWIDGET_H_
#define MGSUBWIDGET_H_

//MG_INCLUDE_INFO:MgSubWidget

#include <QWidget>

#include <MgCore/MgGlobal>

class QToolBar;

MG_USE_PRIVATE_CLASS(MgSubWidget)

class MgSubWidget : public QWidget
{
	Q_OBJECT
public:
	MgSubWidget(QWidget * w, QWidget*parent=0);//takes ownership of w
	virtual ~MgSubWidget();

	QWidget * contentWidget()const;

Q_SIGNALS:
	void closeRequest();

protected:
	QToolBar * toolBar();


protected Q_SLOTS:
	void onClose();

private:
	MG_PRIVATE_CLASS(MgSubWidget)
	Q_DISABLE_COPY(MgSubWidget)


};

#endif /* MGSUBWIDGET_H_ */
