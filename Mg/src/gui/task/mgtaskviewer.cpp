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
#include "mgtaskviewer.h"
#include <MgCore/MgTask>
#include <MgCore/MgThread>


#include <QTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QApplication>
#include <QStyle>
#include <QLabel>

#include "../widgets/mgmessagesareawidget.h"

struct MgTaskViewerPrivate
{
	QVBoxLayout * mainLayout;
	MgMessagesAreaWidget * messagesArea;
	QProgressBar * progressBar;
	QPushButton * stopButton;
	QLabel * statusLabel;
};


MgTaskViewer::MgTaskViewer(MgTask * task,QWidget * parent):QWidget(parent),d_ptr(new MgTaskViewerPrivate)
{
	d_ptr->mainLayout = new QVBoxLayout(this);
	d_ptr->statusLabel =  new QLabel(this);
	d_ptr->statusLabel->setText("Status : to be started ...");
	d_ptr->mainLayout->addWidget(d_ptr->statusLabel);

	d_ptr->progressBar  = new QProgressBar(this);
	d_ptr->progressBar->setRange(0,100);
	d_ptr->progressBar->setVisible(false);

	if(task->supportsStop())
	{
		QSplitter * splitter = new QSplitter(this);
		splitter->setLayoutDirection(Qt::LeftToRight);
		splitter->addWidget(d_ptr->progressBar);
		d_ptr->stopButton = new QPushButton(this);
		d_ptr->stopButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop));
		connect(d_ptr->stopButton,SIGNAL(clicked()),task,SLOT(stop()));
		splitter->addWidget(d_ptr->stopButton);
		d_ptr->stopButton->setVisible(false);
		d_ptr->mainLayout->addWidget(splitter);
	}
	else
	{
		d_ptr->stopButton = NULL;
		d_ptr->mainLayout->addWidget(d_ptr->progressBar);
	}

	d_ptr->messagesArea = new MgMessagesAreaWidget(this);
	d_ptr->messagesArea->registerSender(task);
	d_ptr->mainLayout->addWidget(d_ptr->messagesArea);

	connect(task,SIGNAL(started()),this,SLOT(onTaskStarted()));
	connect(task,SIGNAL(finished()),this,SLOT(onTaskFinished()));
	connect(task,SIGNAL(progress(int)),d_ptr->progressBar ,SLOT(setValue(int)));
	setLayout(d_ptr->mainLayout);
}



MgTaskViewer::MgTaskViewer(MgThread * task,QWidget * parent):QWidget(parent),d_ptr(new MgTaskViewerPrivate)
{
	d_ptr->mainLayout = new QVBoxLayout(this);
	d_ptr->statusLabel =  new QLabel(this);
	d_ptr->statusLabel->setText("Status : to be started ...");
	d_ptr->mainLayout->addWidget(d_ptr->statusLabel);

	d_ptr->progressBar  = new QProgressBar(this);
	d_ptr->progressBar->setRange(0,100);
	d_ptr->progressBar->setVisible(false);

	if(task->supportsStop())
	{
		QSplitter * splitter = new QSplitter(this);
		splitter->setLayoutDirection(Qt::LeftToRight);
		splitter->addWidget(d_ptr->progressBar);
		d_ptr->stopButton = new QPushButton(this);
		d_ptr->stopButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop));
		connect(d_ptr->stopButton,SIGNAL(clicked()),task,SLOT(stop()));
		splitter->addWidget(d_ptr->stopButton);
		d_ptr->stopButton->setVisible(false);
		d_ptr->mainLayout->addWidget(splitter);
	}
	else
	{
		d_ptr->stopButton = NULL;
		d_ptr->mainLayout->addWidget(d_ptr->progressBar);
	}

	d_ptr->messagesArea = new MgMessagesAreaWidget(this);
	d_ptr->messagesArea->registerSender(task);
	d_ptr->mainLayout->addWidget(d_ptr->messagesArea);

	connect(task,SIGNAL(started()),this,SLOT(onTaskStarted()));
	connect(task,SIGNAL(finished()),this,SLOT(onTaskFinished()));
	connect(task,SIGNAL(progress(int)),d_ptr->progressBar ,SLOT(setValue(int)));
	connect(task,SIGNAL(informationMessage(QString)),this ,SLOT(onInformationMessage(QString)));
	connect(task,SIGNAL(warningMessage(QString)),this ,SLOT(onWarningMessage(QString)));
	connect(task,SIGNAL(errorMessage(QString)),this ,SLOT(onErrorMessage(QString)));
	setLayout(d_ptr->mainLayout);
}



MgTaskViewer::~MgTaskViewer()
{
	delete d_ptr;
}

void MgTaskViewer::onTaskStarted()
{
	if(d_ptr->stopButton)
		d_ptr->stopButton->setVisible(true);
	d_ptr->progressBar->setVisible(true);
	d_ptr->statusLabel->setText("Status : running");
	Q_EMIT taskStarted();
}
void MgTaskViewer::onTaskFinished()
{
	if(d_ptr->stopButton)
		d_ptr->stopButton->setVisible(false);
	d_ptr->progressBar->setVisible(false);
	d_ptr->statusLabel->setText("Status : finished");
	Q_EMIT taskFinished();
}


