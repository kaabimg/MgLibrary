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
** along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
** 
****************************************************************************/
#include <QApplication>


#include <MgTest/MgQObjectTreeInfo>
#include <MgTest/MgApplicationMonitor>
#include <MgTest/MgEventsView>
#include <QStyle>

//========================

#include <MgGui/MgMainWindow>
#include <MgGui/MgTabWidget>
#include <MgScript/MgCommandPrompt>
#include <MgGui/MgMessagesAreaWidget>
#include <MgGui/MgMultiWidgets>
#include <MgGui/MgMessagesAreaWidget>
#include <MgScript/MgScriptEngine>
#include <MgCore/MgGlobal>


#include "guitestclass.h"

//================================================================================


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GuiTestClass * w = new GuiTestClass;

	MgApplicationMonitor monitor;
	MgMainWindow mainWindow;

	MgMessagesAreaWidget * messagesArea = new MgMessagesAreaWidget;
	MgEventsView * eventsView = new MgEventsView;


	MgCommandPrompt * commandPrompt = new MgCommandPrompt;
	MgScriptEngine * scriptEngine = monitor.scriptEngine();
	commandPrompt->setScriptEngine(scriptEngine);
	scriptEngine->registerObject("console",commandPrompt);

	mainWindow.addOutputPane("console",commandPrompt);
	mainWindow.addOutputPane("Messages area",messagesArea);

	mainWindow.addSidebarWidget("Hierarchy",
			a.style()->standardPixmap(QStyle::SP_DriveNetIcon),
			new MgQObjectTreeInfo(w));


	mainWindow.addSidebarWidget("Test widget",
			a.style()->standardPixmap(QStyle::SP_ComputerIcon),
			w);

	mainWindow.addSidebarWidget("Events",
			a.style()->standardPixmap(QStyle::SP_MediaPlay),
			eventsView);


	QObject::connect(&monitor,SIGNAL(eventMessage(QString,QString,QString)),
			eventsView,SLOT(addEvent(QString,QString,QString)));

	messagesArea->registerSender(&monitor);
	monitor.registerObject(w);

	mainWindow.resize(800,600);
	mainWindow.show();

	return a.exec();
}
