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
#ifndef MG3DHELPERS_H_
#define MG3DHELPERS_H_

//MG_INCLUDE_INFO:Mg3DHelpers

#include <Qt3D/qglscenenode.h>
#include <QDebug>
class QGLMaterial;

class  Mg3DHelpers
{
public:
	static void viewNormals(QGLSceneNode  * node,bool view)
	{
		node->setOption(QGLSceneNode::ViewNormals,true);
		foreach(QGLSceneNode * subNode,node->children())
			subNode->setOption(QGLSceneNode::ViewNormals,view);
	}


	static void setRecursiveFrontMaterial(QGLSceneNode  * node,QGLMaterial * mat)
	{
		node->setMaterial(mat);
		foreach(QGLSceneNode * subNode,node->children())
			setRecursiveFrontMaterial(subNode,mat);
	}

	static void setRecursiveBackMaterial(QGLSceneNode  * node,QGLMaterial * mat)
	{
		node->setBackMaterial(mat);
		foreach(QGLSceneNode * subNode,node->children())
			setRecursiveBackMaterial(subNode,mat);
	}
	static void debugNodeGeometry(QGLSceneNode  * node,int depth=0)
	{
		QString offset;
		for (int i = 0; i < depth; ++i)
			offset += "  ";
		qDebug()<<offset<<node<<node->objectName();
		qDebug()<<offset<<node->geometry();
		foreach(QGLSceneNode * subNode,node->children())
			debugNodeGeometry(subNode,depth+1);

	}



} ;

#endif /* MG3DHELPERS_H_ */
