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
#ifndef MGVIEWGRIDLAYOUT_H_
#define MGVIEWGRIDLAYOUT_H_

#include <QGraphicsGridLayout>

class MgRectGraphicsObject;

class MgViewGridLayout : public QGraphicsGridLayout
{
public:
    MgViewGridLayout(Qt::Orientations orientation, int l);
    ~MgViewGridLayout();

    Qt::Orientations flowDirection() const { return m_direction; }

    void setFlowDirection(Qt::Orientations d);
    void setLayoutLength(int l);
    void add(MgRectGraphicsObject *item);
    void remove(MgRectGraphicsObject *item);

    int count() const  { return QGraphicsGridLayout::count(); }
    void invalidate()  { QGraphicsGridLayout::invalidate(); }
    void removeItem(QGraphicsLayoutItem *item);
    void relayout();


    void clearItems();

    void setScene(QGraphicsScene *s)  { m_scene = s; }


private:
    void adjustSceneRect();

    Qt::Orientations m_direction;
    int m_layLength;
    QMap<int, MgRectGraphicsObject *> m_items;
    QGraphicsScene *m_scene;
};

#endif /* MGVIEWGRIDLAYOUT_H_ */
