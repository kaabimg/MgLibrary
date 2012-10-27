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
#include "mgcurvesplotter.h"



#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtGui/QStylePainter>
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionFocusRect>
#include <QtGui/QMouseEvent>
#include <QDebug>

#include <math.h>

#include "mgcurve.h"

class MgZoomSettings
{
public:
	MgZoomSettings();

	void scroll(int dx, int dy);
	void scroll(qreal dx, qreal dy);
	void adjust();
	double spanX() const { return maxX - minX; }
	double spanY() const { return maxY - minY; }

	double minX;
	double maxX;
	int numXTicks;
	double minY;
	double maxY;
	int numYTicks;

private:
	static void adjustAxis(double &min, double &max, int &numTicks);
};


MgZoomSettings::MgZoomSettings()
{
	minX =  1000000000000.0;
	maxX = -1000000000000.0;
	numXTicks = 5;
	minY =  1000000000000.0;
	maxY = -1000000000000.0;
	numYTicks = 5;
}

void MgZoomSettings::scroll(int dx, int dy)
{
	double stepX = spanX() / numXTicks;
	minX += dx * stepX;
	maxX += dx * stepX;
	double stepY = spanY() / numYTicks;
	minY += dy * stepY;
	maxY += dy * stepY;
}

void MgZoomSettings::scroll(qreal dx, qreal dy)
{
	double min(minX),max(maxX);
	minX += dx * (max-min);
	maxX += dx * (max-min);
	min = minY; max =maxY;
	minY += dy * (max-min);
	maxY += dy * (max-min);
}

void MgZoomSettings::adjust()
{
	adjustAxis(minX, maxX, numXTicks);
	adjustAxis(minY, maxY, numYTicks);
}


void MgZoomSettings::adjustAxis(double &min, double &max, int &numTicks)
{
	const int MinTicks = 4;
	double grossStep = (max - min) / MinTicks;
	double step = pow(10.0, floor(log10(grossStep)));
	if (5 * step < grossStep)
	{
		step *= 5;
	}
	else if (2 * step < grossStep)
	{
		step *= 2;
	}
	numTicks = int(ceil(max / step) - floor(min / step));
	if (numTicks < MinTicks)
		numTicks = MinTicks;
	min = floor(min / step) * step;
	max = ceil(max / step) * step;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

struct MgCurvesPlotterPrivate
{
	enum { Margin = 50 };
	QList<MgCurve *> curves;
	QList<MgZoomSettings> zoomStack;
	int curZoom;
	bool rubberBandIsShown;
	QRect rubberBandRect;
	QColor backGroundColor,gridColor,zoomerColor,zoomerContourColor;
	MgCurvesPlotter::SelectionMode selectionMode;
	bool mousePressed;
	QPoint mouseLastPosition;

};


MgCurvesPlotter::MgCurvesPlotter(QWidget * parent):QWidget(parent),d_ptr(new MgCurvesPlotterPrivate)
{

	setAutoFillBackground(false);
	setAttribute(Qt::WA_OpaquePaintEvent, true);
	setAttribute(Qt::WA_NoSystemBackground, true);
//	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//	setFocusPolicy(Qt::StrongFocus);
	d_ptr->rubberBandIsShown = false;
	setZoomSettings(MgZoomSettings());



	d_ptr->backGroundColor = Qt::black;
	d_ptr->gridColor = Qt::lightGray;
	d_ptr->zoomerColor = QColor(Qt::blue);
	d_ptr->zoomerColor.setAlpha(200);
	d_ptr->zoomerContourColor =Qt::white;

	setMode(Zoomer);
	d_ptr->mousePressed = false;
}

MgCurvesPlotter::~MgCurvesPlotter()
{
	delete d_ptr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////




void MgCurvesPlotter::setZoomSettings(const MgZoomSettings &settings)
{
	d_ptr->zoomStack.clear();
	d_ptr->zoomStack.append(settings);
	d_ptr->curZoom = 0;
	update();
}

void MgCurvesPlotter::zoomOut()
{
	if (d_ptr->curZoom > 0)
	{
		--(d_ptr->curZoom);
		update();
	}
}

void MgCurvesPlotter::zoomIn()
{
	if (d_ptr->curZoom < d_ptr->zoomStack.count() - 1)
	{
		++(d_ptr->curZoom);
		update();
	}
}

void MgCurvesPlotter::addCurve(MgCurve * curve,bool refresh)
{
	d_ptr->curves<<curve;
	if(refresh)
		update();
}

void MgCurvesPlotter::removeCurve(const QString & id,bool refresh)
{
	foreach(MgCurve *curve ,d_ptr->curves)
	{
		if(curve->id() == id)
		{
			d_ptr->curves.removeOne(curve);
			if(refresh)
				update();
			return;
		}
	}
}
void MgCurvesPlotter::removeCurve(MgCurve * curve,bool refresh)
{
	d_ptr->curves.removeOne(curve);
	if(refresh)
		update();
}


void MgCurvesPlotter::setMode(SelectionMode mode)
{
	d_ptr->selectionMode = mode;
}


QSize MgCurvesPlotter::minimumSizeHint() const
{
	return QSize(6 * d_ptr->Margin, 4 * d_ptr->Margin);
}

QSize MgCurvesPlotter::sizeHint() const
{
	return QSize(12 * d_ptr->Margin, 8 * d_ptr->Margin);
}

void MgCurvesPlotter::paintEvent(QPaintEvent * /* event */)
{
	QPainter painter(this);
	painter.fillRect(rect(),d_ptr->backGroundColor);

	painter.setRenderHint(QPainter::Antialiasing, true);
	drawGrid(&painter);
	drawCurves(&painter);

	if (d_ptr->rubberBandIsShown)
	{
		painter.setPen(d_ptr->zoomerContourColor);
		painter.drawRect(d_ptr->rubberBandRect.normalized()
				.adjusted(0, 0, -1, -1));
	}
}

void MgCurvesPlotter::resizeEvent(QResizeEvent * /* event */)
{
	update();
}

void MgCurvesPlotter::enterEvent ( QEvent * )
{
	switch (d_ptr->selectionMode)
	{
		case Zoomer:
		{

		}
		break;

		case Hand:
		{
			setCursor(QCursor(Qt::OpenHandCursor));
		}
		break;

		default:
			break;
	}
}


void MgCurvesPlotter::mousePressEvent(QMouseEvent *event)
{
	QRect rect(d_ptr->Margin, d_ptr->Margin,width() - 2 * d_ptr->Margin, height() - 2 * d_ptr->Margin);
	if (event->button() == Qt::LeftButton)
	{

		switch (d_ptr->selectionMode)
		{
		case Zoomer:
		{
			if (rect.contains(event->pos()))
			{
				d_ptr->rubberBandIsShown = true;
				d_ptr->rubberBandRect.setTopLeft(event->pos());
				d_ptr->rubberBandRect.setBottomRight(event->pos());
				updateRubberBandRegion();
				setCursor(Qt::CrossCursor);
			}
		}
		break;
		case Hand:
		{
			d_ptr->mousePressed = true;
			setCursor(QCursor(Qt::ClosedHandCursor));
		}
		break;

		default:
			break;
		}
	}
}

void MgCurvesPlotter::mouseMoveEvent(QMouseEvent *event)
{

	switch (d_ptr->selectionMode)
	{
	case Zoomer:
	{
		if (d_ptr->rubberBandIsShown)
		{
			updateRubberBandRegion();
			d_ptr->rubberBandRect.setBottomRight(event->pos());
			updateRubberBandRegion();
		}
	}
	break;


	case Hand:
	{

		if(d_ptr->mousePressed)
		{
			if(d_ptr->mouseLastPosition == QPoint())
			{
				d_ptr->mouseLastPosition= event->pos();
				return;
			}
			QPointF delta = event->pos()-d_ptr->mouseLastPosition;

			delta.setX(-delta.x()/plotRect().width());
			delta.setY(delta.y()/plotRect().height());
			d_ptr->zoomStack[d_ptr->curZoom].scroll(delta.x(),delta.y());
			//d_ptr->zoomStack[d_ptr->curZoom].adjust();
			d_ptr->mouseLastPosition = event->pos();
			update();
		}

	}
	break;


	default:
		break;
	}


}


void MgCurvesPlotter::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() == Qt::LeftButton))
	{

		switch (d_ptr->selectionMode)
		{
		case Zoomer:
			if(d_ptr->rubberBandIsShown)
			{
				d_ptr->rubberBandIsShown = false;

				updateRubberBandRegion();
				unsetCursor();
				QRect rect = d_ptr->rubberBandRect.normalized();
				if (rect.width() < 4 || rect.height() < 4)
					return;
				rect.translate(-d_ptr->Margin, -d_ptr->Margin);
				MgZoomSettings prevSettings = d_ptr->zoomStack[d_ptr->curZoom];
				MgZoomSettings settings;
				double dx = prevSettings.spanX() / (width() - 2 * d_ptr->Margin);
				double dy = prevSettings.spanY() / (height() - 2 * d_ptr->Margin);
				settings.minX = prevSettings.minX + dx * rect.left();
				settings.maxX = prevSettings.minX + dx * rect.right();
				settings.minY = prevSettings.maxY - dy * rect.bottom();
				settings.maxY = prevSettings.maxY - dy * rect.top();
				settings.adjust();
				d_ptr->zoomStack.append(settings);
				zoomIn();
			}
			break;


		case Hand:
		{
			d_ptr->mousePressed = false;
			d_ptr->mouseLastPosition =QPoint();
			setCursor(Qt::OpenHandCursor);
		}
		break;

		default:
			break;
		}
	}
}





void MgCurvesPlotter::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Plus:
		zoomIn();
		break;
	case Qt::Key_Minus:
		zoomOut();
		break;
	case Qt::Key_Left:
		d_ptr->zoomStack[d_ptr->curZoom].scroll(-1, 0);
		update();
		break;
	case Qt::Key_Right:
		d_ptr->zoomStack[d_ptr->curZoom].scroll(+1, 0);
		update();
		break;
	case Qt::Key_Down:
		d_ptr->zoomStack[d_ptr->curZoom].scroll(0, -1);
		update();
		break;
	case Qt::Key_Up:
		d_ptr->zoomStack[d_ptr->curZoom].scroll(0, +1);
		update();
		break;
	default:
		QWidget::keyPressEvent(event);
		break;
	}
}


void MgCurvesPlotter::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numTicks = numDegrees / 15;
	if (event->orientation() == Qt::Horizontal)
	{
		d_ptr->zoomStack[d_ptr->curZoom].scroll(numTicks, 0);
	}
	else
	{
		d_ptr->zoomStack[d_ptr->curZoom].scroll(0, numTicks);
	}
	update();
}


QRect MgCurvesPlotter::plotRect()
{
	return QRect(d_ptr->Margin, d_ptr->Margin,width() - 2 * d_ptr->Margin, height() - 2 * d_ptr->Margin);
}


void MgCurvesPlotter::updateRubberBandRegion()
{
	QRect rect = d_ptr->rubberBandRect.normalized();
	update(rect.left(), rect.top(), rect.width(), 1);
	update(rect.left(), rect.top(), 1, rect.height());
	update(rect.left(), rect.bottom(), rect.width(), 1);
	update(rect.right(), rect.top(), 1, rect.height());
}



void MgCurvesPlotter::drawGrid(QPainter *painter)
{
	QRect rect(d_ptr->Margin, d_ptr->Margin,width() - 2 * d_ptr->Margin, height() - 2 * d_ptr->Margin);
	if (!rect.isValid())
		return;
	MgZoomSettings settings = d_ptr->zoomStack[d_ptr->curZoom];
	QPen quiteDark = d_ptr->gridColor ;// = palette().dark().color().light();
	QPen light = d_ptr->gridColor ;// palette().light().color();
	quiteDark.setStyle(Qt::DashLine);
	light.setStyle(Qt::DashLine);

	for (int i = 0; i <= settings.numXTicks; ++i)
	{
		int x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks);
		double label = settings.minX + (i * settings.spanX()/ settings.numXTicks);
		painter->setPen(quiteDark);
		painter->drawLine(x, rect.top(), x, rect.bottom());
		painter->setPen(light);
		painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
		painter->drawText(x - 50, rect.bottom() + 5, 100, 15,Qt::AlignHCenter | Qt::AlignTop,
				QString::number(label));
	}
	for (int j = 0; j <= settings.numYTicks; ++j)
	{
		int y = rect.bottom() - (j * (rect.height() - 1)/ settings.numYTicks);
		double label = settings.minY + (j * settings.spanY()/ settings.numYTicks);
		painter->setPen(quiteDark);
		painter->drawLine(rect.left(), y, rect.right(), y);
		painter->setPen(light);
		painter->drawLine(rect.left() - 5, y, rect.left(), y);
		painter->drawText(rect.left() - d_ptr->Margin, y - 10, d_ptr->Margin - 5, 20,
				Qt::AlignRight | Qt::AlignVCenter,
				QString::number(label));
	}
	painter->drawRect(rect.adjusted(0, 0, -1, -1));
}



void MgCurvesPlotter::drawCurves(QPainter *painter)
{

	MgZoomSettings settings = d_ptr->zoomStack[d_ptr->curZoom];
	QRect rect(d_ptr->Margin, d_ptr->Margin, width() - 2 * d_ptr->Margin, height() - 2 * d_ptr->Margin);
	if (!rect.isValid())
		return;
	painter->setClipRect(rect.adjusted(+1, +1, -1, -1));
	for(int i=0;i<d_ptr->curves.size();++i)
		drawCurve(painter,d_ptr->curves[i],settings,rect);
}

void MgCurvesPlotter::drawCurve(QPainter * painter, MgCurve * curve,const MgZoomSettings& settings,const QRect & rect)
{
	painter->setPen(curve->pen());
	MgCurveData * data = curve->data();
	int begin = data->firstIndexBefore(settings.minX);
	if(begin == -1)
		return;
	int end = data->firstIndexAfter(settings.maxX);
	if(end == -1)
		return;

	QPolygonF points(end-begin+1);
	qreal x,y,dx,dy;
	for(int i = begin;i<=end;++i)
	{
		dx = (*data)[i].x() - settings.minX;
		dy = (*data)[i].y() - settings.minY;
		x = rect.left() + (dx * (rect.width() - 1)/ settings.spanX());
		y = rect.bottom() - (dy * (rect.height() - 1)/ settings.spanY());
		points[i-begin] = QPointF(x, y);
	}

	painter->drawPolyline(points);
}



void MgCurvesPlotter::updateContentGeometry()
{
	MgZoomSettings settings;
	for (int i = 0;  i < d_ptr->curves.size(); ++ i)
	{
		settings.maxX = std::max(d_ptr->curves[i]->data()->maxX(),settings.maxX);
		settings.minX = std::min(d_ptr->curves[i]->data()->minX(),settings.minX);
		settings.maxY = std::max(d_ptr->curves[i]->data()->maxY(),settings.maxY);
		settings.minY = std::min(d_ptr->curves[i]->data()->minY(),settings.minY);
	}


	settings.maxX += (settings.maxX - settings.minX) /25 ;
	settings.minX -= (settings.maxX - settings.minX) /25 ;

	settings.maxY += (settings.maxY - settings.minY) /25 ;
	settings.minY -= (settings.maxY - settings.minY) /25 ;
	settings.adjust();
	setZoomSettings(settings);
}
