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
#ifndef MGLISTVIEW_H_
#define MGLISTVIEW_H_

//MG_INCLUDE_INFO:MgListView


#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QIcon>
#include <QtCore/QString>
#include <MgCore/MgGlobal>

class QPaintEvent;
class QPainter;
class QMouseEvent;
class QEvent;
class MgFadeElement;
class QResizeEvent;


MG_USE_PRIVATE_CLASS(MgListView);

class MgListView : public QWidget
{
	Q_OBJECT

public:
	explicit MgListView(QWidget *parent = 0);
	explicit MgListView(int  elementHeigth,QWidget *parent = 0);
	virtual ~MgListView();

	QSize sizeHint() const;
	QSize minimumSizeHint() const;

	void setElementEnabled(int index, bool enable);
	bool isElementEnabled(int index) const;

	void insertElement(int index, MgFadeElement *) ;
	void setEnabled(int index, bool enabled);

	void removeElement(int index) ;

	void setCurrentIndex(int index);
	int currentIndex() const;


	int count() const ;

	QScrollArea * embedInScrollArea();

Q_SIGNALS:
	void currentChanged(QString);
	void elementClicked(QString);
	void elementDoubleClicked(QString);

protected Q_SLOTS:
	void emitCurrentIndex();


protected:
	bool event(QEvent *event);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mouseDoubleClickEvent (QMouseEvent *);
	void resizeEvent ( QResizeEvent *  );

private:
	QRect elementRect(int index) const;
	bool validIndex(int index) const ;
	void paintElement(QPainter *painter, int ) const;
	void paintElementContent(QPainter *painter,const QRect &,MgFadeElement*)const;
	void create();


	MG_PRIVATE_CLASS(MgListView)

};

#endif /* MGLISTVIEW_H_ */
