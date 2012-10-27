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
#include "mglinesnumbersextraarea.h"

#include "mgbasetextedit.h"
#include <QTextBlock>
#include <QPainter>
#include <QCursor>

MgLinesNumbersExtraArea::MgLinesNumbersExtraArea(MgBaseTextEdit *edit)
: QWidget(edit),m_editor(edit)
{
	setMouseTracking(true);
}

QSize MgLinesNumbersExtraArea::sizeHint() const
{
	return QSize(m_editor->linesNumbersAreaWidth(), 0);
}

void MgLinesNumbersExtraArea::paintEvent(QPaintEvent *e)
{
    QRect rect = e->rect();
    QPalette pal = palette();
    pal.setCurrentColorGroup(QPalette::Active);
    QPainter painter(this);
    painter.fillRect(rect, Qt::lightGray);
    const QFontMetrics fm(m_editor->fontMetrics());

    int linesNumbersAreaWidth = width();

    painter.fillRect(rect, Qt::white);//lines numbers

    painter.setPen(QPen(pal.color(QPalette::Background), 2));
    painter.drawLine(rect.x() + linesNumbersAreaWidth-1, rect.top(), rect.x() + linesNumbersAreaWidth-1, rect.bottom());

    painter.setRenderHint(QPainter::Antialiasing);

    QTextBlock block = m_editor->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    qreal top = m_editor->blockBoundingGeometry(block).translated(m_editor->contentOffset()).top();
    qreal bottom = top + m_editor->blockBoundingRect(block).height();

    painter.setPen(QColor(Qt::gray));
    while (block.isValid() && top <= rect.bottom())
    {
        if (block.isVisible() && bottom >= rect.top())
        {

            int lineNumber = blockNumber + m_editor->baseLineNumber();
            QString number = QString::number(lineNumber);
            painter.drawText(rect.x() , (int)top, rect.x() + linesNumbersAreaWidth  - 4,
                             fm.height(), Qt::AlignCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + m_editor->blockBoundingRect(block).height();
        ++blockNumber;
    }
}
void MgLinesNumbersExtraArea::mousePressEvent(QMouseEvent *e)
{
    QTextCursor cursor = m_editor->cursorForPosition(QPoint(0, e->pos().y()));
    cursor.setPosition(cursor.block().position());
}
void MgLinesNumbersExtraArea::mouseMoveEvent(QMouseEvent *e)
{
    QTextCursor cursor = m_editor->cursorForPosition(QPoint(0, e->pos().y()));
    cursor.setPosition(cursor.block().position());
}
void MgLinesNumbersExtraArea::mouseReleaseEvent(QMouseEvent *e)
{
    QTextCursor cursor = m_editor->cursorForPosition(QPoint(0, e->pos().y()));
    cursor.setPosition(cursor.block().position());
}
bool MgLinesNumbersExtraArea::event(QEvent *e)
{
    if (e->type() == QEvent::ToolTip)
    {
        // ### show informations
        return true;
    }

	return QWidget::event(e);
}





