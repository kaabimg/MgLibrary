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
#ifndef MGMATHSCRIPTBINDINGS_H_
#define MGMATHSCRIPTBINDINGS_H_

//MG_INCLUDE_INFO:MgMathScriptBindings

#include <QObject>
#include <QVector3D>
#include <math.h>
#include "mgscriptengine.h"

class MgMathScriptBindings : public QObject
{
	Q_OBJECT

	Q_CLASSINFO("MG_SLOTS",
			"cos,"
			"sin,"
			"rand,"
			"pi,"
			"length,"
			"createVector,"
			"crossProduct,"
			"dotProduct")
public:
	MgMathScriptBindings(MgScriptEngine * engine,QObject * parent =0):QObject(parent)
	{
		setObjectName("mgMath");
		engine->registerObject(this);
	}
public Q_SLOTS:
	double cos(double a)const{return ::cos(a);}
	double sin(double a)const{return ::sin(a);}
	double rand(double min,double max)const
	{
		return min + (qrand()%1000/1000.)/(max-min);
	}
	double pi()const{return M_PI;}
	double length(const QVector3D & v)const{return v.length();}
	QVector3D createVector(double x,double y, double z)const{return QVector3D(x,y,z);}
	QVector3D crossProduct(const QVector3D & v1,const QVector3D & v2)const
	{
		return QVector3D::crossProduct(v1,v2);
	}
	double dotProduct(const QVector3D & v1,const QVector3D & v2)const
	{
		return QVector3D::dotProduct(v1,v2);
	}
};

#endif /* MGMATHSCRIPTBINDINGS_H_ */
