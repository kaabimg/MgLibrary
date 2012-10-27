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
#include "mgmultiwidgets.h"
#include "mgfadewidget.h"
#include "../global/mgguiparameters.h"

#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QDebug>
struct MgAnimationAction
{
	enum AnimationType{Direct,Fade,Slide};

	MgAnimationAction(QWidget * w,AnimationType t):widget(w),type(t){}
	MgAnimationAction(QWidget * w,AnimationType t,MgAnimatedStackedWidget::SlideDirection d):widget(w),type(t),direction(d){}

	QWidget * widget;
	AnimationType type;
	MgAnimatedStackedWidget::SlideDirection direction;

};

struct MgAnimatedStackedWidgetPrivate
{

	MgAnimatedStackedWidgetPrivate()
	{
		fadeAnimator.setPropertyName("alpha");
		fadeAnimator.setStartValue(255);
		fadeAnimator.setEndValue(0);
		isActive= false;

		animationType = QEasingCurve::InOutQuad;
		now=0;
		next=0;
		pnow=QPoint(0,0);
		currentWidgetAnimator = new QPropertyAnimation;
		nextWidgetAnimator =new QPropertyAnimation;
		groupAnimator.addAnimation(currentWidgetAnimator);
		groupAnimator.addAnimation(nextWidgetAnimator);
	}

	bool isActive;

	//////
	QPropertyAnimation fadeAnimator;
	MgFadeWidget * fadeWidget;
	//////
	QWidget *mainwindow;
	QEasingCurve::Type animationType;
	int now;
	int next;
	QPoint pnow;
	QPropertyAnimation * currentWidgetAnimator, * nextWidgetAnimator;
	QParallelAnimationGroup groupAnimator;
	//////
	QList<MgAnimationAction*> nextActions;
};


MgAnimatedStackedWidget::MgAnimatedStackedWidget(QWidget * parent) :
		QStackedWidget(parent),d_ptr(new MgAnimatedStackedWidgetPrivate)
{
	if (parent!=0)
		d_ptr->mainwindow=parent;
	else
		d_ptr->mainwindow=this;

	connect(&d_ptr->groupAnimator, SIGNAL(finished()),this,SLOT(onSlideFinished()));
	connect(&d_ptr->fadeAnimator,SIGNAL(finished()),this,SLOT(onFadeFinished()));
}

MgAnimatedStackedWidget::~MgAnimatedStackedWidget()
{
	delete d_ptr;
}

void MgAnimatedStackedWidget::setCurrentWidget(QWidget * w)
{
	checkWidget(w);
	QStackedWidget::setCurrentWidget(w);
}

void MgAnimatedStackedWidget::fadeToWidget(QWidget * w)
{
	if(d_ptr->isActive)
	{
		d_ptr->nextActions<<new MgAnimationAction(w,MgAnimationAction::Fade);
		return;
	}

	setCurrentWidget(w);

	if(!MgGuiParameters::animationsEnabled)
		return;

	d_ptr->isActive = true;
	d_ptr->fadeWidget = new MgFadeWidget(w);
	d_ptr->fadeAnimator.setTargetObject(d_ptr->fadeWidget);
	d_ptr->fadeAnimator.setDuration(MgGuiParameters::transparenceAnimationsDuration);
	d_ptr->fadeWidget->show();
	d_ptr->fadeAnimator.start();
}

void MgAnimatedStackedWidget::onFadeFinished()
{
	d_ptr->fadeWidget->close();
	d_ptr->isActive = false;
	emit fadeFinished();
	execNextAction();
}


void MgAnimatedStackedWidget::checkWidget(QWidget * w)
{
	if(indexOf(w)== -1)
		addWidget(w);
}

void MgAnimatedStackedWidget::setSlideAnimationType(QEasingCurve::Type animationtype)
{
	d_ptr->animationType = animationtype;
}

void MgAnimatedStackedWidget::slideToLeft()
{
	int index = currentIndex()-1;
	if(index<0)
		return;
	slideToWidget(widget(index),MgAnimatedStackedWidget::RightToLeft);
}
void MgAnimatedStackedWidget::slideToRight()
{
	int index = currentIndex()+1;
	if(index>=count())
		return;
	slideToWidget(widget(index),MgAnimatedStackedWidget::LeftToRight);
}



void MgAnimatedStackedWidget::slideToWidget(QWidget * newWidget,MgAnimatedStackedWidget::SlideDirection direction)
{
	if ( newWidget == currentWidget())
		return;
	if(d_ptr->isActive)
	{
		d_ptr->nextActions<<new MgAnimationAction(newWidget,MgAnimationAction::Slide,direction);
		return;
	}

	if(!MgGuiParameters::animationsEnabled)
	{
		setCurrentWidget(newWidget);
		return;
	}

	checkWidget(newWidget);


	d_ptr->isActive=true;


	int now=currentIndex();
	int next=indexOf(newWidget);


	int offsetx = frameRect().width();
	int offsety = frameRect().height();


	newWidget->setGeometry ( 0,  0, offsetx, offsety );

	switch (direction)
	{
		case BottomToTop:
			offsetx=0;
			break;
		case TopToBottom:
			offsetx=0;
			offsety=-offsety;
			break;
		case LeftToRight:
			offsetx=-offsetx;
			offsety=0;
			break;
		case RightToLeft:
			offsety=0;
			break;
	}


	QPoint pnext=newWidget->pos();
	QPoint pnow=currentWidget()->pos();
	d_ptr->pnow=pnow;

	newWidget->move(pnext.x()-offsetx,pnext.y()-offsety);

	newWidget->show();
	newWidget->raise();



	d_ptr->currentWidgetAnimator->setTargetObject(currentWidget());
	d_ptr->currentWidgetAnimator->setPropertyName("pos");
	d_ptr->currentWidgetAnimator->setDuration(MgGuiParameters::slideAnimationsDuration);
	d_ptr->currentWidgetAnimator->setEasingCurve(d_ptr->animationType);
	d_ptr->currentWidgetAnimator->setStartValue(QPoint(pnow.x(), pnow.y()));
	d_ptr->currentWidgetAnimator->setEndValue(QPoint(offsetx+pnow.x(), offsety+pnow.y()));



	d_ptr->nextWidgetAnimator->setTargetObject(newWidget);
	d_ptr->nextWidgetAnimator->setPropertyName("pos");
	d_ptr->nextWidgetAnimator->setDuration(MgGuiParameters::slideAnimationsDuration);
	d_ptr->nextWidgetAnimator->setEasingCurve(d_ptr->animationType);
	d_ptr->nextWidgetAnimator->setStartValue(QPoint(-offsetx+pnext.x(), -offsety+pnext.y()));
	d_ptr->nextWidgetAnimator->setEndValue(QPoint(pnext.x(), pnext.y()));


	d_ptr->next=next;
	d_ptr->now=now;
	d_ptr->groupAnimator.start();
}

void MgAnimatedStackedWidget::onSlideFinished()
{
	setCurrentIndex(d_ptr->next);
//	widget(d_ptr->now)->hide();
//	widget(d_ptr->now)->move(d_ptr->pnow);

	d_ptr->isActive=false;
	emit slideFinished();
	execNextAction();
}


void MgAnimatedStackedWidget::execNextAction()
{
	if(d_ptr->nextActions.isEmpty())
		return;
	MgAnimationAction * animation = d_ptr->nextActions.takeFirst();

	switch (animation->type)
	{
		case MgAnimationAction::Direct:
			setCurrentWidget(animation->widget);
			break;
		case MgAnimationAction::Fade:
			fadeToWidget(animation->widget);
			break;

		case MgAnimationAction::Slide:
			slideToWidget(animation->widget,animation->direction);
			break;
	}
	delete animation;
}


