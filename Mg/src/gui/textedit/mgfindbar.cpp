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
#include "mgfindbar.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QToolButton>
#include <QApplication>
#include <QStyle>
struct MgFindBarPrivate
{
	QFormLayout * formLayout;
	QHBoxLayout * horizontalLayout;
	QLineEdit * findLineEdit, * replaceWithLineEdit;
	QCheckBox * isRegularExpressionCheckBox, * isCaseSensitiveCheckBox;
	QToolButton * findNext, * findPrevious;
};

MgFindBar::MgFindBar(QWidget * parent):QWidget(parent),
		d_ptr(new MgFindBarPrivate)
{

	d_ptr->findLineEdit = new QLineEdit(this);
//	d_ptr->replaceWithLineEdit = new QLineEdit(this);
	d_ptr->findNext = new QToolButton(this);
	d_ptr->findNext->setIcon(qApp->style()->standardIcon(QStyle::SP_ArrowRight));
	d_ptr->findPrevious = new QToolButton(this);
	d_ptr->findPrevious->setIcon(qApp->style()->standardIcon(QStyle::SP_ArrowLeft));

	d_ptr->horizontalLayout = new QHBoxLayout;
	d_ptr->horizontalLayout->addWidget(d_ptr->findLineEdit);
	d_ptr->horizontalLayout->addWidget(d_ptr->findPrevious);
	d_ptr->horizontalLayout->addWidget(d_ptr->findNext);

	d_ptr->isRegularExpressionCheckBox = new QCheckBox(this);
	d_ptr->isCaseSensitiveCheckBox = new QCheckBox(this);

	d_ptr->formLayout = new QFormLayout;
	d_ptr->formLayout->addRow("<font color='white'>Find</font>",d_ptr->horizontalLayout);
	d_ptr->formLayout->addRow("<font color='white'>Regular expression</font>",d_ptr->isRegularExpressionCheckBox);
	d_ptr->formLayout->addRow("<font color='white'>Case sensitive</font>",d_ptr->isCaseSensitiveCheckBox);

	setLayout(d_ptr->formLayout);

	setStyleSheet("MgFindBar{background-color: rgb(50,50,50)}");
}

MgFindBar::~MgFindBar() {
	// TODO Auto-generated destructor stub
}

