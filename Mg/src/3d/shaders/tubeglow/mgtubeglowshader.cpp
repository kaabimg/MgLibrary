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
#include "mgtubeglowshader.h"

static char const MgTubeGlowShader_vertexShader [] =
"attribute highp vec4 qt_Vertex;\n"
"attribute highp vec4 qt_Normal;\n"
"uniform highp vec3 cameraPosition;\n"
"uniform mediump mat4 qt_ModelViewProjectionMatrix;\n"
"varying float intensity;\n"
"void main(void)\n"
"{\n"
"	gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;\n"
"	intensity =  dot (normalize(cameraPosition - qt_Vertex),normalize(qt_Normal));\n"
"}\n";

static char const MgTubeGlowShader_fragmentShader [] =
"varying float intensity;\n"
"void main()\n"
"{\n"
"	float alpha = clamp (intensity,1,1);\n"
"	gl_FragColor = vec4(.1,.9,.9,alpha);			\n"
"	gl_FragColor = 1.0 - exp2 (-gl_FragColor * 10);\n"
"	gl_FragColor.a = alpha;\n"
"}\n";

MgTubeGlowShader::MgTubeGlowShader()
{
	setShaderSourceCode(QGLShader::Vertex,MgTubeGlowShader_vertexShader);
	setShaderSourceCode(QGLShader::Fragment,MgTubeGlowShader_fragmentShader);
}

MgTubeGlowShader::~MgTubeGlowShader(){}

void MgTubeGlowShader::setCameraPosition(const QVector3D & position)
{
	if(program())
		program()->setUniformValue("cameraPosition",position);
}
