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
#ifndef MGLINESNUMBERSEXTRAAREA_H_
#define MGLINESNUMBERSEXTRAAREA_H_
#include <QWidget>

class MgBaseTextEdit;
class MgLinesNumbersExtraArea : public QWidget
{
public:
	MgLinesNumbersExtraArea(MgBaseTextEdit *edit);

    QSize sizeHint() const ;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool event(QEvent *event);

private:
    MgBaseTextEdit * m_editor;
};


#endif /* MGLINESNUMBERSEXTRAAREA_H_ */
