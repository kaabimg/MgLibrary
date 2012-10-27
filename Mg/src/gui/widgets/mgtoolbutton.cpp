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
#include "mgtoolbutton.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QPainter>
#include <QtGui/QPicture>
#include <QtGui/QVBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QStyle>
#include <QtGui/QStyleOption>
#include <QtGui/QMouseEvent>
#include <QtGui/QApplication>
#include <QtGui/QFont>
#include <QtCore/QEvent>
#include <QtCore/QAnimationGroup>
#include <QtCore/QPropertyAnimation>
#include <QDebug>

#include "mgutils.h"


MgToolButton::MgToolButton(Qt::Orientations orientation,QWidget *parent)
    : QToolButton(parent), m_fader(0),m_orientation(orientation)
{
    m_hasForceVisible = false;
    setAttribute(Qt::WA_Hover, true);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}


MgToolButton::MgToolButton(Qt::Orientations orientation,QAction * action,QWidget *parent):
		QToolButton(parent), m_fader(0),m_orientation(orientation)
{
    m_hasForceVisible = false;
    setAttribute(Qt::WA_Hover, true);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	setDefaultAction(action);
}

void MgToolButton::forceVisible(bool visible)
{
    m_hasForceVisible = true;
    setVisible(visible);
}



QSize MgToolButton::sizeHint() const
{
    QSizeF buttonSize = iconSize().expandedTo(QSize(64, 64));
    return buttonSize.toSize();
}



QSize MgToolButton::minimumSizeHint() const
{
    return QSize(8, 8);
}

void MgToolButton::actionChanged()
{
   if (!m_hasForceVisible) {
        if (QAction* action = defaultAction())
            setVisible(action->isVisible());
    }
}



bool MgToolButton::event(QEvent *e)
{
    switch(e->type()) {
    case QEvent::Enter:
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
            animation->setDuration(180);
            animation->setEndValue(1.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    case QEvent::Leave:
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
            animation->setDuration(180);
            animation->setEndValue(0.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    default:
        return QToolButton::event(e);
    }
    return false;
}

void MgToolButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QRect rect = this->rect().adjusted(-1,-1,2,2);

    MgGuiHelpers::verticalGradient(&painter, rect, rect);

    // draw borders
      if (m_fader > 0 && isEnabled() && !isDown() && !isChecked())
    {
        painter.save();
        int fader = int(60 * m_fader);
        QLinearGradient grad(rect.topLeft(), rect.topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(255, 255, 255, fader));
        grad.setColorAt(1, Qt::transparent);
        painter.fillRect(rect, grad);
        painter.setPen(QPen(grad, 1.0));
        painter.drawLine(rect.topLeft(), rect.topRight());
        painter.drawLine(rect.bottomLeft(), rect.bottomRight());
        painter.restore();

    }
    else if (isDown() || isChecked())
    {
		painter.save();
		QLinearGradient grad(rect.topLeft(), rect.topRight());
		grad.setColorAt(0, QColor(255, 255, 255, 140));
		grad.setColorAt(1, QColor(255, 255, 255, 210));
		painter.fillRect(rect.adjusted(0, 0, 0, -1), grad);
		painter.restore();

		//shadows
		painter.setPen(QColor(0, 0, 0, 110));
		painter.drawLine(rect.topLeft() + QPoint(1,-1), rect.topRight() - QPoint(0,1));
		painter.drawLine(rect.bottomLeft(), rect.bottomRight());
		painter.setPen(QColor(0, 0, 0, 40));
		painter.drawLine(rect.topLeft(), rect.bottomLeft());

		//highlights
		painter.setPen(QColor(255, 255, 255, 50));
		painter.drawLine(rect.topLeft() + QPoint(0, -2), rect.topRight() - QPoint(0,2));
		painter.drawLine(rect.bottomLeft() + QPoint(0, 1), rect.bottomRight() + QPoint(0,1));
		painter.setPen(QColor(255, 255, 255, 40));
		painter.drawLine(rect.topLeft() + QPoint(0, 0), rect.topRight());
		painter.drawLine(rect.topRight() + QPoint(0, 1), rect.bottomRight() - QPoint(0, 1));
		painter.drawLine(rect.bottomLeft() + QPoint(0,-1), rect.bottomRight()-QPoint(0,1));
    }
    QPixmap borderPixmap;


    QRect iconRect(0, 0, MgGuiHelpers::iconSize, MgGuiHelpers::iconSize);
    // draw popup texts

    iconRect.moveCenter(rect.center());
    MgGuiHelpers::mgDrawIconWithShadow(icon(), iconRect, &painter, isEnabled() ? QIcon::Normal : QIcon::Disabled);

}

