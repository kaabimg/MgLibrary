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
#include "mgobjectpropertieseditor.h"

#include "mgobjectpropertiesmanager.h"

#include <QtVariantPropertyManager>
#include <QtTreePropertyBrowser>
#include <QtVariantEditorFactory>
#include <QVBoxLayout>

struct MgObjectPropertiesEditorPrivate
{
	QObject * object;
	QtTreePropertyBrowser *browser;
	QtVariantEditorFactory *factory;
	QtVariantPropertyManager * manager;
	MgObjectPropertiesManager * propertiesManager;
};

MgObjectPropertiesEditor::MgObjectPropertiesEditor(QWidget * parent)
	:QWidget(parent),d_ptr(new MgObjectPropertiesEditorPrivate)
{
	d_ptr->browser = new QtTreePropertyBrowser(this);
	d_ptr->factory = new QtVariantEditorFactory(this);
	d_ptr->manager = new QtVariantPropertyManager(this);
	d_ptr->propertiesManager = new MgObjectPropertiesManager(d_ptr->manager,d_ptr->browser,this);
	d_ptr->browser->setFactoryForManager(d_ptr->manager,d_ptr->factory);

	d_ptr->object = NULL;
	QVBoxLayout* layout =new QVBoxLayout(this);
	layout->addWidget(d_ptr->browser);
	setLayout(layout);
}

MgObjectPropertiesEditor::~MgObjectPropertiesEditor()
{
	delete d_ptr;
}

QObject *MgObjectPropertiesEditor::object()const
{
	return d_ptr->object;
}

void MgObjectPropertiesEditor::setObject(QObject * obj)
{
	d_ptr->manager->clear();
	d_ptr->propertiesManager->setcontrolledObject(obj);
	d_ptr->object = obj;

}
