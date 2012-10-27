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
#include "mgoutputpanebar.h"

#include <QtCore/QList>
#include <QtGui/QHBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QDebug>
#include "mgoutputpanetogglebutton.h"
//#include "../global/mgguiparameters.h"

struct MgOutputPaneBarPrivate
{
	QHBoxLayout * layout;
	QList<MgOutputPaneToggleButton*> buttons;
	int width;

};


MgOutputPaneBar::MgOutputPaneBar(QWidget * parent):QWidget(parent),d_ptr(new MgOutputPaneBarPrivate)
{
	d_ptr->layout = new QHBoxLayout;
    d_ptr->layout ->setContentsMargins(0,0,0,0);
    d_ptr->layout ->setSpacing(10);
    d_ptr->layout->setDirection(QBoxLayout::LeftToRight);
    d_ptr->layout->setAlignment(Qt::AlignCenter);

    setLayout(d_ptr->layout );

    setFixedHeight(29);
    d_ptr->width = 0;

}

MgOutputPaneBar::~MgOutputPaneBar()
{
	delete d_ptr;
}


void MgOutputPaneBar::addWidget(QWidget * w)
{
	d_ptr->layout->addWidget(w);
}

void MgOutputPaneBar::addPane(const QString &text )
{
	MgOutputPaneToggleButton * button = new MgOutputPaneToggleButton(d_ptr->buttons.count()+1,text,this);
	d_ptr->layout->addWidget(button);
	d_ptr->buttons<<button;
	connect(button,SIGNAL(toggled(bool)),this,SLOT(paneButtonToggled(bool)));
}

void MgOutputPaneBar::untoggleButton(const QString& text)
{
	foreach(MgOutputPaneToggleButton* button, d_ptr->buttons)
	{
		if(button->text() == text)
		{
			button->blockSignals(true);
			button->setChecked(false);
			button->blockSignals(false);
		}
	}
}

void MgOutputPaneBar::paneButtonToggled(bool toggled)
{
	MgOutputPaneToggleButton * theButton = qobject_cast<MgOutputPaneToggleButton*>(sender());

	if(toggled)
	{
//		foreach(MgOutputPaneToggleButton * button,d_ptr->buttons)
//		{
//			if(button != theButton )
//			{
//				button->blockSignals(true);
//				button->setChecked(false);
//				button->blockSignals(false);
//			}
//		}
		emit showRequest(theButton->text());
	}
	else
	{
		emit hideRequest(theButton->text());
	}
}

void MgOutputPaneBar::paintEvent(QPaintEvent * e)
{
	QPainter painter(this);

	QLinearGradient linearGrad(rect().topLeft(),rect().bottomLeft());
	QColor color(70,70,70);
	linearGrad.setColorAt(0, color);
	color = QColor(20,20,20);
	linearGrad.setColorAt(1, color);
	painter.fillRect(rect(),linearGrad);

	QWidget::paintEvent(e);

}
