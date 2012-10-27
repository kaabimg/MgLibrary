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
#include "mgtextureshader.h"
#include <QDebug>

static char const MgTextureShader_vertexShader [] =
"attribute highp vec4 qt_Vertex;\n"
"attribute highp vec4 qt_MultiTexCoord0;\n"
"uniform mediump mat4 qt_ModelViewProjectionMatrix;\n"
"varying highp vec2 qt_TexCoord0;\n"
"\n"
"void main(void)\n"
"{\n"
"    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;\n"
"    qt_TexCoord0 = qt_MultiTexCoord0.st;\n"
"}";

static char const MgTextureShader_fragmentShader [] =
"varying highp vec2 qt_TexCoord0;\n"
"uniform sampler2D qt_Texture0;\n"
"uniform mediump float alpha;\n"
"void main(void)\n"
"{\n"
"	gl_FragColor = texture2D(qt_Texture0,qt_TexCoord0.st);\n"
"	gl_FragColor.a = alpha;\n"
//"	gl_FragColor = vec4(.1,.1,.8,1);\n"
"}\n";


MgTextureShader::MgTextureShader():m_alphaLocation(-1)
{
	setShaderSourceCode(QGLShader::Vertex,MgTextureShader_vertexShader);
	setShaderSourceCode(QGLShader::Fragment,MgTextureShader_fragmentShader);
}

MgTextureShader::~MgTextureShader(){}


void MgTextureShader::postInit()
{
	if(program())
	{
		m_alphaLocation = program()->uniformLocation("alpha");
	}
	else
		qDebug()<<"Can't get alpha location : null shader program";
}


void MgTextureShader:: setAlpha(GLfloat alpha)
{
	if(m_alphaLocation>-1)
		program()->setUniformValue(m_alphaLocation,alpha);
	else
		qDebug()<<"Can't set alpha value, undefined alpha location";
}

