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
#include "mgbumpmappingshader.h"

MgBumpMappingShader::MgBumpMappingShader()
{
	setShaderSourceCodeFromFile(QGLShader::Vertex,":/bumpmapping/bumpmapping.vsh");
	setShaderSourceCodeFromFile(QGLShader::Fragment,":/bumpmapping/bumpmapping.fsh");
}


void MgBumpMappingShader::setCameraPosition(const QVector3D & pos)
{
	if(program())
		program()->setUniformValue("cameraPosition",pos);
}
void MgBumpMappingShader::setAmbiantColor(const QColor & color)
{
	if(program())
		program()->setUniformValue("ambiantColor",
				QVector4D(
						color.redF(),
						color.greenF(),
						color.blue(),
						color.alphaF()
						));
}
void MgBumpMappingShader::setDiffuseColor(const QColor & color)
{
	if(program())
		program()->setUniformValue("diffuseColor",
				QVector4D(
						color.redF(),
						color.greenF(),
						color.blue(),
						color.alphaF()
						));
}
void MgBumpMappingShader::setAlpha(float a)
{
	if(program())
		program()->setUniformValue("alpha",a);
}
