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
#include "mgscriptwidget.h"
#include "mgcommandprompt.h"
#include "mgjavascripteditor.h"
#include "../core/mgscriptengine.h"

#include <MgGui/MgNavigationBar>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

struct MgScriptWidgetPrivate
{
	MgWidgetWithNavigationBar * consoleWidget;
	MgWidgetWithNavigationBar * jsEditorWidget;
	MgCommandPrompt * console;
	MgJavaScriptEditor * jsEditor;
	QTimer updateTextTimer;
};

MgScriptWidget::MgScriptWidget(QWidget * parent):MgAnimatedStackedWidget(parent)
{
	d_ptr = new MgScriptWidgetPrivate();

	d_ptr->console = new MgCommandPrompt();//parent will be set in MgWidgetWithNavigationBar
	d_ptr->consoleWidget = new MgWidgetWithNavigationBar(d_ptr->console,MgNavigationBar::Forward,this);

	connect(d_ptr->consoleWidget->navigationBar(),SIGNAL(forwardRequest()),
			this,SLOT(makeJavaScriptEditorCurrent()));
	addWidget(d_ptr->consoleWidget);

	d_ptr->jsEditor = new MgJavaScriptEditor();
	d_ptr->jsEditorWidget =  new MgWidgetWithNavigationBar(d_ptr->jsEditor,MgNavigationBar::Backward,this);

	connect(d_ptr->jsEditorWidget->navigationBar(),SIGNAL(backwardRequest()),
			this,SLOT(makeConsoleCurrent()));
	addWidget(d_ptr->jsEditorWidget);
	setCurrentWidget(d_ptr->consoleWidget);

	d_ptr->updateTextTimer.setInterval(500);
	d_ptr->updateTextTimer.setSingleShot(true);
	connect(&d_ptr->updateTextTimer,SIGNAL(timeout()),this,SLOT(updateCachedProgram()));
	connect(d_ptr->jsEditor,SIGNAL(textChanged()),&d_ptr->updateTextTimer,SLOT(start()));
}

MgScriptWidget::~MgScriptWidget()
{
	delete d_ptr;
}

MgScriptEngine * MgScriptWidget::scriptEngine()const
{
	return d_ptr->console->scriptEngine();
}

void MgScriptWidget::setScriptEngine(MgScriptEngine * engine)
{
	d_ptr->console->setScriptEngine(engine);
}

void MgScriptWidget::makeConsoleCurrent()
{
	if(d_ptr->console->scriptEngine())
		d_ptr->console->scriptEngine()->setCachedProgram(scriptProgram());

	slideToWidget(d_ptr->consoleWidget,RightToLeft);
}
void MgScriptWidget::makeJavaScriptEditorCurrent()
{
	if(d_ptr->console->scriptEngine())
		d_ptr->jsEditor->setPlainText(d_ptr->console->scriptEngine()->cachedProgram());

	slideToWidget(d_ptr->jsEditorWidget,LeftToRight);
}
QString MgScriptWidget::scriptProgram()const
{
	return d_ptr->jsEditor->toPlainText();
}
void MgScriptWidget::updateCachedProgram()
{
	if(scriptEngine())
		scriptEngine()->setCachedProgram(scriptProgram());
}
