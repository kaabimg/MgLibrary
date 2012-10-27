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
#include "mgrectgraphicsobject.h"

#include <QtGui/QPen>
#include <QtGui/QFontMetricsF>
#include <QtGui/QGraphicsDropShadowEffect>
#include <QtGui/QGraphicsSceneContextMenuEvent>
#include <QtGui/QMenu>
#include <QtCore/QVariant>
#include <QtGui/QGraphicsScene>
#include <QtGui/QApplication>
#include <QtGui/QStyle>
#include <QtGui/QGraphicsSceneMouseEvent>

#include <QDebug>


struct MgRectGraphicsObjectPrivate
{
    QGraphicsPathItem *backItem;
    QGraphicsTextItem *title;
    QGraphicsWidget *imgContainer;
    QGraphicsPixmapItem *img;
    QGraphicsTextItem *message;
    QColor color,borderColor;
    static QColor selectionColor;
    const void *userData;
    int id;
    bool selected;
};

QColor MgRectGraphicsObjectPrivate::selectionColor("#FFD700");

MgRectGraphicsObject::MgRectGraphicsObject(int id,QGraphicsItem *parent)
: QGraphicsWidget(parent),d_ptr(new MgRectGraphicsObjectPrivate)
{
	setObjectName(QString::number(id));
	d_ptr->id = id;
	d_ptr->selected = false;
	setCacheMode(QGraphicsItem::ItemCoordinateCache);

	d_ptr->backItem = new QGraphicsPathItem;
	QPainterPath path;
	path.addRoundedRect(0, 0, ITEM_WIDTH, ITEM_HEIGHT, 15, 15);
	d_ptr->backItem->setPath(path);
	d_ptr->backItem->setParentItem(this);

	setVisible(false);
	resize(ITEM_WIDTH, ITEM_HEIGHT);


	setTransformOriginPoint(ITEM_WIDTH / 2.0, ITEM_HEIGHT / 2.0);

	QString testname ("Test name");

	d_ptr->title = new QGraphicsTextItem(this);
	d_ptr->title->setTextInteractionFlags(Qt::NoTextInteraction);
	d_ptr->title->setDefaultTextColor(Qt::white);
	QFont f("Monotype", 9, QFont::DemiBold);
	QFontMetricsF fm(f);
	if (fm.width(testname) >= ITEM_WIDTH - 10)
	{
		d_ptr->title->setTextWidth(ITEM_WIDTH - 10);
	}
	d_ptr->title->setFont(f);
	d_ptr->title->setPos(geometry().width() / 2 - d_ptr->title->boundingRect().width() / 2, 2);

	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
	shadow->setBlurRadius(4);
	shadow->setOffset(2, 3);
	shadow->setColor(QColor(50, 50, 50));
	d_ptr->title->setGraphicsEffect(shadow);

	d_ptr->imgContainer = new QGraphicsWidget(this);
	d_ptr->img = new QGraphicsPixmapItem(d_ptr->imgContainer);
	d_ptr->img->setPos(0, 0);

	QFont f2("Monotype", 8/*, QFont::DemiBold*/);
//	QFont f3("Monotype", 14, QFont::DemiBold);

	d_ptr->message = new QGraphicsTextItem(this);
	d_ptr->message->setTextInteractionFlags(Qt::NoTextInteraction);
	d_ptr->message->setFont(f2);
	d_ptr->message->setDefaultTextColor(Qt::white);

	setBorderColor(Qt::gray);
//	setText("the text");
//	setTitle("the title");
//	setToolTip("the tool tip");

	d_ptr->userData = NULL;
}

int MgRectGraphicsObject::id()const
{
	return d_ptr->id;
}

/**************************************************************************************************
 **************************************************************************************************/
MgRectGraphicsObject::~MgRectGraphicsObject()
{

}

/**************************************************************************************************
 **************************************************************************************************/
QLinearGradient MgRectGraphicsObject::createGradientFromColor(const QColor &c)
{
	QLinearGradient linearGrad(QPointF(d_ptr->backItem->boundingRect().width() * 0.42, 0),
			QPointF(d_ptr->backItem->boundingRect().width() * 0.76, d_ptr->backItem->boundingRect().height()));
	QColor dark;
	dark.setCmyk(c.cyan(), c.magenta(), c.yellow(), 180);
	linearGrad.setColorAt(0, dark);
	linearGrad.setColorAt(1, c);
	return linearGrad;
}


void MgRectGraphicsObject::setBackItemOpacity(qreal o)
{
	d_ptr->backItem->setOpacity(o);
}

void MgRectGraphicsObject::setColor(const QColor & color)
{
	d_ptr->color  = color;
}
void MgRectGraphicsObject::setBorderColor(const QColor & color)
{
	d_ptr->borderColor  = color;
}

void MgRectGraphicsObject::setSelectionColor(const QColor & color)
{
	d_ptr->selectionColor  = color;
}
void MgRectGraphicsObject::setIcon(const QIcon & icon)
{
	d_ptr->img->setPixmap(icon.pixmap(32,32));
}
void MgRectGraphicsObject::setText(const QString & text)
{
	d_ptr->message->setPlainText(text);
}
void MgRectGraphicsObject::setTitle(const QString & title)
{
	d_ptr->title->setPlainText(title);
}

void MgRectGraphicsObject::setItemSelected(bool selected)
{
	d_ptr->selected = selected;
}
bool MgRectGraphicsObject::isItemSelected()const
{
	return d_ptr->selected;
}


void MgRectGraphicsObject::update()
{
	qreal imgContainerX = d_ptr->backItem->boundingRect().width() / 2 - d_ptr->img->boundingRect().width() / 2;
	qreal imgContainerY = d_ptr->backItem->boundingRect().height() / 2 - d_ptr->img->boundingRect().height() / 2 + 5;

	d_ptr->imgContainer->setPos(imgContainerX, imgContainerY);

	d_ptr->imgContainer->setTransformOriginPoint(d_ptr->img->boundingRect().width() / 2
			, d_ptr->img->boundingRect().height() / 2);

	d_ptr->backItem->setPen(QPen(QColor(
			isItemSelected() ? d_ptr->selectionColor :
			d_ptr->borderColor), 2));

	d_ptr->backItem->setBrush(createGradientFromColor(d_ptr->color));

	d_ptr->message->setPos(d_ptr->backItem->boundingRect().width() / 2 - d_ptr->message->boundingRect().width() / 2,
			d_ptr->imgContainer->pos().y() + d_ptr->img->boundingRect().height() + 1);
}


void MgRectGraphicsObject::moveEvent(QGraphicsSceneMoveEvent *event)
{
	QGraphicsWidget::moveEvent(event);

	if (!isVisible())
		setVisible(true);
}

void MgRectGraphicsObject::mousePressEvent ( QGraphicsSceneMouseEvent * e)
{
	QGraphicsWidget::mousePressEvent(e);
	setItemSelected(!isItemSelected());

	if(e->modifiers() ==  Qt::CTRL)
		Q_EMIT selected(isItemSelected(),true);
	else
		Q_EMIT selected(isItemSelected(),false);

	update();
}

QRectF MgRectGraphicsObject::boundingRect() const  { return d_ptr->backItem->boundingRect(); }

void MgRectGraphicsObject::setGeometry(const QRectF &rect)
{
	QGraphicsWidget::setGeometry(QRectF(rect.topLeft(), d_ptr->backItem->boundingRect().size()));
}


void MgRectGraphicsObject::setUserData(const void * data)
{
	d_ptr->userData = data;
}


const void * MgRectGraphicsObject::userData()const
{
	return d_ptr->userData;
}
//==========================================================



