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
#include "mggeometriesdata.h"

QGeometryData MgGeometriesData::sphere(qreal radius,int divisions)
{
	QGeometryData geometry;

	// Determine the number of slices and stacks to generate.
	static int const slicesAndStacks[] = {
			4, 4,
			8, 4,
			8, 8,
			16, 8,
			16, 16,
			32, 16,
			32, 32,
			64, 32,
			64, 64,
			128, 64,
			128, 128
	};
	if (divisions < 1)
		divisions = 1;
	else if (divisions > 10)
		divisions = 10;
	int stacks = slicesAndStacks[divisions * 2 - 1];
	int slices = slicesAndStacks[divisions * 2 - 2];

	// Precompute sin/cos values for the slices and stacks.
	const int maxSlices = 128 + 1;
	const int maxStacks = 128 + 1;
	qreal sliceSin[maxSlices];
	qreal sliceCos[maxSlices];
	qreal stackSin[maxStacks];
	qreal stackCos[maxStacks];
	for (int slice = 0; slice < slices; ++slice)
	{
		qreal angle = 2 * M_PI * slice / slices;
		sliceSin[slice] = qFastSin(angle);
		sliceCos[slice] = qFastCos(angle);
	}
	sliceSin[slices] = sliceSin[0]; // Join first and last slice.
	sliceCos[slices] = sliceCos[0];

	for (int stack = 0; stack <= stacks; ++stack)
	{
		qreal angle = M_PI * stack / stacks;
		stackSin[stack] = qFastSin(angle);
		stackCos[stack] = qFastCos(angle);
	}
	stackSin[0] = 0.0f;             // Come to a point at the poles.
	stackSin[stacks] = 0.0f;

	// Create the stacks.
	for (int stack = 0; stack < stacks; ++stack)
	{
		QGeometryData prim;
		qreal z = radius * stackCos[stack];
		qreal nextz = radius * stackCos[stack + 1];
		qreal s = stackSin[stack];
		qreal nexts = stackSin[stack + 1];
		qreal c = stackCos[stack];
		qreal nextc = stackCos[stack + 1];
		qreal r = radius * s;
		qreal nextr = radius * nexts;
		for (int slice = 0; slice <= slices; ++slice)
		{
			prim.appendVertex
			(QVector3D(nextr * sliceSin[slice],
					nextr * sliceCos[slice], nextz));
			prim.appendNormal
			(QVector3D(sliceSin[slice] * nexts,
					sliceCos[slice] * nexts, nextc));

			prim.appendVertex
			(QVector3D(r * sliceSin[slice],
					r * sliceCos[slice], z));
			prim.appendNormal
			(QVector3D(sliceSin[slice] * s,
					sliceCos[slice] * s, c));
		}
		geometry.appendGeometry(prim);
	}
	return geometry;
}



QQuaternion rotationFromZ(const QVector3D & vect)
{
	static const QVector3D z(0.,0.,1.);
	QVector3D cross_product = QVector3D::crossProduct(z,vect);

	QQuaternion rotation = QQuaternion::fromAxisAndAngle(cross_product,
			acos(QVector3D::dotProduct(z,vect)/vect.length())*180/M_PI);
	return rotation;
}


QGeometryData MgGeometriesData::cylinder(const QGLCylinder & cylinder,const QVector3D & orientation)
{
	QGeometryData my_geometry;

	qreal x(.0),y(.0);
	int n = cylinder.slices();
	qreal d_angle = 2.0 * M_PI/n;
	qreal angle=0;
	qreal z=cylinder.height();


	qreal scale_bottom,scale_top;
	QVector3D current_point;
	QQuaternion rotation = rotationFromZ(orientation);

	for(int i =0;i<n+1;++i)
	{
		x = cos(angle);
		y = sin(angle);
		if(z!=cylinder.height())
		{
			scale_bottom = cylinder.diameterTop();
			scale_top = cylinder.diameterBottom();
		}
		else
		{
			scale_bottom = cylinder.diameterBottom();
			scale_top = cylinder.diameterTop();
		}


		//bottom point;
		x = cos(angle) * scale_bottom;
		y = sin(angle) * scale_bottom;

		current_point = QVector3D(x,y,z);
		my_geometry.appendVertex(rotation.rotatedVector(current_point));
		my_geometry.appendNormal(rotation.rotatedVector(current_point));

		//top point
		x = scale_top * cos(angle);
		y = scale_top * sin(angle);
		z = qAbs(z-cylinder.height());

		current_point = QVector3D(x,y,z);
		my_geometry.appendVertex(rotation.rotatedVector(current_point));
		my_geometry.appendNormal(rotation.rotatedVector(current_point));

		// next point
		x = scale_top * cos((angle+d_angle));
		y = scale_top * sin(angle+d_angle);
		z = qAbs(z-cylinder.height());

		current_point = QVector3D(x,y,z);
		my_geometry.appendVertex(rotation.rotatedVector(current_point));
		my_geometry.appendNormal(rotation.rotatedVector(current_point));


		z = qAbs(z-cylinder.height());
		angle+=d_angle;
	}
    return my_geometry;
}




QVector3DArray MgGeometriesData::cercle(const QVector3D & orientation, int slices, qreal radus)
{
	QVector3DArray points;

	qreal x(.0),y(.0);
	qreal d_angle = 2.0 * M_PI/slices;
	qreal angle=0;
	QQuaternion rotation = rotationFromZ(orientation);

	for(int i =0;i<slices+1;++i)
	{
		x = cos(angle) * radus;
		y = sin(angle) * radus;

		points<<rotation.rotatedVector(QVector3D(x,y,.0));
		angle+=d_angle;
	}

	return points;
}


void MgGeometriesData::rotateGeometry(QGeometryData & data,const QQuaternion & rotation)
{
	for (int i = 0; i < data.count(); ++i)
		data.vertex(i) = rotation.rotatedVector(data.vertexAt(i));
}

