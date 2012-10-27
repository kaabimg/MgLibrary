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
#ifndef MGGRIDGRAPHICSVIEW_H_
#define MGGRIDGRAPHICSVIEW_H_


#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QSet>

#define ZOOM_IN_FACTOR 1.18921
#define ZOOM_OUT_FACTOR 0.840896
#define ZOOM_MIN 0.29
#define ZOOM_MAX 2.4

class MgViewGridLayout;
class QStateMachine;
class QState;
class QGraphicsOpacityEffect;
class QGraphicsDropShadowEffect;
class MgRectGraphicsObject;

class MgGridGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MgGridGraphicsView(QWidget *parent = 0);
    ~MgGridGraphicsView();

    void relayout();

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void zoomFit();

    inline qreal zoom() const { return m_currentZoomLevel; }
    void setZoom(qreal z);

    void addItem(MgRectGraphicsObject *);

Q_SIGNALS:
    void detailsRequested();
    void zoomLevelChanged(qreal zoomLevel);

protected Q_SLOTS:
	void updateSelection(bool,bool);

protected:
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);
    void updateLayout();
    void clear();
private:
    MgViewGridLayout * m_layout;
    QGraphicsWidget * m_itemsContainer;
    qreal m_currentZoomLevel;
    QSet<MgRectGraphicsObject *> m_selectedItems;
};

#endif /* MGGRIDGRAPHICSVIEW_H_ */
