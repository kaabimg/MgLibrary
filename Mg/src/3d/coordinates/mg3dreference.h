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
#ifndef MG3DREFERENCE_H_
#define MG3DREFERENCE_H_

#include <MgCore/MgGlobal>
#include <QtCore/QObject>


//MG_INCLUDE_INFO:Mg3DReference

MG_USE_PRIVATE_CLASS(Mg3DReference)
class QGLSceneNode;


class Mg3DReference
{
public:
	Mg3DReference();
	virtual ~Mg3DReference();

	qreal axisLength()const;
	void setAxisLenght(qreal);

	QGLSceneNode * createReferenceAxis();
	QGLSceneNode * createReferenceGrids();

	int gridWidth();
	void setGridWidth(int);


private:
	MG_PRIVATE_CLASS(Mg3DReference)
	Q_DISABLE_COPY(Mg3DReference)

	QGLSceneNode * createAxis(double);
	void createXAxis();
	void createYAxis();
	void createZAxis();

	QGLSceneNode * createCylinderLine(double size,double diameter);
};

#endif /* MG3DREFERENCE_H_ */
