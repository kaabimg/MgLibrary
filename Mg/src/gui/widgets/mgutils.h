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
#ifndef UTILS_H_
#define UTILS_H_

#include <QtGui/QPixmapCache>
#include <QtGui/QWidget>
#include <QtCore/QRect>
#include <QtGui/QPainter>
#include <QtGui/QApplication>
#include <QtGui/QPalette>
#include <QtGui/QStyleOption>
#include <QtGui/QLinearGradient>
#include <QtCore/QObject>



#include <MgCore/MgGlobal>

//defined in opengl module
void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);

MG_BEGIN_NAMESPACE(MgGuiHelpers)


///////////////////////////////////////

//static QColor requestedBaseColor = QColor(Qt::black);
static QColor baseColor = QColor(Qt::black);
static int navigationWidgetHeight (24);
static const float fontSize (8.5);
static const int iconSize = 32;
static QColor sidebarShadow =  QColor(0, 0, 0, 40);


///////////////////////////////////////


static void mgDrawIconWithShadow(const QIcon &icon, const QRect &rect, QPainter *p, QIcon::Mode iconMode,
		int radius = 3, const QColor &color = QColor(0, 0, 0, 130),
		const QPoint &offset = QPoint(1, -2))
{
	QPixmap cache;
	QString pixmapName = QString("icon %0 %1 %2").arg(icon.cacheKey()).arg(iconMode).arg(rect.height());

	if (!QPixmapCache::find(pixmapName, cache))
	{
		QPixmap px = icon.pixmap(rect.size());
		cache = QPixmap(px.size() + QSize(radius * 2, radius * 2));
		cache.fill(Qt::transparent);

		QPainter cachePainter(&cache);
		if (iconMode == QIcon::Disabled) {
			QImage im = px.toImage().convertToFormat(QImage::Format_ARGB32);
			for (int y=0; y<im.height(); ++y) {
				QRgb *scanLine = (QRgb*)im.scanLine(y);
				for (int x=0; x<im.width(); ++x) {
					QRgb pixel = *scanLine;
					char intensity = qGray(pixel);
					*scanLine = qRgba(intensity, intensity, intensity, qAlpha(pixel));
					++scanLine;
				}
			}
			px = QPixmap::fromImage(im);
		}

		// Draw shadow
		QImage tmp(px.size() + QSize(radius * 2, radius * 2 + 1), QImage::Format_ARGB32_Premultiplied);
		tmp.fill(Qt::transparent);

		QPainter tmpPainter(&tmp);
		tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
		tmpPainter.drawPixmap(QPoint(radius, radius), px);
		tmpPainter.end();

		// blur the alpha channel
		QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
		blurred.fill(Qt::transparent);
		QPainter blurPainter(&blurred);
		qt_blurImage(&blurPainter, tmp, radius, false, true);
		blurPainter.end();

		tmp = blurred;

		// blacken the image...
		tmpPainter.begin(&tmp);
		tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
		tmpPainter.fillRect(tmp.rect(), color);
		tmpPainter.end();

		tmpPainter.begin(&tmp);
		tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
		tmpPainter.fillRect(tmp.rect(), color);
		tmpPainter.end();

		// draw the blurred drop shadow...
		cachePainter.drawImage(QRect(0, 0, cache.rect().width(), cache.rect().height()), tmp);

		// Draw the actual pixmap...
		cachePainter.drawPixmap(QPoint(radius, radius) + offset, px);
		QPixmapCache::insert(pixmapName, cache);
	}

	QRect targetRect = cache.rect();
	targetRect.moveCenter(rect.center());
	p->drawPixmap(targetRect.topLeft() - offset, cache);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int clamp(float x)
{
	const int val = x > 255 ? 255 : static_cast<int>(x);
	return val < 0 ? 0 : val;
}


static QColor highlightColor()
{
	QColor highlight = baseColor.lighter(230);
	highlight.setHsv(highlight.hue(),
			clamp(highlight.saturation()),
			clamp(highlight.value() * 1.16));
	return highlight;
}


static QColor borderColor()
{
	QColor result = baseColor;
	result.setHsv(result.hue(),
			result.saturation(),
			result.value() / 2);
	return result;
}

static QColor shadowColor()
{
	QColor result = baseColor;
	result.setHsv(result.hue(),
			clamp(result.saturation() * 1.1),
			clamp(result.value() * 0.70));
	return result;
}

static QColor sidebarHighlight() { return QColor(255, 255, 255, 40); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////:
static void verticalGradientHelper(QPainter *p, const QRect &spanRect, const QRect &rect)
{
	QColor highlight = highlightColor();
	QColor shadow = shadowColor();
	QLinearGradient grad(spanRect.topRight(), spanRect.topLeft());
	grad.setColorAt(0, highlight.lighter(117));
	grad.setColorAt(1, shadow.darker(109));
	p->fillRect(rect, grad);

	QColor light(255, 255, 255, 80);
	p->setPen(light);
	p->drawLine(rect.topRight() - QPoint(1, 0), rect.bottomRight() - QPoint(1, 0));
	QColor dark(0, 0, 0, 90);
	p->setPen(dark);
	p->drawLine(rect.topLeft(), rect.bottomLeft());
}

static void verticalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect)
{

	QString key;
	QColor keyColor = baseColor;
	key.sprintf("mh_vertical %d %d %d %d %d",
			spanRect.width(), spanRect.height(), clipRect.width(),
			clipRect.height(), keyColor.rgb());;

	QPixmap pixmap;
	if (!QPixmapCache::find(key, pixmap)) {
		pixmap = QPixmap(clipRect.size());
		QPainter p(&pixmap);
		QRect rect(0, 0, clipRect.width(), clipRect.height());
		verticalGradientHelper(&p, spanRect, rect);
		p.end();
		QPixmapCache::insert(key, pixmap);
	}

	painter->drawPixmap(clipRect.topLeft(), pixmap);

}

static void horizontalGradientHelper(QPainter *p, const QRect &spanRect, const
		QRect &rect)
{
	QColor base = baseColor;
	QColor highlight = highlightColor();
	QColor shadow = shadowColor();
	QLinearGradient grad(rect.topLeft(), rect.bottomLeft());
	grad.setColorAt(0, highlight.lighter(120));
	if (rect.height() == navigationWidgetHeight)
	{
		grad.setColorAt(0.4, highlight);
		grad.setColorAt(0.401, base);
	}
	grad.setColorAt(1, shadow);
	p->fillRect(rect, grad);

	QLinearGradient shadowGradient(spanRect.topLeft(), spanRect.topRight());
	shadowGradient.setColorAt(0, QColor(0, 0, 0, 30));
	QColor lighterHighlight;
	lighterHighlight = highlight.lighter(130);
	lighterHighlight.setAlpha(100);
	shadowGradient.setColorAt(0.7, lighterHighlight);
	shadowGradient.setColorAt(1, QColor(0, 0, 0, 40));
	p->fillRect(rect, shadowGradient);
}

static void horizontalGradient(QPainter *painter, const QRect &spanRect, const QRect &clipRect)
{

	QString key;
	QColor keyColor = baseColor;
	key.sprintf("mh_horizontal %d %d %d %d %d %d",
			spanRect.width(), spanRect.height(), clipRect.width(),
			clipRect.height(), keyColor.rgb(), spanRect.x());

	QPixmap pixmap;
	if (!QPixmapCache::find(key, pixmap))
	{
		pixmap = QPixmap(clipRect.size());
		QPainter p(&pixmap);
		QRect rect = QRect(0, 0, clipRect.width(), clipRect.height());
		horizontalGradientHelper(&p, spanRect, rect);
		p.end();
		QPixmapCache::insert(key, pixmap);
	}

	painter->drawPixmap(clipRect.topLeft(), pixmap);


}

static void drawArrow(QStyle::PrimitiveElement element, QPainter *painter, const QStyleOption *option)
{
    // From windowsstyle but modified to enable AA
    if (option->rect.width() <= 1 || option->rect.height() <= 1)
        return;

    QRect r = option->rect;
    int size = qMin(r.height(), r.width());
    QPixmap pixmap;
    QString pixmapName;
    pixmapName.sprintf("arrow-%s-%d-%d-%d-%lld",
                       "$qt_ia",
                       uint(option->state), element,
                       size, option->palette.cacheKey());
    if (!QPixmapCache::find(pixmapName, pixmap)) {
        int border = size/5;
        int sqsize = 2*(size/2);
        QImage image(sqsize, sqsize, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter imagePainter(&image);
        imagePainter.setRenderHint(QPainter::Antialiasing, true);
        imagePainter.translate(0.5, 0.5);
        QPolygon a;
        switch (element) {
            case QStyle::PE_IndicatorArrowUp:
                a.setPoints(3, border, sqsize/2,  sqsize/2, border,  sqsize - border, sqsize/2);
                break;
            case QStyle::PE_IndicatorArrowDown:
                a.setPoints(3, border, sqsize/2,  sqsize/2, sqsize - border,  sqsize - border, sqsize/2);
                break;
            case QStyle::PE_IndicatorArrowRight:
                a.setPoints(3, sqsize - border, sqsize/2,  sqsize/2, border,  sqsize/2, sqsize - border);
                break;
            case QStyle::PE_IndicatorArrowLeft:
                a.setPoints(3, border, sqsize/2,  sqsize/2, border,  sqsize/2, sqsize - border);
                break;
            default:
                break;
        }

        int bsx = 0;
        int bsy = 0;

        if (option->state & QStyle::State_Sunken) {
            bsx = qApp->style()->pixelMetric(QStyle::PM_ButtonShiftHorizontal);
            bsy = qApp->style()->pixelMetric(QStyle::PM_ButtonShiftVertical);
        }

        QRect bounds = a.boundingRect();
        int sx = sqsize / 2 - bounds.center().x() - 1;
        int sy = sqsize / 2 - bounds.center().y() - 1;
        imagePainter.translate(sx + bsx, sy + bsy);

        if (!(option->state & QStyle::State_Enabled)) {
            QColor foreGround(150, 150, 150, 150);
            imagePainter.setBrush(option->palette.mid().color());
            imagePainter.setPen(option->palette.mid().color());
        } else {
            QColor shadow(0, 0, 0, 100);
            imagePainter.translate(0, 1);
            imagePainter.setPen(shadow);
            imagePainter.setBrush(shadow);
            QColor foreGround(255, 255, 255, 210);
            imagePainter.drawPolygon(a);
            imagePainter.translate(0, -1);
            imagePainter.setPen(foreGround);
            imagePainter.setBrush(foreGround);
        }
        imagePainter.drawPolygon(a);
        imagePainter.end();
        pixmap = QPixmap::fromImage(image);
        QPixmapCache::insert(pixmapName, pixmap);
    }
    int xOffset = r.x() + (r.width() - size)/2;
    int yOffset = r.y() + (r.height() - size)/2;
    painter->drawPixmap(xOffset, yOffset, pixmap);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



MG_END_NAMESPACE




#endif /* UTILS_H_ */
