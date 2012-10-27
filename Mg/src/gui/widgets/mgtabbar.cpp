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
#include "mgtabbar.h"



#include <QtGui/QMouseEvent>
#include <QtGui/QWindowsStyle>
#include <QtGui/QPainter>
#include <QtGui/QToolTip>
#include <QtGui/QPixmapCache>
#include <QtCore/QAnimationGroup>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

#include "mgfadeelement.h"
#include "mgutils.h"

struct MgTabBarPrivate
{
	MgTabBarPrivate():hoverIndex(-1),currentIndex(-1)
	{
		triggerTimer.setSingleShot(true);
		tabElementSize = QSize(80,40);
	}
	~MgTabBarPrivate(){triggerTimer.stop();}

	QRect hoverRect;
	int hoverIndex;
	int currentIndex;
	QList<MgFadeElement*> tabs;
	QTimer triggerTimer;

	Qt::Orientations orientation;
//	static const int rounding;

	QSize tabElementSize;


	QColor panelTextColor(bool lightColored = false)
	{
		if (!lightColored)
			return Qt::white;
		else
			return Qt::black;
	}

};

//const int MgTabBarPrivate::rounding = 22;




MgTabBar::MgTabBar(Qt::Orientations orientation,QWidget *parent)
: QWidget(parent),d_ptr(new MgTabBarPrivate)
{
	d_ptr->orientation = orientation;
	create();

}

MgTabBar::MgTabBar(Qt::Orientations orientation,const QSize & elementSize,QWidget *parent)
: QWidget(parent),d_ptr(new MgTabBarPrivate)
{
	d_ptr->orientation = orientation;
	d_ptr->tabElementSize  = elementSize;
	create();
}


void MgTabBar::create()
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	setStyle(new QWindowsStyle);

	setAttribute(Qt::WA_Hover, true);
	setFocusPolicy(Qt::NoFocus);
	setMouseTracking(true); // Needed for hover events

	if(d_ptr->orientation == Qt::Vertical)
		setMinimumWidth(d_ptr->tabElementSize.width());
	else
		setMinimumHeight(d_ptr->tabElementSize.height());

	connect(&d_ptr->triggerTimer, SIGNAL(timeout()), this, SLOT(emitCurrentIndex()));
}

MgTabBar::~MgTabBar()
{
	delete style();
	delete d_ptr;
}


bool MgTabBar::validIndex(int index) const { return index >= 0 && index < d_ptr->tabs.count(); }


void MgTabBar::insertTab(int index, const QIcon &icon, const QString &label)
{
	MgFadeElement*tab = new MgFadeElement(this);
	tab->leftIcon = icon;
	tab->text = label;
	d_ptr->tabs.insert(index, tab);
}

void MgTabBar::removeTab(int index)
{
	if(!validIndex(index))
		return;

	MgFadeElement *tab = d_ptr->tabs.takeAt(index);
	delete tab;

}

int MgTabBar::currentIndex() const
{
	return d_ptr->currentIndex;
}


void MgTabBar::setTabToolTip(int index, QString toolTip)
{
	if(!validIndex(index))
		return;
	d_ptr->tabs[index]->toolTip = toolTip;
}
QString MgTabBar::tabToolTip(int index) const
{
	if(!validIndex(index))
		return QString();
	return d_ptr->tabs.at(index)->toolTip;
}

QIcon MgTabBar::tabIcon(int index) const
{
	if(!validIndex(index))
		return QIcon();
	return d_ptr->tabs.at(index)->leftIcon;
}
QString MgTabBar::tabText(int index) const
{
	if(!validIndex(index))
		return QString();
	return d_ptr->tabs.at(index)->text;
}
int MgTabBar::count() const {return d_ptr->tabs.count(); }


void MgTabBar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)
    QPainter p(this);

	p.save();
	QLinearGradient grad(rect().topLeft(), rect().topRight());
	grad.setColorAt(0, QColor(20, 20, 20));
	grad.setColorAt(1, QColor(75, 75, 75));
	p.fillRect(rect(), grad);
	p.restore();

	for (int i = 0; i < count(); ++i)
		if (i != currentIndex())
			paintTab(&p, i);

	// paint active tab last
	if (currentIndex() != -1)
		paintTab(&p, currentIndex());
}


void MgTabBar::mouseMoveEvent(QMouseEvent *e)
{
	int newHover = -1;
	for (int i = 0; i < count(); ++i)
	{
		QRect area = tabRect(i);
		if (area.contains(e->pos()))
		{
			newHover = i;
			break;
		}
	}
	if (newHover == d_ptr->hoverIndex)
		return;

	if (validIndex(d_ptr->hoverIndex))
		d_ptr->tabs[d_ptr->hoverIndex]->fadeOut();

	d_ptr->hoverIndex = newHover;

	if (validIndex(d_ptr->hoverIndex))
	{
		d_ptr->tabs[d_ptr->hoverIndex]->fadeIn();
		d_ptr->hoverRect = tabRect(d_ptr->hoverIndex);
	}
}

bool MgTabBar::event(QEvent *event)
{
	if (event->type() == QEvent::ToolTip)
	{
		if (validIndex(d_ptr->hoverIndex))
		{
			QString tt = tabToolTip(d_ptr->hoverIndex);
			if (!tt.isEmpty()) {
				QToolTip::showText(static_cast<QHelpEvent*>(event)->globalPos(), tt, this);
				return true;
			}
		}
	}
	return QWidget::event(event);
}

// Resets hover animation on mouse enter
void MgTabBar::enterEvent(QEvent *e)
{
	Q_UNUSED(e)
	d_ptr->hoverRect = QRect();
	d_ptr->hoverIndex = -1;
}

// Resets hover animation on mouse enter
void MgTabBar::leaveEvent(QEvent *e)
{
	Q_UNUSED(e)
    d_ptr->hoverIndex = -1;
	d_ptr->hoverRect = QRect();
	for (int i = 0 ; i < d_ptr->tabs.count() ; ++i) {
		d_ptr->tabs[i]->fadeOut();
	}
}

QSize MgTabBar::sizeHint() const
{
	QSize sh = tabSizeHint();
	if(d_ptr->orientation == Qt::Vertical)
		return QSize(sh.width(), sh.height() * d_ptr->tabs.count());
	return QSize(sh.width()* d_ptr->tabs.count(), sh.height() );
}

QSize MgTabBar::minimumSizeHint() const
{
	QSize sh = tabSizeHint(true);
	if(d_ptr->orientation == Qt::Vertical)
		return QSize(sh.width(), sh.height() * d_ptr->tabs.count());
	return QSize(sh.width()* d_ptr->tabs.count(), sh.height() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSize MgTabBar::tabSizeHint(bool minimum) const
{
	QFont boldFont(font());
	boldFont.setPointSizeF(MgGuiHelpers::fontSize);
	boldFont.setBold(true);
	QFontMetrics fm(boldFont);
	int spacing = 8;

	int width = d_ptr->tabElementSize.width() + spacing + 2;//old :: 60

	int maxLabelwidth = 0;
	for (int tab=0 ; tab<count() ;++tab)
	{
		int width = fm.width(tabText(tab));
		if (width > maxLabelwidth)
			maxLabelwidth = width;
	}
	int iconHeight = minimum ? 0 : d_ptr->tabElementSize.height();//old :: 32
	return QSize(qMax(width, maxLabelwidth + 4), iconHeight + spacing + fm.height());
}


QRect MgTabBar::tabRect(int index) const
{
	QSize sh = tabSizeHint();

	if(d_ptr->orientation == Qt::Vertical)
	{

		if (sh.height() * d_ptr->tabs.count() > height())
			sh.setHeight(height() / d_ptr->tabs.count());


		return QRect(0, index * sh.height(), sh.width(), sh.height());
	}

	if (sh.width() * d_ptr->tabs.count() > width())
		sh.setWidth(width() / d_ptr->tabs.count());

	return QRect(index * sh.width(), 0, sh.width(), sh.height());

}


void MgTabBar::emitCurrentIndex()
{
	emit currentChanged(d_ptr->currentIndex);
}

void MgTabBar::mousePressEvent(QMouseEvent *e)
{
	e->accept();
	for (int index = 0; index < d_ptr->tabs.count(); ++index) {
		if (tabRect(index).contains(e->pos())) {

			if (isTabEnabled(index)) {
				d_ptr->currentIndex = index;
				update();
				d_ptr->triggerTimer.start(0);
			}
			break;
		}
	}
}


void MgTabBar::paintTab(QPainter *painter, int tabIndex) const
{
	if (!validIndex(tabIndex))
		return;

	painter->save();

	QRect rect = tabRect(tabIndex);
	bool selected = (tabIndex == d_ptr->currentIndex);
	bool enabled = isTabEnabled(tabIndex);

	if (selected)
	{
		//background
		painter->save();
		QLinearGradient grad(rect.topLeft(), rect.topRight());
		grad.setColorAt(0, QColor(255, 255, 255, 140));
		grad.setColorAt(1, QColor(255, 255, 255, 210));
		painter->fillRect(rect.adjusted(0, 0, 0, -1), grad);
		painter->restore();

		//shadows
//		painter->setPen(QColor(0, 0, 0, 110));
		painter->drawLine(rect.topLeft() + QPoint(1,-1), rect.topRight() - QPoint(0,1));
		painter->drawLine(rect.bottomLeft(), rect.bottomRight());
		painter->setPen(QColor(0, 0, 0, 40));
		painter->drawLine(rect.topLeft(), rect.bottomLeft());

		//highlights
		painter->setPen(QColor(255, 255, 255, 50));
		painter->drawLine(rect.topLeft() + QPoint(0, -2), rect.topRight() - QPoint(0,2));
		painter->drawLine(rect.bottomLeft() + QPoint(0, 1), rect.bottomRight() + QPoint(0,1));
		painter->setPen(QColor(255, 255, 255, 40));
		painter->drawLine(rect.topLeft() + QPoint(0, 0), rect.topRight());
		painter->drawLine(rect.topRight() + QPoint(0, 1), rect.bottomRight() - QPoint(0, 1));
		painter->drawLine(rect.bottomLeft() + QPoint(0,-1), rect.bottomRight()-QPoint(0,1));
	}

	QString tabText(this->tabText(tabIndex));
	QRect tabTextRect(tabRect(tabIndex));
	QRect tabIconRect(tabTextRect);
	tabTextRect.translate(0, -2);
	QFont boldFont(painter->font());
	boldFont.setPointSizeF(MgGuiHelpers::fontSize);
	boldFont.setBold(true);
	painter->setFont(boldFont);
	painter->setPen(selected ? QColor(255, 255, 255, 160) : QColor(0, 0, 0, 110));
	int textFlags = Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap;

	if (enabled)
	{
		painter->drawText(tabTextRect, textFlags, tabText);
		painter->setPen(selected ? QColor(60, 60, 60) : d_ptr->panelTextColor());
	}
	else
	{
		painter->setPen(selected ? d_ptr->panelTextColor() : QColor(255, 255, 255, 120));
	}

	if (!selected && enabled)
	{
		painter->save();
		int fader = int(d_ptr->tabs[tabIndex]->fader());
		QLinearGradient grad(rect.topLeft(), rect.topRight());
		grad.setColorAt(0, Qt::transparent);
		grad.setColorAt(0.5, QColor(255, 255, 255, fader));
		grad.setColorAt(1, Qt::transparent);
		painter->fillRect(rect, grad);
		painter->setPen(QPen(grad, 1.0));
		painter->drawLine(rect.topLeft(), rect.topRight());
		painter->drawLine(rect.bottomLeft(), rect.bottomRight());
		painter->restore();
	}


	if (!enabled)
		painter->setOpacity(0.7);

	int textHeight = painter->fontMetrics().boundingRect(QRect(0, 0, width(), height()), Qt::TextWordWrap, tabText).height();
	tabIconRect.adjust(0, 4, 0, -textHeight);
	MgGuiHelpers::mgDrawIconWithShadow(tabIcon(tabIndex), tabIconRect, painter, enabled ? QIcon::Normal : QIcon::Disabled);

	painter->translate(0, -1);
	painter->drawText(tabTextRect, textFlags, tabText);
	painter->restore();
}

void MgTabBar::setCurrentIndex(int index)
{
	if (isTabEnabled(index))
	{
		d_ptr->currentIndex = index;
		update();
		emit currentChanged(d_ptr->currentIndex);
	}
}

void MgTabBar::setTabEnabled(int index, bool enable)
{
	if(!validIndex(index))
		return;

	d_ptr->tabs[index]->enabled = enable;
	update(tabRect(index));
}

bool MgTabBar::isTabEnabled(int index) const
{
	if(!validIndex(index))
		return false;

	return d_ptr->tabs[index]->enabled;
}
