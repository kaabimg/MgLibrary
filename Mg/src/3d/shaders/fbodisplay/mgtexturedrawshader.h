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
#ifndef MGTEXTUREDRAWSHADER_H_
#define MGTEXTUREDRAWSHADER_H_

//MG_INCLUDE_INFO:MgTextureDrawShader

#include "../mgabstractshader.h"

class MgTextureDrawShader : public MgAbstractShader
{
public:
	MgTextureDrawShader();

	//in [-1,1]
	void setCenter(const QVector2D &);

	//in [0,1]
	void setSize(const QVector2D &);

};

#endif /* MGTEXTUREDRAWSHADER_H_ */
