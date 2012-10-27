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
#ifndef MGCURVESPLOTTER_H_
#define MGCURVESPLOTTER_H_

//MG_INCLUDE_INFO:MgCurvesPlotter

#include <QtGui/QWidget>
#include <QtCore/QRect>
#include <MgCore/MgGlobal>
class MgZoomSettings;
class MgCurve;


MG_USE_PRIVATE_CLASS(MgCurvesPlotter)

class MgCurvesPlotter :public QWidget
{
	Q_OBJECT
public:

	enum SelectionMode{Zoomer,Hand};
	Q_ENUMS(SelectionMode)


	explicit MgCurvesPlotter(QWidget * parent=0);
	virtual ~MgCurvesPlotter();

	void addCurve(MgCurve *,bool refresh=false);
	void removeCurve(const QString &,bool refresh=false);
	void removeCurve(MgCurve *,bool refresh=false);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void updateContentGeometry();

public slots:
	void zoomIn();
	void zoomOut();
	void setMode(SelectionMode);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent *);
    void enterEvent ( QEvent * );


private:
    void updateRubberBandRegion();
    void drawGrid(QPainter *painter);
    void drawCurves(QPainter *painter);
    void drawCurve(QPainter *, MgCurve * ,const MgZoomSettings&,const QRect &);
    void setZoomSettings(const MgZoomSettings &settings);

    QRect plotRect();

	MG_PRIVATE_CLASS(MgCurvesPlotter)
    Q_DISABLE_COPY(MgCurvesPlotter)


};

#endif /* MGCURVESPLOTTER_H_ */
