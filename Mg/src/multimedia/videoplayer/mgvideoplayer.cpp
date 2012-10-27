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
#include "mgvideoplayer.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>

#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/videoplayer.h>
#include <phonon/videowidget.h>

#include "mgvideocontroller.h"

struct MgVideoPlayerPrivate
{
	Phonon::VideoPlayer * videoPlayer;
	MgVideoController * videoController;
	QVBoxLayout * layout;
};


MgVideoPlayer::MgVideoPlayer(QWidget * parent) : QWidget(parent),
		d_ptr(new MgVideoPlayerPrivate)
{

	d_ptr->videoPlayer = new Phonon::VideoPlayer(this);
	d_ptr->videoController = new MgVideoController(this);
	QToolBar * controlToolBar = d_ptr->videoController->toolBar();
	controlToolBar->setParent(this);


	d_ptr->layout = new QVBoxLayout;
	d_ptr->layout->setContentsMargins(0,0,0,0);
	d_ptr->layout->setSpacing(0);
	d_ptr->layout->addWidget(d_ptr->videoPlayer);
	d_ptr->layout->addWidget(controlToolBar);

	setLayout(d_ptr->layout);



	d_ptr->videoController->setMediaObject(d_ptr->videoPlayer->mediaObject());
//	Phonon::MediaSource videoFile("/home/ghaith/Desktop/gilmour.avi");
//	d_ptr->videoPlayer->load(videoFile);
}

MgVideoPlayer::~MgVideoPlayer()
{
	delete d_ptr;
}
