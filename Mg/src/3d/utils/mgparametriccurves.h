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
#ifndef MGPARAMETRICCURVES_H_
#define MGPARAMETRICCURVES_H_

//MG_INCLUDE_INFO:MgLagrangeCurve


#include <QVector3D>
#include <QList>

typedef QList<QVector3D> InterpolationPoints;

class MgLagrangeCurve
{
public:
	MgLagrangeCurve(){}
	virtual ~MgLagrangeCurve(){}

	void init(double period,const QVector3D & from,const QVector3D & to);

	void setData(const QList<double> & times,const InterpolationPoints & points)
	{
		m_times = times;
		m_interpolationPoints = points;

	}
	InterpolationPoints interpolationPoints()const{return m_interpolationPoints;}

	double period()const
	{
		if(m_times.size())
			return m_times.last();
		return 0;
	}

	QVector3D position(double t)const;
	QVector3D derivative(double t)const;

	static void generateIntermediatePoints(
			const QVector3D & begin,const QVector3D & end,int intermediatePointsSize,
			QList<double> & times,InterpolationPoints & points,double time);

private:
	QList<double> m_times;
	InterpolationPoints m_interpolationPoints;

};

#endif /* MGPARAMETRICCURVES_H_ */
