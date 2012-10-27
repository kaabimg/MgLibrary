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
#include "mgviewgridlayout.h"


#include "mgrectgraphicsobject.h"

#include <QGraphicsScene>
#include <QDebug>

/**************************************************************************************************
 **************************************************************************************************/
MgViewGridLayout::MgViewGridLayout(Qt::Orientations d, int l)
    : QGraphicsGridLayout(),
      m_direction(d),
      m_layLength(l)
{}

MgViewGridLayout::~MgViewGridLayout(){}

void MgViewGridLayout::setFlowDirection(Qt::Orientations d)
{
    if (m_direction == d)
        return;

    m_direction = d;
    relayout();
}

void MgViewGridLayout::setLayoutLength(int l)
{
    if (m_layLength == l)
        return;

    m_layLength = l;
    relayout();
}

void MgViewGridLayout::add(MgRectGraphicsObject *item)
{
    if (m_items.contains(item->id()))
        return;

    m_items.insert(item->id(), item);
    QList<MgRectGraphicsObject *> list = m_items.values();
    int insIndex = list.indexOf(item);

    for (int i = count() - 1; i >= insIndex; i--)
    {
        removeItem(list.at(i + 1));
        int newIndex = i + 1;
        int row = newIndex / m_layLength;
        int column = newIndex - row * m_layLength;
        if (m_direction == Qt::Horizontal)
            qSwap(row, column);
        QGraphicsGridLayout::addItem(list.at(i + 1), row, column);
    }

    int row = insIndex / m_layLength;

    int column = insIndex - row * m_layLength;

    if (m_direction == Qt::Horizontal)
        qSwap(row, column);

//    QGraphicsGridLayout::addItem(item, row, column);

//    adjustSceneRect();
}


void MgViewGridLayout::remove(MgRectGraphicsObject *item)
{
    if (!m_items.contains(item->id()))
        return;

    QList<MgRectGraphicsObject *> list = m_items.values();
    int delIndex = list.indexOf(item);
    removeItem(item);
    for (int i = delIndex + 1; i < list.count(); i++)
    {
        int newIndex = i - 1;
        removeItem(list.at(i));
        int row = newIndex / m_layLength;
        int column = newIndex - row * m_layLength;
        if (m_direction == Qt::Horizontal)
            qSwap(row, column);
        QGraphicsGridLayout::addItem(list.at(i), row, column);
    }
    delete m_items.take(item->id());

    adjustSceneRect();
}

/**************************************************************************************************
 **************************************************************************************************/
void MgViewGridLayout::relayout()
{
    QList<MgRectGraphicsObject *> list = m_items.values();
    for (int i = 0; i < list.count(); i++)
    {
        removeItem(list.at(i));
    }

    for (int i = 0; i < list.count(); i++)
    {
        int row = i / m_layLength;
        int column = i - row * m_layLength;
        if (m_direction == Qt::Horizontal)
            qSwap(row, column);
        QGraphicsGridLayout::addItem(list.at(i), row, column);
    }

    for (int i = 0; i < columnCount(); ++i)
    {
        setColumnMinimumWidth(i, 0);
        setColumnMaximumWidth(i, 0);
    }
    for (int i = 0; i < rowCount(); ++i)
    {
        setRowMinimumHeight(i, 0);
        setRowMaximumHeight(i, 0);
    }

    adjustSceneRect();
}


void MgViewGridLayout::clearItems()
{
	qDeleteAll(m_items);
	m_items.clear();
}

/**************************************************************************************************
 **************************************************************************************************/
void MgViewGridLayout::removeItem(QGraphicsLayoutItem *item)
{
    for (int i = count() - 1; i >= 0; --i)
    {
        QGraphicsLayoutItem *itemTmp = itemAt(i);
        if (item == itemTmp)
        {
            removeAt(i);
            invalidate();
            return;
        }
    }
}

/**************************************************************************************************
 **************************************************************************************************/
void MgViewGridLayout::adjustSceneRect()
{
    qreal lmargin, tmargin, rmargin, bmargin;
    getContentsMargins(&lmargin, &tmargin, &rmargin, &bmargin);
    qreal width = columnCount() * horizontalSpacing() + lmargin + rmargin;
    qreal height = rowCount() * verticalSpacing() + tmargin + bmargin;
    m_scene->setSceneRect(0, 0, width, height);
}
