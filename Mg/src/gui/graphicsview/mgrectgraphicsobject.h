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
#ifndef MGRECTGRAPHICSOBJECT_H_
#define MGRECTGRAPHICSOBJECT_H_


#include <QtGui/QGraphicsWidget>
#include <QtCore/QString>
#include <MgCore/MgGlobal>
class QGraphicsSceneMouseEvent;

#define ITEM_WIDTH 100
#define ITEM_HEIGHT 100

MG_USE_PRIVATE_CLASS(MgRectGraphicsObject);

class MgRectGraphicsObject: public QGraphicsWidget
{
    Q_OBJECT

public:

    MgRectGraphicsObject(int,  QGraphicsItem * parent = 0);
    ~MgRectGraphicsObject();

    int id()const;
    QRectF boundingRect() const ;
    void setGeometry(const QRectF &rect);
    const void * userData()const;


public Q_SLOTS:

	void setBackItemOpacity(qreal);
	void setColor(const QColor &);
	void setBorderColor(const QColor &);
	void setSelectionColor(const QColor &);
	void setIcon(const QIcon &);
	void setText(const QString &);
	void setTitle(const QString &);
	void update();
	void setUserData(const void *);
void setItemSelected(bool);
	bool isItemSelected()const;

Q_SIGNALS:
	void selected(bool,bool);
	void multiSelected();


protected:
    QLinearGradient createGradientFromColor(const QColor &c);
    void moveEvent(QGraphicsSceneMoveEvent *event);
    void mousePressEvent ( QGraphicsSceneMouseEvent * );

private:

	MG_PRIVATE_CLASS(MgRectGraphicsObject);
};


#endif /* MGRECTGRAPHICSOBJECT_H_ */
