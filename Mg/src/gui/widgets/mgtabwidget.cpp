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
#include "mgtabwidget.h"


#include <QtGui/QColorDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QWindowsStyle>
#include <QtGui/QPainter>
#include <QtGui/QSplitter>
#include <QtGui/QStackedLayout>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QToolTip>
#include <QtGui/QPixmapCache>
#include <QtCore/QAnimationGroup>
#include <QtCore/QPropertyAnimation>
#include <QPair>
#include <QHash>

#include "mgtabbar.h"
#include "mgutils.h"
#include "mgmultiwidgets.h"
#include "dynamicwidget/mgdynamicwidget.h"


struct MgTabWidgetPrivate
{
    MgTabBar *tabBar;
    QWidget * cornerWidgetContainer;
    MgAnimatedStackedWidget * transitionWidget;
    MgDynamicWidget * dynamicWidget;
    QWidget * selectionWidget;
    Qt::Orientations orientation;


};



MgTabWidget::MgTabWidget(Qt::Orientations orientation,QWidget *parent)
    : QWidget(parent),d_ptr(new MgTabWidgetPrivate)
{
    d_ptr->tabBar = new MgTabBar(orientation,this);
    d_ptr->orientation = orientation;
    create();
}



MgTabWidget::MgTabWidget(Qt::Orientations orientation,const QSize & elementSize,QWidget *parent)
: QWidget(parent),d_ptr(new MgTabWidgetPrivate)
{
    d_ptr->tabBar = new MgTabBar(orientation,elementSize,this);
    d_ptr->orientation = orientation;
    create();
}

void MgTabWidget::create()
{
    d_ptr->cornerWidgetContainer = new QWidget(this);
    d_ptr->dynamicWidget = new MgDynamicWidget(this);



    connect(d_ptr->dynamicWidget,SIGNAL(widgetShown(QString))
    		,this,SIGNAL(temporaryWidgetShown(const QString&)));
    connect(d_ptr->dynamicWidget,SIGNAL(widgetHidden(QString))
    		,this,SIGNAL(temporaryWidgetHidden(const QString&)));

    d_ptr->transitionWidget = new MgAnimatedStackedWidget(d_ptr->dynamicWidget);
    d_ptr->dynamicWidget->setCentralWidget( d_ptr->transitionWidget);

    d_ptr->selectionWidget = new QWidget(this);

    QBoxLayout *selectionLayout;
    QBoxLayout *cornerWidgetLayout;
    QBoxLayout *mainLayout;

    if(d_ptr->orientation == Qt::Vertical)
    {
    	selectionLayout = new QVBoxLayout;
    	d_ptr->selectionWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    	d_ptr->cornerWidgetContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    	cornerWidgetLayout = new QVBoxLayout;
    	mainLayout = new QHBoxLayout;
    }
    else
    {
        selectionLayout = new QHBoxLayout;
        d_ptr->selectionWidget->setSizePolicy( QSizePolicy::Expanding,QSizePolicy::Fixed);
        d_ptr->cornerWidgetContainer->setSizePolicy( QSizePolicy::Preferred,QSizePolicy::Minimum);
        cornerWidgetLayout = new QHBoxLayout;
        mainLayout = new QVBoxLayout;
    }

	selectionLayout->setSpacing(0);
	selectionLayout->setContentsMargins(0,0,0,0);
	selectionLayout->addWidget(d_ptr->tabBar, 1);
	d_ptr->selectionWidget->setLayout(selectionLayout);
	d_ptr->cornerWidgetContainer->setAutoFillBackground(false);
	cornerWidgetLayout->setSpacing(0);
	cornerWidgetLayout->setContentsMargins(0,0,0,0);
	cornerWidgetLayout->addStretch();
	d_ptr->cornerWidgetContainer->setLayout(cornerWidgetLayout);
	selectionLayout->addWidget(d_ptr->cornerWidgetContainer, 0);
	mainLayout->setContentsMargins(0,0,0,0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(d_ptr->selectionWidget);
	mainLayout->addWidget(d_ptr->dynamicWidget);
	setLayout(mainLayout);
    connect(d_ptr->tabBar, SIGNAL(currentChanged(int)), this, SLOT(showWidget(int)));
}

MgTabWidget::~MgTabWidget()
{
	delete d_ptr;
}

void MgTabWidget::setSelectionWidgetHidden(bool hidden)
{
    d_ptr->selectionWidget->setHidden(hidden);
}

void MgTabWidget::insertTab(int index, QWidget *tab, const QIcon &icon, const QString &label)
{
    d_ptr->transitionWidget->insertWidget(index, tab);
    d_ptr->tabBar->insertTab(index, icon, label);
}

int MgTabWidget::appendTab(QWidget *tab, const QIcon &icon, const QString &label)
{
	insertTab(d_ptr->transitionWidget->count(),tab,icon,label);
	return d_ptr->transitionWidget->count()-1;
}

int MgTabWidget::tabCount()const
{
	return d_ptr->transitionWidget->count();
}

void MgTabWidget::removeTab(int index)
{
    d_ptr->transitionWidget->removeWidget(d_ptr->transitionWidget->widget(index));
    d_ptr->tabBar->removeTab(index);
}

void MgTabWidget::setBackgroundBrush(const QBrush &brush)
{
    QPalette pal = d_ptr->tabBar->palette();
    pal.setBrush(QPalette::Mid, brush);
    d_ptr->tabBar->setPalette(pal);
    pal = d_ptr->cornerWidgetContainer->palette();
    pal.setBrush(QPalette::Mid, brush);
    d_ptr->cornerWidgetContainer->setPalette(pal);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////




void MgTabWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QRect rect = d_ptr->selectionWidget->rect().adjusted(0, 0, 1, 0);
    rect = style()->visualRect(layoutDirection(), geometry(), rect);

    if(d_ptr->orientation == Qt::Vertical)
    	MgGuiHelpers::verticalGradient(&painter, rect, rect);
    else
    	MgGuiHelpers::horizontalGradient(&painter, rect, rect);


    painter.setPen(MgGuiHelpers::borderColor());
    painter.drawLine(rect.topRight(), rect.bottomRight());

    QColor light = MgGuiHelpers::sidebarHighlight();

    painter.setPen(light);
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}

void MgTabWidget::insertCornerWidget(int pos, QWidget *widget)
{
    QVBoxLayout *layout = static_cast<QVBoxLayout *>(d_ptr->cornerWidgetContainer->layout());
    layout->insertWidget(pos, widget);
}

int MgTabWidget::cornerWidgetCount() const
{
    return d_ptr->cornerWidgetContainer->layout()->count();
}

void MgTabWidget::addCornerWidget(QWidget *widget)
{
    d_ptr->cornerWidgetContainer->layout()->addWidget(widget);
}

int MgTabWidget::currentIndex() const
{
    return d_ptr->tabBar->currentIndex();
}

void MgTabWidget::setCurrentIndex(int index)
{
    if (d_ptr->tabBar->isTabEnabled(index))
        d_ptr->tabBar->setCurrentIndex(index);
}

void MgTabWidget::showWidget(int index)
{
    d_ptr->transitionWidget->setCurrentIndex(index);
    emit currentChanged(index);
}

void MgTabWidget::setTabToolTip(int index, const QString &toolTip)
{
    d_ptr->tabBar->setTabToolTip(index, toolTip);
}

void MgTabWidget::setTabEnabled(int index, bool enable)
{
    d_ptr->tabBar->setTabEnabled(index, enable);
}

bool MgTabWidget::isTabEnabled(int index) const
{
    return d_ptr->tabBar->isTabEnabled(index);
}

//===========================================================================

void  MgTabWidget::registerTemporaryWidget(const QString & name,QWidget* widget,const char * closeSignal)
{
	d_ptr->dynamicWidget->registerTemporaryWidget(name,widget,closeSignal);
}
void MgTabWidget::registerTemporaryWidget(const QString & name,QWidget*w,const char * showSignal,const char * closeSignal)
{
	d_ptr->dynamicWidget->registerTemporaryWidget(name,w,showSignal,closeSignal);
}

void MgTabWidget::showTemporaryWidget(const QString & name)
{
	d_ptr->dynamicWidget->showTemporaryWidget(name);
}

void MgTabWidget::hideTemporaryWidget(const QString & name)
{
	d_ptr->dynamicWidget->hideTemporaryWidget(name);
}






