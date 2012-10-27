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
#ifndef MGPARAMETERICLINEBUILDER_H_
#define MGPARAMETERICLINEBUILDER_H_

//MG_INCLUDE_INFO:MgParametericLineBuilder

#include "../utils/mgparametriccurves.h"

#include "mgabstractnodebuilder.h"

#include <Qt3D/qvector3darray.h>
#include <Qt3D/qgeometrydata.h>

Q_DECLARE_METATYPE(InterpolationPoints)


class QGLBuilder;

class MgParametericLineBuilder : public MgAbstractNodeBuilder
{
	Q_OBJECT
	Q_PROPERTY(float radius READ radius WRITE setRadius)
	Q_PROPERTY(float step READ step WRITE setStep)

public:
	enum CurveShape{Line,Cylinder};
	MgParametericLineBuilder(QObject * parent=0);
	virtual ~MgParametericLineBuilder();
	QGLSceneNode * buildNode();

public Q_SLOTS:


	void setLagrangeCurve(const MgLagrangeCurve & curve){m_lagrangeCurve = curve;}
	MgLagrangeCurve lagrangeCurve()const{return m_lagrangeCurve;}

	float radius()const {return m_radius;}
	void setRadius(float r){m_radius = r;}

	float additiveRandomRadius()const{return m_additiveRandomRadius;}
	void setAdditiveRandomRadius(float r){m_additiveRandomRadius =r;}

	float extremityRadius()const {return m_extremityRadius;}
	void setExtremityRadius(float r){m_extremityRadius = r;}

	float step()const{return m_step;}
	void setStep(float s){m_step = s;}

	void setCurveShape(CurveShape type){m_shape = type;}
	CurveShape curveShape()const{return m_shape;}

protected:
	void  buildGeomety(QGLBuilder & builder);
	double radius(const QVector3D & position);
	double radius(double t);
	QQuaternion rotationFromZ(const QVector3D & vect)const;
	QVector3DArray createCercle(const QVector3D & orientation, int slices, qreal radus,const QVector3D & translate = QVector3D());
	QGeometryData generateTube(const QVector3D & from , const QVector3D & to, double radius ,int slices)const;
	float rand0_1()const;
private:
	CurveShape m_shape;
	float m_radius,m_extremityRadius,m_step,m_length,m_additiveRandomRadius;
	MgLagrangeCurve m_lagrangeCurve;
};

#endif /* MGPARAMETERICLINEBUILDER_H_ */
