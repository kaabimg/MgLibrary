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
#ifndef MGCURVEDATA_H_
#define MGCURVEDATA_H_

//MG_INCLUDE_INFO:MgCurveData

#include <QtCore/QPointF>
#include <QtCore/QList>


class MgCurveData
{
public:
	MgCurveData():m_min(0),m_max(0){}
	~MgCurveData(){}

	void clear()
	{
		m_points.clear();
		m_min = 0;
		m_max = 0;
	}
	int size()const{return m_points.size();}
	bool isEmpty()const{return m_points.isEmpty();}
	qreal maxY()const{return m_max;}
	qreal minY()const{return m_min;}
	qreal minX()const{return m_points.size() ? m_points.first().x() : 0;}
	qreal maxX()const{return m_points.size() ? m_points.last().x() : 0;}


	void addPoint(qreal x,qreal y)
	{
		addPoint(QPointF(x,y));
	}
	void addPoint(const QPointF & p)
	{
		m_min = m_min < p.y() ? m_min :  p.y();
		m_max = m_max > p.y() ? m_max :  p.y();
		m_points<<p;
	}
	const QPointF & operator[](int i)const{return m_points[i];}
	const QPointF & at(int i)const{return m_points[i];}

	int firstIndexBefore(qreal x)const
	{
		if(m_points.isEmpty())
			return -1;
		if(x<m_points.first().x() )
			return 0;
		if(x>m_points.last().x())
			return m_points.size()-1;

		return firstIndexBefore(x,0,m_points.size()-1);
	}

	int firstIndexAfter(qreal x)const
	{
		if(!m_points.size())
			return -1;
		if(x<m_points.first().x() )
			return 0;
		if(x>m_points.last().x())
			return m_points.size()-1;

		return firstIndexAfter(x,0,m_points.size()-1);
	}

private:

	int firstIndexBefore(qreal x,int begin,int end)const
	{
		if(x == m_points[begin].x())
			return begin;
		if(x == m_points[end].x())
			return end;
		if((end - begin) == 1)
			return begin;

		int middle = (begin + end) /2;


		if(x < m_points[middle].x())
			return firstIndexBefore(x,begin,middle);

		return firstIndexBefore(x,middle,end);
	}

	int firstIndexAfter(qreal x,int begin,int end)const
	{
		if(x == m_points[begin].x())
			return begin;
		if(x == m_points[end].x())
			return end;
		if((end - begin) == 1)
			return end;

		int middle = (begin + end) /2;


		if(x < m_points[middle].x())
			return firstIndexAfter(x,begin,middle);

		return firstIndexAfter(x,middle,end);
	}

private:
	qreal m_min,m_max;
	QList<QPointF> m_points;

};

#endif /* MGCURVEDATA_H_ */
