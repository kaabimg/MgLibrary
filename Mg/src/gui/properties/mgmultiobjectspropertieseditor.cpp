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
#include "mgmultiobjectspropertieseditor.h"
#include "mgobjectpropertieseditor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QResizeEvent>



MgMultiObjectsPropertiesEditor::MgMultiObjectsPropertiesEditor(QWidget * parent)
	:QSplitter(parent)
{
	setOrientation(Qt::Vertical);
	setChildrenCollapsible(false);

	QPalette p;

	setAutoFillBackground( true );
	p = palette();
	p.setColor(backgroundRole(),QColor(75,75,75));
	setPalette(p);
}

MgMultiObjectsPropertiesEditor::~MgMultiObjectsPropertiesEditor(){}



void MgMultiObjectsPropertiesEditor::appendObject(const QString & title,QObject* obj)
{

	QWidget  *container = new QWidget(this);
	QVBoxLayout * layout = new QVBoxLayout;
	container->setLayout(layout);
	MgObjectPropertiesEditor * editor = new MgObjectPropertiesEditor(container);
	editor->setObject(obj);


	QLabel * label = new QLabel(container);
	QPalette p = container->palette();
	p.setColor(QPalette::WindowText,Qt::white);
	label->setPalette(p);
	label->setText(title);

	layout->addWidget(label);
	layout->addWidget(editor);


	addWidget(container);
}
