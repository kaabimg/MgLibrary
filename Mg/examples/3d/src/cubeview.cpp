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
** along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
** 
****************************************************************************/
#include "cubeview.h"
#include <Qt3D/qglcube.h>
#include <Qt3D/qglteapot.h>
#include <QtOpenGL/qglframebufferobject.h>
#include <QtCore/qpropertyanimation.h>

//! [1]
CubeView::CubeView(QWidget *parent)
    : QGLView(parent)
    , fbo(0)
    , tangle(0.0f)
    , cangle(0.0f)
    , oangle(0.0f)
{
    QGLBuilder builder;


    builder.newSection(QGL::Faceted);
//    builder << QGLCube(1.5f);
    builder.addPane(3);
    cube = builder.currentNode();
    cube->setObjectName(QLatin1String("Cube"));

    builder.newSection();
    builder << QGLTeapot();
    teapot = builder.currentNode();
    teapot->setObjectName(QLatin1String("Teapot"));

    scene = builder.finalizedSceneNode();
    scene->setParent(this);
    innerCamera = new QGLCamera(this);
}
//! [3]

CubeView::~CubeView()
{
    delete fbo;
}


void CubeView::initializeGL(QGLPainter *)
{
    fbo = new QGLFramebufferObject(1024, 1024, QGLFramebufferObject::Depth);

    fboSurface.setFramebufferObject(fbo);

    glEnable(GL_BLEND);
}


void CubeView::paintGL(QGLPainter *painter)
{
//    painter->modelViewMatrix().push();

    painter->pushSurface(&fboSurface);

    painter->setFaceColor(QGL::AllFaces, QColor(170, 202, 0));
    painter->setStandardEffect(QGL::LitMaterial);
//    painter->setCamera(innerCamera);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    teapot->draw(painter);

    painter->popSurface();
//    painter->projectionMatrix().pop();
//    painter->modelViewMatrix().pop();

//    painter->modelViewMatrix().rotate(oangle, 0.0f, 1.0f, 0.0f);

    QVector3D posn(1.5f, 0.0f, 0.0f);

//    painter->modelViewMatrix().push();


 	painter->setFaceColor(QGL::AllFaces, QColor(0, 0, 0, 125));
    painter->setStandardEffect(QGL::LitDecalTexture2D);
    glBindTexture(GL_TEXTURE_2D, fbo->texture());
    glEnable(GL_TEXTURE_2D);


//    painter->modelViewMatrix().translate(posn);
//    painter->modelViewMatrix().rotate(cangle, 1.0f, 1.0f, 1.0f);

//    glCullFace(GL_FRONT);
//    glEnable(GL_CULL_FACE);
    cube->draw(painter);
//    glCullFace(GL_BACK);
//    cube->draw(painter);
//    glDisable(GL_CULL_FACE);
////
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

//    painter->modelViewMatrix().pop();
}

void CubeView::drawCube2(QGLPainter *painter, const QVector3D &posn)
{

}
//! [11]
