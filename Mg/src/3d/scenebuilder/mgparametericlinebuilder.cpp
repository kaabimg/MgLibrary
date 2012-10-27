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
#include "mgparametericlinebuilder.h"
#include "../utils/mgparametriccurves.h"
#include "../utils/mg3dhelpers.h"

#include <Qt3D/qglbuilder.h>
#include <Qt3D/qtriangle3d.h>


#include <Qt3D/qvector3darray.h>
#include <QQuaternion>



#include <math.h>

MgParametericLineBuilder::MgParametericLineBuilder(QObject * parent)
	:MgAbstractNodeBuilder(parent),
	 m_shape(Cylinder),
	 m_radius(.1),
	 m_extremityRadius(-1),
	 m_step(-1),
	 m_additiveRandomRadius(0)
{}

MgParametericLineBuilder::~MgParametericLineBuilder()
{}

float MgParametericLineBuilder::rand0_1()const
{
	return (qrand()%1000) / 1000.;
}


QGLSceneNode * MgParametericLineBuilder::buildNode()
{
	QGLSceneNode  * node = NULL;
	if(m_shape == Cylinder)
	{
		QGLBuilder builder ;
		buildGeomety(builder);
		node = builder.finalizedSceneNode();
	}
	else
	{
		QGeometryData data;
		double dt(m_lagrangeCurve.period()/30);
		int index(0);
		for (double t = 0;  t< m_lagrangeCurve.period(); t+= dt)
		{
			data.appendVertex(m_lagrangeCurve.position(t));
			data.appendIndex(index);index++;
		}
		data.appendVertex(m_lagrangeCurve.position(m_lagrangeCurve.period()));
		data.appendIndex(index);



		node =  new QGLSceneNode(data);
		node->setStart(0);
		node->setCount(data.count());
		node->setDrawingMode(QGL::LineStrip);
		node->setDrawingWidth(2);
	}

	return node;

}

int nextIndex(int i,int total)
{
	return (i+1)%total;
}
int previousIndex(int i,int total)
{
	return (i-1)%total;
}


int mgVertexIndex(int layer, int layerSize, int index)
{
	return layer * layerSize + index;
}

#define vertexIndex(layer,index) mgVertexIndex(layer,slices,index)



void MgParametericLineBuilder::buildGeomety(QGLBuilder & builder)
{
	static int slices = 12;

	if(m_step == -1)
		m_step = m_lagrangeCurve.period()/30;


	double textureIndexInterval = qMax( m_step * 5.,m_lagrangeCurve.period()/5);

	QGeometryData verticesBottom;
	QGeometryData data;


	QVector3D direction = m_lagrangeCurve.derivative(0);
	QVector3DArray cercle(createCercle(
			direction,
			slices,
			radius(0),
			m_lagrangeCurve.position(0)
		));

	for (int i = 0; i < slices; ++i)
	{
		verticesBottom.appendVertex(cercle[i]);
		verticesBottom.appendTexCoord(QVector2D(0,(1.*i)/slices));
//		verticesBottom.appendAttribute(direction);
	}
	verticesBottom.appendVertex(cercle.first());


	double t = m_step;
	double texCoordX;
	while(true)
	{
		QGeometryData verticesTop;

		t = qMin(t,m_lagrangeCurve.period());


		QVector3D direction = m_lagrangeCurve.derivative(t);
		QVector3DArray cercle(createCercle(
				direction,
				slices,
				radius(t),
				m_lagrangeCurve.position(t)
			));

		for (int i = 0; i < slices; ++i)
		{
			verticesTop.appendVertex(cercle[i]);

			texCoordX = t;
			while(texCoordX>textureIndexInterval)
				texCoordX -=textureIndexInterval;
			verticesTop.appendTexCoord(QVector2D(texCoordX/textureIndexInterval,(1.*i)/slices));
//			verticesTop.appendAttribute(direction);
		}
		verticesTop.appendVertex(cercle.first());


		builder.addQuadsInterleaved(verticesTop,verticesBottom);


		verticesBottom=verticesTop;


		if(t == m_lagrangeCurve.period())
			break;

		t += m_step;
	}
}


double MgParametericLineBuilder::radius(const QVector3D & position)
{
	qreal alpha = -m_extremityRadius;
	qreal distance_to_source = (m_lagrangeCurve.interpolationPoints().first()-position).length();
	qreal distance_to_destination = (m_lagrangeCurve.interpolationPoints().last()-position).length();

	return m_radius +
			(m_extremityRadius - m_radius)  * .75 *
			(exp(distance_to_source/alpha)+exp(distance_to_destination/alpha));
}


double MgParametericLineBuilder::radius(double t)
{
	if(m_extremityRadius==-1)
		return m_radius + m_additiveRandomRadius * rand0_1();
	qreal alpha = m_lagrangeCurve.period()/30;

	return m_radius + m_additiveRandomRadius * rand0_1() +
			(m_extremityRadius - m_radius)  *
			(exp(-t/alpha) + exp((t- m_lagrangeCurve.period())/alpha));

}


QQuaternion MgParametericLineBuilder::rotationFromZ(const QVector3D & vect)const
{
	static const QVector3D z(0.,0.,1.);
	QVector3D cross_product = QVector3D::crossProduct(z,vect);

	QQuaternion rotation = QQuaternion::fromAxisAndAngle(cross_product,
			acos(QVector3D::dotProduct(z,vect.normalized()))*180/M_PI);
	return rotation;
}

QVector3DArray MgParametericLineBuilder::createCercle(const QVector3D & orientation, int slices, qreal radus,const QVector3D & translate)
{
	QVector3DArray points;

	qreal x(.0),y(.0);
	qreal d_angle = 2.0 * M_PI/slices;
	qreal angle=0;
	QQuaternion rotation = rotationFromZ(orientation);

	for(int i =0;i<slices;++i)
	{
		x = cos(angle) * radus;
		y = sin(angle) * radus;

		points<<rotation.rotatedVector(QVector3D(x,y,.0))+translate;
		angle+=d_angle;
	}
	return points;
}
QGeometryData MgParametericLineBuilder::generateTube(
		const QVector3D & from ,
		const QVector3D & to,
		double radius ,
		int slices)const
{
	QGeometryData data;

	double length = (to -from).length();
	qreal x(.0),y(.0);
	qreal d_angle = 2.0 * M_PI/slices;
	qreal angle=0;
	QQuaternion rotation = rotationFromZ(to-from);
	QVector3D p0,p1,p2,p3;
	for(float i =0;i<slices;++i)
	{
		x = cos(angle) * radius;
		y = sin(angle) * radius;

		p0 = rotation.rotatedVector(QVector3D(x,y,.0));
		p2 = rotation.rotatedVector(QVector3D(x,y,length));

		x = cos(angle+d_angle) * radius;
		y = sin(angle+d_angle) * radius;

		p1 = rotation.rotatedVector(QVector3D(x,y,.0));
		p3 = rotation.rotatedVector(QVector3D(x,y,length));

		data.appendVertex(p0,p1,p2);
		data.appendTexCoord(QVector2D(i/slices,0),QVector2D(i/slices,1),QVector2D(i+1/slices,0));

		data.appendVertex(p1,p3,p2);
		data.appendTexCoord(QVector2D(i/slices,1),QVector2D(i+1/slices,1),QVector2D(i+1/slices,0));

		angle+=d_angle;
	}


	return data.translated(from);
}
