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
#include "mglistview.h"

#include <QtGui/QMouseEvent>
#include <QtGui/QWindowsStyle>
#include <QtGui/QPainter>
#include <QtGui/QToolTip>
#include <QtGui/QPixmapCache>
#include <QtGui/QScrollArea>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>

#include <QtCore/QAnimationGroup>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

#include "mgfadeelement.h"
#include "mgutils.h"
#include "mgstylehelper.h"
#include "../global/mgguiparameters.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////


class MgListViewScrollArea : public QScrollArea
{
public:
	MgListViewScrollArea(QWidget * parent=0):QScrollArea(parent){}

protected:
	void resizeEvent(QResizeEvent *event)
	{
		widget()->resize(event->size());
		QScrollArea::resizeEvent(event);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MgListViewPrivate
{
	MgListViewPrivate():hoverIndex(-1),currentIndex(-1)
	{
		triggerTimer.setSingleShot(true);
		elementHeigth = 100;
	}
	~MgListViewPrivate(){triggerTimer.stop();}

	QRect hoverRect;
	int hoverIndex;
	int currentIndex;
	QList<MgFadeElement*> elements;
	QTimer triggerTimer;

	int elementHeigth;

};





MgListView::MgListView(QWidget *parent)
: QWidget(parent),d_ptr(new MgListViewPrivate)
{
	create();
}

MgListView::MgListView(int elementHeigth,QWidget *parent)
: QWidget(parent),d_ptr(new MgListViewPrivate)
{
	d_ptr->elementHeigth  = elementHeigth;
	create();
}


void MgListView::create()
{
//	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	setStyle(new QWindowsStyle);

	setAttribute(Qt::WA_Hover, true);
	setFocusPolicy(Qt::NoFocus);
	setMouseTracking(true); // Needed for hover events


	connect(&d_ptr->triggerTimer, SIGNAL(timeout()), this, SLOT(emitCurrentIndex()));
}

MgListView::~MgListView()
{
	delete style();
	delete d_ptr;
}

QScrollArea * MgListView::embedInScrollArea()
{
	MgListViewScrollArea * scrollArea = new MgListViewScrollArea;
	scrollArea->setWidget(this);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setWidgetResizable(true);

	return scrollArea;

}


QSize MgListView::sizeHint() const
{
	return QSize(width(),d_ptr->elementHeigth * d_ptr->elements.size());
}

QSize MgListView::minimumSizeHint() const
{
	return sizeHint();
//	return QSize(d_ptr->elementHeigth * 6,d_ptr->elementHeigth * d_ptr->elements.size());
}

bool MgListView::validIndex(int index) const { return index >= 0 && index < d_ptr->elements.count(); }


void MgListView::insertElement(int index, MgFadeElement * element)
{
	element->setParent(this);
	d_ptr->elements.insert(index, element);
}

void MgListView::removeElement(int index)
{
	if(!validIndex(index))
		return;

	MgFadeElement *element = d_ptr->elements.takeAt(index);
	delete element;

}

int MgListView::currentIndex() const
{
	return d_ptr->currentIndex;
}

int MgListView::count() const {return d_ptr->elements.count(); }


void MgListView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);


    QRect myRect = style()->visualRect(layoutDirection(), geometry(), rect());

    QColor color(MgGuiParameters::listViewBaseColor);
    color.setAlpha(200);
    painter.fillRect(myRect,QBrush(color));


    painter.setPen(MgGuiParameters::listViewborderColor);

    painter.drawLine(myRect.topRight(), myRect.bottomRight());
    painter.drawLine(myRect.bottomLeft(), myRect.bottomRight());

	for (int i = 0; i < count(); ++i)
		if (i != currentIndex())
			paintElement(&painter,i);

	// paint active tab last, since it overlaps the neighbors
	if (currentIndex() != -1)
		paintElement(&painter, currentIndex());

}

// Handle hover events for mouse fade ins
void MgListView::mouseMoveEvent(QMouseEvent *e)
{
	int newHover = -1;
	for (int i = 0; i < count(); ++i)
	{
		QRect area = elementRect(i);
		if (area.contains(e->pos()))
		{
			newHover = i;
			break;
		}
	}
	if (newHover == d_ptr->hoverIndex)
		return;

	if (validIndex(d_ptr->hoverIndex))
		d_ptr->elements[d_ptr->hoverIndex]->fadeOut();

	d_ptr->hoverIndex = newHover;

	if (validIndex(d_ptr->hoverIndex))
	{
		d_ptr->elements[d_ptr->hoverIndex]->fadeIn();
		d_ptr->hoverRect = elementRect(d_ptr->hoverIndex);
	}
}

bool MgListView::event(QEvent *event)
{
	if (event->type() == QEvent::ToolTip)
	{
		if (validIndex(d_ptr->hoverIndex))
		{
			QString tt = d_ptr->elements[d_ptr->hoverIndex]->toolTip;
			if (!tt.isEmpty()) {
				QToolTip::showText(static_cast<QHelpEvent*>(event)->globalPos(), tt, this);
				return true;
			}
		}
	}
	return QWidget::event(event);
}

// Resets hover animation on mouse enter
void MgListView::enterEvent(QEvent *e)
{
	Q_UNUSED(e)
    d_ptr->hoverRect = QRect();
	d_ptr->hoverIndex = -1;
}

// Resets hover animation on mouse enter
void MgListView::leaveEvent(QEvent *e)
{
	Q_UNUSED(e)
    d_ptr->hoverIndex = -1;
	d_ptr->hoverRect = QRect();
	for (int i = 0 ; i < d_ptr->elements.count() ; ++i)
	{
		d_ptr->elements[i]->fadeOut();
	}
}

void MgListView::resizeEvent ( QResizeEvent *  event)
{
//	if(d_ptr->elementHeigth > event->size().width()/6 || d_ptr->elementHeigth < event->size().width()/8)
//		d_ptr->elementHeigth = event->size().width()/6;

	QWidget::resizeEvent(event);
}


QRect MgListView::elementRect(int index) const
{
	return QRect(0, index * d_ptr->elementHeigth, width(), d_ptr->elementHeigth );
}

void MgListView::emitCurrentIndex()
{
	emit currentChanged(d_ptr->elements[d_ptr->currentIndex]->id);
}

void MgListView::mousePressEvent(QMouseEvent *e)
{
	e->accept();
	for (int index = 0; index < d_ptr->elements.count(); ++index)
	{
		if (elementRect(index).contains(e->pos()))
		{

			if (isElementEnabled(index))
			{
				d_ptr->currentIndex = index;
				update();
				d_ptr->triggerTimer.start(0);
				emit elementClicked(d_ptr->elements[index]->id);
			}
			break;
		}
	}
}

void MgListView::mouseDoubleClickEvent (QMouseEvent * e)
{
	e->accept();
	for (int index = 0; index < d_ptr->elements.count(); ++index)
	{
		if (elementRect(index).contains(e->pos())) {

			if (isElementEnabled(index))
			{
				emit elementDoubleClicked(d_ptr->elements[index]->id);
			}
			break;
		}
	}
}

void MgListView::paintElement(QPainter *painter, int index) const
{
	if (!validIndex(index))
		return;

	painter->save();
	MgFadeElement * element = d_ptr->elements[index];
	QRect rect = elementRect(index);
	bool selected = (index == d_ptr->currentIndex);

	if(d_ptr->hoverIndex == index && !selected)
		MgStyleHelper::mgDrawHorizontalGradiant(painter,rect,MgGuiParameters::listViewHoverColor,40,60);
	else if (selected)
	{

		MgStyleHelper::mgDrawHorizontalGradiant(painter,rect,MgGuiParameters::listViewHighlightColor,100,140);

		painter->setPen(MgGuiParameters::listViewHighlightColor);
		painter->drawRect(rect);
	}



	painter->setPen(selected ? MgGuiParameters::listViewActiveTextColor : MgGuiParameters::listViewPassiveTextColor);
	paintElementContent(painter,rect,element);

	painter->restore();
}

void MgListView::paintElementContent(QPainter *painter,const QRect & rect,MgFadeElement* element)const
{
	if (!element->enabled)
		painter->setOpacity(0.7);

	QRect leftIconRect (rect.topLeft(),QSize(d_ptr->elementHeigth,d_ptr->elementHeigth));
	if(!element->leftIcon.isNull())
		MgGuiHelpers::mgDrawIconWithShadow(element->leftIcon, leftIconRect, painter, element->enabled ? QIcon::Normal : QIcon::Disabled);


	QRect rightIconRect (QPoint(rect.topRight().x()-d_ptr->elementHeigth,rect.topLeft().y()),
			QSize(d_ptr->elementHeigth,d_ptr->elementHeigth));
	if(!element->rightIcon.isNull())
		MgGuiHelpers::mgDrawIconWithShadow(element->rightIcon, rightIconRect, painter, element->enabled ? QIcon::Normal : QIcon::Disabled);


	QRect textRect (QPoint(rect.topLeft().x()+d_ptr->elementHeigth,rect.topLeft().y()),
			QSize(rect.width()-2 *d_ptr->elementHeigth,d_ptr->elementHeigth));



	QRect titleRect(textRect.topLeft(),QSize(textRect.width(),d_ptr->elementHeigth/3));
	titleRect.adjust(titleRect.width()/20,titleRect.height()/20,titleRect.width()/10,titleRect.height()/10);

	QRect elementTextRect(titleRect.bottomLeft(),QSize(textRect.width(),d_ptr->elementHeigth*2/3));
	elementTextRect.adjust(elementTextRect.width()/20,elementTextRect.height()/20,elementTextRect.width()/10,elementTextRect.height()/10);

	QFont font = painter->font();


	font.setPointSize(10);

	painter->save();
	font.setBold(true);

	painter->setFont(font);

	painter->drawText(titleRect,Qt::AlignLeft || Qt::AlignVCenter,element->title);
	painter->restore();


	painter->save();
	font.setBold(false);
	painter->setFont(font);
	painter->drawText(elementTextRect,Qt::AlignLeft || Qt::AlignVCenter ,element->text);
	painter->restore();
}

void MgListView::setCurrentIndex(int index)
{
	if (isElementEnabled(index))
	{
		d_ptr->currentIndex = index;
		update();
		emitCurrentIndex();
	}
}

void MgListView::setElementEnabled(int index, bool enable)
{
	if(!validIndex(index))
		return;

	d_ptr->elements[index]->enabled = enable;
	update(elementRect(index));
}

bool MgListView::isElementEnabled(int index) const
{
	if(!validIndex(index))
		return false;

	return d_ptr->elements[index]->enabled;
}
