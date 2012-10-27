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
#include "mgfadeelement.h"



#include <QPropertyAnimation>
#include <QWidget>


MgFadeElement::MgFadeElement (QWidget * parent): enabled(false), m_parent(parent), m_fader(0)
{
	m_animator = new QPropertyAnimation;
	m_animator->setPropertyName("fader");
	m_animator->setTargetObject(this);
}

MgFadeElement:: ~MgFadeElement(){}


void MgFadeElement::setFader(float value)
{
	m_fader = value;
	m_parent->update();
}

void MgFadeElement::fadeIn()
{
	m_animator->stop();
	m_animator->setDuration(80);
	m_animator->setEndValue(40);
	m_animator->start();
}

void MgFadeElement::fadeOut()
{
	m_animator->stop();
	m_animator->setDuration(160);
	m_animator->setEndValue(0);
	m_animator->start();
}



