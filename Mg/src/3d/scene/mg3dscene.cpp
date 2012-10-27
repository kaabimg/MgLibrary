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
#include "mg3dscene.h"

#include <Qt3D/qglpainter.h>
#include <Qt3D/qglcamera.h>
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qglscenenode.h>
#include <Qt3D/qglsphere.h>
#include <Qt3D/qglcylinder.h>
#include <Qt3D/qgraphicsscale3d.h>
#include <Qt3D/qglshaderprogrameffect.h>
#include <Qt3D/qgeometrydata.h>
#include <Qt3D/qvector3darray.h>
#include <Qt3D/qgltexture2d.h>
#include <Qt3D/qglcube.h>
#include <QPainter>
#include <QResizeEvent>

#include <QGLShaderProgram>

#include "../coordinates/mg3dreference.h"
#include "../scenebuilder/mgparametericlinebuilder.h"
#include "../utils/mg3dhelpers.h"
#include "../shaders/fbodisplay/mgtexturedrawshader.h"
#include "../shaders/fbodisplay/mgfbodisplayshader.h"

#include <QPropertyAnimation>
#include <QList>
#include <QTimer>
#include <QTime>

#include <QGLFramebufferObject>

#include <Qt3D/qglframebufferobjectsurface.h>
#include <Qt3D/qgllightmodel.h>


struct MgFpsManager
{
	MgFpsManager():historySize(10){}
	void addNewTime(int t)
	{
		times.append(t);
		if(times.size()>historySize)
			times.removeFirst();
	}
	QString fpsString()const
	{
		int total = 0;
		for (int i = 0; i <times.size() ; ++i)
			total+=times[i];
		return QString("Average FPS : %0").arg((1000 * times.size())/total);
	}

	QList<int> times;
	int historySize;

};


float Mg3dScene::remapVal(float value,float origin_low,float origin_high,float dest_low,float dest_high)
{
	return dest_low + (dest_high - dest_low) * (value - origin_low) / (origin_high - origin_low);
}


struct Mg3dScenePrivate
{
	QGLSceneNode *axisNode,*gridsNode;
	Mg3DReference * reference;
	bool showReference,showGrid;
	QGeometryData fboVertices;
	QStringList stateTextList;
	QTime fpsTime;
	MgFpsManager fpsManager;
	MgTextureDrawShader textureDisplayShader;
	MgFboDisplayShader fboDisplayShader;
};



Mg3dScene::Mg3dScene(QWidget*parent):QGLView(parent),d_ptr(new Mg3dScenePrivate)
{

	/////////////////////

	d_ptr->showGrid = false;
	d_ptr->showReference = false;

	d_ptr->reference = new Mg3DReference();
	d_ptr->reference->setAxisLenght(20);

	d_ptr->axisNode = d_ptr->reference->createReferenceAxis();
	d_ptr->gridsNode = d_ptr->reference->createReferenceGrids();
	d_ptr->axisNode->setParent(this);
	d_ptr->gridsNode->setParent(this);


	d_ptr->fboVertices.appendVertex(QVector3D(-1,-1,0));//0
	d_ptr->fboVertices.appendVertex(QVector3D(1,-1,0));//1
	d_ptr->fboVertices.appendVertex(QVector3D(1,1,0));//2
	d_ptr->fboVertices.appendVertex(QVector3D(-1,1,0));//3

	d_ptr->fboVertices.appendIndices(0,1,2);
	d_ptr->fboVertices.appendIndices(2,3,0);


	setStateTextSize(1);
	setStateText(0,"FPS : undefined");
}


void Mg3dScene::drawFboVertices(QGLPainter * painter)
{
	d_ptr->fboVertices.draw(painter,0,6,QGL::Triangles);
}



Mg3dScene::~Mg3dScene()
{
	delete d_ptr;
}

QGLFramebufferObjectSurface * Mg3dScene::createFboSurface(const QSize & size)const
{
	return new QGLFramebufferObjectSurface
			(
					new QGLFramebufferObject(size, QGLFramebufferObject::Depth),
					context()
			);
}
void Mg3dScene::destroyFboSurface(QGLFramebufferObjectSurface * surface)
{
	if(!surface)
		return;

	delete surface->framebufferObject();
	delete surface;
}

void Mg3dScene::resizeFbo(QGLFramebufferObjectSurface * & surface,const QSize & size)
{
	if(!surface)
		surface = createFboSurface(size);
	else
	{
		if(surface->framebufferObject()->size()!=size)
		{
			destroyFboSurface(surface);
			surface = createFboSurface(size);
		}
	}
}

void Mg3dScene::initializeGL(QGLPainter * )
{
	camera()->setUpVector(QVector3D(0,0,1));
	camera()->setCenter(QVector3D(5,5,5));
	camera()->setEye(QVector3D(10,10,10)*1.5);

	d_ptr->fboVertices.upload();
	d_ptr->fpsTime.start();
}


void Mg3dScene::drawGridAndReference(QGLPainter * painter)
{
	if(d_ptr->showReference)
		d_ptr->axisNode->draw(painter);

	if(d_ptr->showGrid)
	{
		painter->setColor(Qt::white);
		d_ptr->gridsNode->draw(painter);
	}
}


void Mg3dScene::drawFboSurface(QGLFramebufferObjectSurface * fbo ,QGLPainter * painter)
{
	d_ptr->fboDisplayShader.setActive(painter,true);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,fbo->framebufferObject()->texture());
	drawFboVertices(painter);
	fbo->framebufferObject()->release();
	d_ptr->fboDisplayShader.setActive(painter,false);
}

void Mg3dScene::drawFboSurface(QGLFramebufferObjectSurface * fbo,const QVector2D & center,const QVector2D & size,QGLPainter * painter)
{
	d_ptr->textureDisplayShader.setActive(painter,true);
	d_ptr->textureDisplayShader.setCenter(center);
	d_ptr->textureDisplayShader.setSize(size);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,fbo->framebufferObject()->texture());
	drawFboVertices(painter);
	fbo->framebufferObject()->release();
	d_ptr->textureDisplayShader.setActive(painter,false);
}

//==================================================


bool Mg3dScene::showReference()const
{
	return d_ptr->showReference;
}
void Mg3dScene::setShowReference(bool ok)
{
	if(ok != d_ptr->showReference)
	{
		d_ptr->showReference = ok;
		Q_EMIT referenceShown(ok);
		if(isVisible())
			updateGL();
	}
}

bool Mg3dScene::showGrid()const
{
	return d_ptr->showGrid;
}
void Mg3dScene::setShowGrid(bool ok)
{
	if(ok != d_ptr->showGrid)
	{
		d_ptr->showGrid = ok;
		Q_EMIT gridShown(ok);
		if(isVisible())
			updateGL();
	}
}


void Mg3dScene::setCameraPosition(const QVector3D & pos)
{
	if(pos != cameraPosition())
	{
		camera()->setEye(pos);
		updateGLContent();
		Q_EMIT cameraPositionChanged(pos);
	}
}
QVector3D Mg3dScene::cameraPosition()const
{
	return camera()->eye();
}
void Mg3dScene::setCameraCenter(const QVector3D & pos)
{
	if(pos != cameraCenter())
	{
		camera()->setCenter(pos);
		updateGLContent();
		Q_EMIT cameraCenterChanged(pos);
	}
}
QVector3D Mg3dScene::cameraCenter()const
{
	return camera()->center();
}


void Mg3dScene::setCameraUpVector(const QVector3D & v)
{
	if(v != cameraUpVector())
	{
		camera()->setUpVector(v);
		updateGLContent();
		Q_EMIT cameraUpVectorChanged(v);
	}
}
QVector3D Mg3dScene::cameraUpVector()const
{
	return camera()->upVector();
}

void Mg3dScene::updateGLContent()
{
	if(isVisible())
		updateGL();
}

void Mg3dScene::paintGL()
{
	d_ptr->fpsTime.restart();
	QGLView::paintGL();
}

void Mg3dScene::clearStateText()
{
	d_ptr->stateTextList.clear();
}
void  Mg3dScene::setStateText(int pos,const QString& text)
{
	d_ptr->stateTextList[pos]=text;
}
void Mg3dScene::setStateTextSize(int size)
{
	size = qMax(1,size);
	if(d_ptr->stateTextList.size()<size)
	{
		int sizeToAdd = size-d_ptr->stateTextList.size();
		for (int i = 0; i < sizeToAdd; ++i)
			d_ptr->stateTextList.append("");
	}
	else if(d_ptr->stateTextList.size()>size)
	{
		int sizeToRemove = d_ptr->stateTextList.size() - size;
		for (int i = 0; i < sizeToRemove; ++i)
			d_ptr->stateTextList.removeLast();
	}
}

void Mg3dScene::keyPressEvent(QKeyEvent* event)
{
	QGLView::keyPressEvent(event);
	if(event->key() == Qt::Key_G && event->modifiers().testFlag(Qt::ControlModifier))
		setShowGrid(!showGrid());

	if(event->key() == Qt::Key_R && event->modifiers().testFlag(Qt::ControlModifier))
		setShowReference(!showReference());
}

void Mg3dScene::updateFps()
{
	int elapsed =qMax(d_ptr->fpsTime.elapsed(),1);
	d_ptr->fpsManager.addNewTime(elapsed);
	setStateText(0,d_ptr->fpsManager.fpsString());
}
void Mg3dScene::drawStateText(QGLPainter *painter)
{
	drawText(painter,d_ptr->stateTextList);
}

void Mg3dScene::drawText(QGLPainter * painter, const QStringList& str)
{
	QString longest;
	const int minWidth = 100;
	for (int i = 0; i < str.size(); ++i)
	{
		if(str[i].length()>longest.length())
			longest = str[i];
	}

	QFont f = font();
	f.setPointSize(11);

	QFontMetrics metrics(f);

	QRect rect = metrics.boundingRect(longest);

	if(rect.width()<minWidth)
		rect.setWidth(minWidth);

	QImage image(
			QSize(rect.width()+10,rect.height()*str.size()+10),
			QImage::Format_ARGB32
			);
	image.fill(0);
	QPainter p2(&image);
	p2.setFont(f);
	p2.setPen(Qt::yellow);
	p2.setRenderHint(QPainter::TextAntialiasing);
	for(int y= 0;y<str.size();++y)
		p2.drawText(
				0 ,
				((y+1) * rect.height()),
				" "+str[y]
		);


	p2.end();

	QGLTexture2D texture;
	texture.setImage(image);
	texture.bind();
	glDisable(GL_DEPTH_TEST);


	d_ptr->textureDisplayShader.setActive(painter,true);

	QVector2D size((float)image.width()/width(),
			(float)image.height()/height());
	QVector2D center(
			remapVal(size.x()/2,0,1,-1,1),
			remapVal(1-size.y()/2,0,1,-1,1));

	d_ptr->textureDisplayShader.setCenter(center);
	d_ptr->textureDisplayShader.setSize(size);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture.textureId());
	drawFboVertices(painter);
	d_ptr->textureDisplayShader.setActive(painter,false);
	texture.release();

	glEnable(GL_DEPTH_TEST);
}


