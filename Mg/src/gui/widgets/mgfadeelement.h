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
#ifndef MGFADEELEMENT_H_
#define MGFADEELEMENT_H_

//MG_INCLUDE_INFO:MgFadeElement

#include <QObject>
#include <QIcon>
#include <QString>

class QPropertyAnimation;
class QWidget;

class MgFadeElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float fader READ fader WRITE setFader)
public:
    MgFadeElement (QWidget *parent);
    ~MgFadeElement();
    float fader() const{ return m_fader; }
    void setFader(float value);

    void fadeIn();
    void fadeOut();

	QString id;
	QString title;
	QString text;
	QString toolTip;
	QIcon leftIcon;
	QIcon rightIcon;
	bool enabled;

private:
    QPropertyAnimation *  m_animator;
    QWidget * m_parent;
    float m_fader;
};

#endif /* MGFADEELEMENT_H_ */
