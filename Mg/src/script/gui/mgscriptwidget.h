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
#ifndef MGSCRIPTWIDGET_H_
#define MGSCRIPTWIDGET_H_

//MG_INCLUDE_INFO:MgScriptWidget

#include <MgCore/MgGlobal>
#include <MgGui/MgAnimatedStackedWidget>

class MgScriptEngine;

MG_USE_PRIVATE_CLASS(MgScriptWidget)

class MgScriptWidget : public MgAnimatedStackedWidget
{
	Q_OBJECT
public:
	MgScriptWidget(QWidget * parent=0);
	virtual ~MgScriptWidget();

	MgScriptEngine * scriptEngine()const;
	void setScriptEngine(MgScriptEngine *);

protected Q_SLOTS:
	void makeConsoleCurrent();
	void makeJavaScriptEditorCurrent();

private:
	MG_PRIVATE_CLASS(MgScriptWidget)
	Q_DISABLE_COPY(MgScriptWidget)
};

#endif /* MGSCRIPTWIDGET_H_ */
