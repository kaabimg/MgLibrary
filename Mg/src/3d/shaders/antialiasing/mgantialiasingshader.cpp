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
#include "mgantialiasingshader.h"

MgAntialiasingShader::MgAntialiasingShader()
{
	setShaderSourceCodeFromFile(QGLShader::Vertex,":/fbodisplay/fbodisplay.vsh");
	setShaderSourceCodeFromFile(QGLShader::Fragment,":/antialiasing/antialiasing.fsh");
}


void MgAntialiasingShader::setWidth(int w)
{
	if(program())
		program()->setUniformValue("width",w);
}
void MgAntialiasingShader::setHeight(int h)
{
	if(program())
		program()->setUniformValue("height",h);
}
