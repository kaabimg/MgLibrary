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
#ifndef GEOMETRIESDATA_H_
#define GEOMETRIESDATA_H_

#include <Qt3D/qgeometrydata.h>
#include <qmath.h>
#include <Qt3D/qglcylinder.h>

struct MgGeometriesData
{
	static QGeometryData sphere(qreal radius,int divisions = 3);
	static QGeometryData cylinder(const QGLCylinder & cylinder,const QVector3D & orientation);
	static QVector3DArray cercle(const QVector3D & orientation, int slices, qreal radus);

	static void rotateGeometry(QGeometryData & data,const QQuaternion & rotation);


} ; // namespace GeometriesData


#endif /* GEOMETRIESDATA_H_ */
