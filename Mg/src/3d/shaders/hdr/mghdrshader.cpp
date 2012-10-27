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
#include "mghdrshader.h"



static char const MgHdrShader_vertexShader [] =
"attribute highp vec4 qt_Vertex;\n"
"attribute highp vec4 qt_MultiTexCoord0;\n"
"varying highp vec2 qt_TexCoord0;\n"
"void main(void)\n"
"{\n"
"    gl_Position = qt_Vertex;\n"
"    qt_TexCoord0 = (qt_Vertex.xy + vec2(1,1))/2;\n"
"}\n";

static char const MgHdrShader_fragmentShader [] =
"uniform sampler2D qt_Texture0;\n"
"varying highp vec2 qt_TexCoord0;\n"
"uniform float exposure = 15;\n"
"\n"
"void main()\n"
"{\n"
"	vec4 color = texture2D(qt_Texture0, qt_TexCoord0);\n"
"	gl_FragColor = 1.0 - exp2 (-color * exposure);\n"
"	gl_FragColor.a = 1.0;\n"
"}";


MgHdrShader::MgHdrShader()
{
	setShaderSourceCode(QGLShader::Vertex,MgHdrShader_vertexShader);
	setShaderSourceCode(QGLShader::Fragment,MgHdrShader_fragmentShader);
}

MgHdrShader::~MgHdrShader(){}

void MgHdrShader::setExposure(float exposure)
{
	if(program())
		program()->setUniformValue("exposure",exposure);
}
