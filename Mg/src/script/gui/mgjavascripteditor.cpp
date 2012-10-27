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
#include "mgjavascripteditor.h"
#include "mgjavascriptsyntaxhighlighter.h"

#include <QDropEvent>
#include <QMimeData>
#include <QFile>
#include <QDebug>

MgJavaScriptEditor::MgJavaScriptEditor(QWidget * parent):MgBaseTextEdit(parent)
{
	new QScriptSyntaxHighlighter(document());
}

MgJavaScriptEditor::~MgJavaScriptEditor(){}

void MgJavaScriptEditor::dropEvent(QDropEvent *e)
{
	const QMimeData * mimeData = e->mimeData();
	if(mimeData)
	{
		QString text = mimeData->text().simplified().trimmed();
		if(text.startsWith("file://"))
		{
			text.remove(0,7);
			QFile file(text);
			if(file.open(QFile::ReadOnly | QFile::Text))
			{
				clear();
				setPlainText(file.readAll());
				file.close();
				return;
			}
		}
	}
	MgBaseTextEdit::dropEvent(e);
}
