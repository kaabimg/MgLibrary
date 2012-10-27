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
#include "mgabstractshader.h"

#include <Qt3D/qglshaderprogrameffect.h>

MgAbstractShader::MgAbstractShader()
{
	m_effect = new QGLShaderProgramEffect;
}

MgAbstractShader::~MgAbstractShader()
{
	delete m_effect;
}


void MgAbstractShader::setShaderSourceCode(QGLShader::ShaderType type,const QString & code)
{
	if(type == QGLShader::Vertex)
		m_effect->setVertexShader(code.toLatin1());
	else if(type == QGLShader::Fragment)
		m_effect->setFragmentShader(code.toLatin1());
}
void MgAbstractShader::setShaderSourceCodeFromFile(QGLShader::ShaderType type,const QString & file)
{
	if(type == QGLShader::Vertex)
		m_effect->setVertexShaderFromFile(file);
	else if(type == QGLShader::Fragment)
		m_effect->setFragmentShaderFromFile(file);

}
QGLShaderProgramEffect * MgAbstractShader::effect()const
{
	return m_effect;
}

QGLShaderProgram * MgAbstractShader::program()const
{
	return m_effect->program();
}

void MgAbstractShader::setActive(QGLPainter* painter,bool flag)
{
	m_effect->setActive(painter,flag);
	if(flag)
	{
		m_effect->update(painter,QGLPainter::UpdateAll);
		painter->setUserEffect(m_effect);
	}
}
void MgAbstractShader::init(QGLPainter* p)
{
	preInit();
	setActive(p,true);
	setActive(p,false);
	postInit();

}
