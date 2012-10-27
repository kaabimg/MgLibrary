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
#include "mgparametriccurves.h"

QVector3D MgLagrangeCurve::position(double t)const
{
	double x =.0, y =.0 ,z =.0;
	double product;
	for (int j = 0; j < m_interpolationPoints.size(); ++j)
	{
		product = 1.;
		for (int i = 0; i < j; ++i)
		{
			product *= (t- m_times[i])/(m_times[j] - m_times[i]);
		}
		for (int i = j+1; i <  m_interpolationPoints.size(); ++i)
		{
			product *= (t- m_times[i])/(m_times[j] - m_times[i]);
		}
		x += m_interpolationPoints[j].x() * product ;
		y += m_interpolationPoints[j].y() * product ;
		z += m_interpolationPoints[j].z() * product ;

	}
	return QVector3D(x,y,z);
}

QVector3D MgLagrangeCurve::derivative(double t)const
{
	static const double dt = 0.0001;
	return (position(t+dt)-position(t))/dt;
}

void  MgLagrangeCurve::init(double period,const QVector3D & from,const QVector3D & to)
{
	generateIntermediatePoints(from,to,2,m_times,m_interpolationPoints,period);
}



void MgLagrangeCurve::generateIntermediatePoints(
		const QVector3D & begin,const QVector3D & end,	int intermediatePointsSize,
		QList<double> & times,InterpolationPoints & points,double time)
{

	int totalPoints = 2 + intermediatePointsSize;
	points.append(begin);
	times.append(.0);


	double t,x,y,z;

	double dt = time/(totalPoints-1);
	double dx = (end.x() - begin.x())/(totalPoints -1);
	double dy = (end.y() - begin.y())/(totalPoints -1);
	double dz = (end.z() - begin.z())/(totalPoints -1);

	double begin_t = dt;
	double begin_x = begin.x() + dx ;
	double begin_y = begin.y() + dy ;
	double begin_z = begin.z() + dz ;


	for (int i = 0; i < totalPoints -2;  ++i)
	{
		t = begin_t ;
		x = begin_x + dx * (500-qrand()%1000)/1000.;
		y = begin_y + dy * (500-qrand()%1000)/1000.;
		z = begin_z + dz * (500-qrand()%1000)/1000.;

		times.append(t);
		points.append(QVector3D(x,y,z));
		begin_t += dt;
		begin_x += dx;
		begin_y += dy;
		begin_z += dz;
	}


	points.append(end);
	times.append(time);//TODO last
}
