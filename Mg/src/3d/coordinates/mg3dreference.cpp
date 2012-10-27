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
#include "mg3dreference.h"

#include <Qt3D/qglscenenode.h>
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qgeometrydata.h>
#include <Qt3D/qglcylinder.h>
#include <Qt3D/qglmaterial.h>
#include <Qt3D/qgraphicsrotation3d.h>


struct Mg3DReferencePrivate
{

	QGLSceneNode * referenceNode;
	QGLSceneNode * zAxisNode,* yAxisNode,* xAxisNode;
	QGLSceneNode * gridsNode;
	QGLSceneNode * xyGridNode,* xzGridNode,* yzGridNode;
	int gridWidth;
	qreal gridLineWidth,axisWidth,axisLength;

};

Mg3DReference::Mg3DReference():d_ptr(new Mg3DReferencePrivate )
{
	d_ptr->referenceNode = NULL;
	d_ptr->gridWidth = 5;
	setAxisLenght(1000);
}




Mg3DReference::~Mg3DReference()
{
	delete d_ptr;
}

qreal Mg3DReference::axisLength()const
{
	return d_ptr->axisLength;
}
void Mg3DReference::setAxisLenght(qreal l)
{
	d_ptr->axisLength = l;
	d_ptr->gridLineWidth = d_ptr->axisLength/500;
	d_ptr->axisWidth = d_ptr->axisLength/100;
}


QGLSceneNode * Mg3DReference::createReferenceAxis()
{
	d_ptr->referenceNode = new QGLSceneNode;
	d_ptr->referenceNode->setObjectName("Coordinates reference");
	createXAxis();
	createYAxis();
	createZAxis();

	return d_ptr->referenceNode;
}

QGLSceneNode * Mg3DReference::createReferenceGrids()
{
	QGeometryData geomtery;
	int indices(0);
	for (float x = -d_ptr->axisLength; x <= d_ptr->axisLength; x += d_ptr->axisLength / d_ptr->gridWidth)
	{
		geomtery.appendVertex(QVector3D(x,-d_ptr->axisLength,0));
		geomtery.appendIndex(indices);indices++;
		geomtery.appendVertex(QVector3D(x,d_ptr->axisLength,0));
		geomtery.appendIndex(indices);indices++;
	}

	for (float y = -d_ptr->axisLength; y <= d_ptr->axisLength; y += d_ptr->axisLength / d_ptr->gridWidth)
	{
		geomtery.appendVertex(QVector3D(-d_ptr->axisLength,y,0));
		geomtery.appendIndex(indices);indices++;
		geomtery.appendVertex(QVector3D(d_ptr->axisLength,y,0));
		geomtery.appendIndex(indices);indices++;
	}

	d_ptr->gridsNode = new QGLSceneNode(geomtery);
	d_ptr->gridsNode->setStart(0);
	d_ptr->gridsNode->setCount(geomtery.count());
	d_ptr->gridsNode->setDrawingMode(QGL::Lines);
	d_ptr->gridsNode->setDrawingWidth(1);


	d_ptr->gridsNode->setObjectName("Grids node");

	d_ptr->gridsNode->setEffect(QGL::FlatColor);

	return d_ptr->gridsNode;
}
int Mg3DReference::gridWidth()
{
	return d_ptr->gridWidth;
}
void Mg3DReference::setGridWidth(int w)
{
	d_ptr->gridWidth = w;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

QGLSceneNode * Mg3DReference::createCylinderLine(double size,double diameter)
{
	QGLBuilder builder;
	builder<<QGLCylinder(diameter,diameter,size);
	return builder.finalizedSceneNode();
}


QGLSceneNode * Mg3DReference::createAxis(double size)
{
	QGLBuilder builder1,builder2;
	builder1<<QGLCylinder(d_ptr->axisWidth,d_ptr->axisWidth,size);
	builder2<<QGLCylinder(0,d_ptr->axisWidth* 6,3);

	QGLSceneNode * base  = builder1.finalizedSceneNode();
	QGLSceneNode * arrow = builder2.finalizedSceneNode();

	arrow->setPosition(QVector3D(0,0,size));

	QGLSceneNode *axisNode = new QGLSceneNode;
	axisNode->addNode(base);
	axisNode->addNode(arrow);
	return axisNode;
}

void Mg3DReference::createXAxis()
{
	d_ptr->xAxisNode = new QGLSceneNode(d_ptr->referenceNode);
	d_ptr->xAxisNode->setObjectName("X axis");
	d_ptr->xAxisNode->addNode(createAxis(d_ptr->axisLength ));
	QGraphicsRotation3D * rotation = new QGraphicsRotation3D(d_ptr->xAxisNode);
	rotation->setAxis(QVector3D(0,1,0));
	rotation->setAngle(90);
	d_ptr->xAxisNode->addTransform(rotation);

	QGLMaterial * material = new QGLMaterial(d_ptr->xAxisNode);
	material->setColor(QColor(255,0,0,250));
	d_ptr->xAxisNode->setMaterial(material);
	d_ptr->xAxisNode->setEffect(QGL::LitMaterial);
	d_ptr->referenceNode->addNode(d_ptr->xAxisNode);
}
void Mg3DReference::createYAxis()
{
	d_ptr->yAxisNode = new QGLSceneNode(d_ptr->referenceNode);
	d_ptr->yAxisNode->setObjectName("Y axis");
	d_ptr->yAxisNode->addNode(createAxis(d_ptr->axisLength));

	QGraphicsRotation3D * rotation = new QGraphicsRotation3D(d_ptr->yAxisNode);
	rotation->setAxis(QVector3D(1,0,0));
	rotation->setAngle(-90);
	d_ptr->yAxisNode->addTransform(rotation);

	QGLMaterial * material = new QGLMaterial(d_ptr->yAxisNode);
	material->setColor(QColor(0,255,0,250));
	d_ptr->yAxisNode->setMaterial(material);
	d_ptr->yAxisNode->setEffect(QGL::LitMaterial);
	d_ptr->referenceNode->addNode(d_ptr->yAxisNode);
}
void Mg3DReference::createZAxis()
{
	d_ptr->zAxisNode = new QGLSceneNode(d_ptr->referenceNode);
	d_ptr->zAxisNode->setObjectName("Z axis");
	d_ptr->zAxisNode->addNode(createAxis(d_ptr->axisLength));

	QGLMaterial * material = new QGLMaterial(d_ptr->zAxisNode);
	material->setColor(QColor(0,0,255,250));
	d_ptr->zAxisNode->setMaterial(material);

	d_ptr->zAxisNode->setEffect(QGL::LitMaterial);
	d_ptr->referenceNode->addNode(d_ptr->zAxisNode);

}
