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
#ifndef MGCURVE_H_
#define MGCURVE_H_

//MG_INCLUDE_INFO:MgCurve

#include <QtGui/QPen>
#include "mgcurvedata.h"

class MgCurve
{

public:

	MgCurve(QString id,MgCurveData * data):m_data(data),m_id(id)
	{
		setColor(Qt::green);
		setPenStyle(Qt::SolidLine);
		setLineWidth(1);
	}
	~MgCurve(){}

	void setColor(const QColor & c){m_pen.setColor(c);}
	QColor color()const{return m_pen.color();}

	int lineWidth()const{return m_pen.width();}
	void setLineWidth(int w){m_pen.setWidth(w);}

	Qt::PenStyle penSyle()const{return m_pen.style();}
	void setPenStyle(Qt::PenStyle st){m_pen.setStyle(st);}

	MgCurveData * data()const{return m_data;}
	void setData(MgCurveData * data){m_data = data;}

	QString id()const{return m_id;}
	QPen pen()const{return m_pen;}

private:
	QPen m_pen;
	MgCurveData * m_data;
	QString m_id;



};

#endif /* MGCURVE_H_ */
