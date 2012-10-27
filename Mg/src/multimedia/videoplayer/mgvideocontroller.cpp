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
#include "mgvideocontroller.h"
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include <QAction>
#include <QHBoxLayout>
#include <QStyle>
#include <QMessageBox>
#include <QApplication>
#include <QToolBar>

struct MgVideoControllerPrivate
{
	Phonon::SeekSlider * seekSlider;
	QAction  * playOrPauseAction, *stopAction;
	QHBoxLayout * layout;
	QToolBar * toolBar;

};

MgVideoController::MgVideoController(QObject  * parent) :QObject(parent),
		d_ptr(new MgVideoControllerPrivate)
{

	d_ptr->toolBar =new QToolBar;

	d_ptr->toolBar->setStyleSheet("background-color: rgb(30,30,30)");



	d_ptr->seekSlider = new Phonon::SeekSlider(d_ptr->toolBar);

	d_ptr->seekSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	d_ptr->toolBar->addWidget(d_ptr->seekSlider);

	d_ptr->playOrPauseAction = d_ptr->toolBar->addAction(qApp->style()->standardIcon(QStyle::SP_MediaPlay),"play",
			this,SLOT(playOrPause()));

	d_ptr->stopAction = d_ptr->toolBar->addAction(qApp->style()->standardIcon(QStyle::SP_MediaStop),"stop"
			,this,SLOT(stop()));




	d_ptr->seekSlider->setStyleSheet("QSlider::groove:horizontal {"
     "border: 1px solid #999999;"
     "height: 8px;"/* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */
     "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
     "margin: 2px 0;"
 	 "}"
	"QSlider::handle:horizontal {"
     "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
     "border: 1px solid #5c5c5c;"
     "width: 18px;"
     "margin: -2px 0;" /* handle is placed by default on the contents rect of the groove. Expand outside the groove */
     "border-radius: 3px;"
 "}");

}

QToolBar * MgVideoController::toolBar()
{
	return d_ptr->toolBar;
}

MgVideoController::~MgVideoController()
{
	delete d_ptr;
}

void MgVideoController::setMediaObject(Phonon::MediaObject* mediaObject)
{
	d_ptr->seekSlider->setMediaObject(mediaObject);
	connect(mediaObject,SIGNAL(stateChanged(Phonon::State,Phonon::State)),this,SLOT(onStateChanged()));
}

void MgVideoController::playOrPause()
{
	Phonon::MediaObject * mediaObject(d_ptr->seekSlider->mediaObject());
	if(mediaObject)
	{
		if(mediaObject->state()!=Phonon::PlayingState)
			mediaObject->play();
		else
			mediaObject->pause();
	}
}
void MgVideoController::stop()
{
	Phonon::MediaObject * mediaObject(d_ptr->seekSlider->mediaObject());
	if(mediaObject)
		mediaObject->stop();
}

void MgVideoController::onStateChanged()
{

	Phonon::MediaObject * mediaObject(d_ptr->seekSlider->mediaObject());
	if(mediaObject)
	{
		Phonon::State s(mediaObject->state());
		switch (s) {
			case Phonon::PlayingState:
			{
				d_ptr->playOrPauseAction->setDisabled(false);
				d_ptr->playOrPauseAction->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaPause));
				break;
			}
			case Phonon::PausedState:
			{


				d_ptr->playOrPauseAction->setDisabled(false);
				d_ptr->playOrPauseAction->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaPlay));
				break;
			}
			case Phonon::StoppedState:
			{
				d_ptr->playOrPauseAction->setDisabled(false);
				d_ptr->playOrPauseAction->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaPlay));
				break;
			}
			case Phonon::LoadingState:
			{
				d_ptr->playOrPauseAction->setDisabled(true);
				break;
			}
			case Phonon::BufferingState:
			{
				d_ptr->playOrPauseAction->setDisabled(true);
				break;
			}
			case Phonon::ErrorState:
				QMessageBox::critical(qobject_cast<QWidget*>(parent()),"Media player error",mediaObject->errorString());
				break;
		}
	}
}

