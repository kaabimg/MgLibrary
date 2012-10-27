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
#include "mgoutputpanetogglebutton.h"

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QFont>
#include <QtGui/QApplication>


MgOutputPaneToggleButton::MgOutputPaneToggleButton(int number, const QString &text,
                                                QWidget *parent)
    : QToolButton(parent)
    , m_number(QString::number(number))
    , m_text(text)

{
    setFocusPolicy(Qt::NoFocus);
    setCheckable(true);
    QFont fnt = QApplication::font();
    setFont(fnt);

}



QSize MgOutputPaneToggleButton::sizeHint() const
{
    ensurePolished();
    QSize s = fontMetrics().size(Qt::TextSingleLine, m_text);
    s *= 1.1;
    s.rwidth() += 26;
    s.rheight() += 4;
    return s.expandedTo(QApplication::globalStrut());
}

void MgOutputPaneToggleButton::paintEvent(QPaintEvent *)
{
    const QFontMetrics fm = fontMetrics();
    const int baseLine = (height() - fm.height() + 1) / 2 + fm.ascent();
    const int numberWidth = fm.width(m_number);

    QPainter p(this);
    p.setRenderHint(QPainter::HighQualityAntialiasing,true);
    QPainterPath path;
    path.addRoundRect(rect(),50);
   	p.fillPath(path,Qt::black);

   	QFont f= font();


    if(isChecked())
    {
    	p.setPen(Qt::white);
    	f.setPointSizeF(f.pointSizeF()* 1.1);
    }
    else
    	p.setPen(Qt::gray);

    p.setFont(f);
    p.drawText((20 - numberWidth) / 2, baseLine, m_number);
    int leftPart = 22;
    p.drawText(leftPart, baseLine, fm.elidedText(m_text, Qt::ElideRight, width() - leftPart - 1));
}
