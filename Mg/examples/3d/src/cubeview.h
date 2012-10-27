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
#ifndef CUBEVIEW_H
#define CUBEVIEW_H

#include <Qt3D/qglview.h>
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qglframebufferobjectsurface.h>

class QGLFramebufferObject;
class QGLCamera;

class CubeView : public QGLView
{
    Q_OBJECT
    Q_PROPERTY(qreal teapotAngle READ teapotAngle WRITE setTeapotAngle)
    Q_PROPERTY(qreal cubeAngle READ cubeAngle WRITE setCubeAngle)
    Q_PROPERTY(qreal orbitAngle READ orbitAngle WRITE setOrbitAngle)
public:
    CubeView(QWidget *parent = 0);
    ~CubeView();

    qreal teapotAngle() const { return tangle; }
    void setTeapotAngle(qreal angle) { tangle = angle; update(); }

    qreal cubeAngle() const { return cangle; }
    void setCubeAngle(qreal angle) { cangle = angle; update(); }

    qreal orbitAngle() const { return oangle; }
    void setOrbitAngle(qreal angle) { oangle = angle; update(); }

protected:
    void initializeGL(QGLPainter *painter);
    void paintGL(QGLPainter *painter);

private:
    QGLSceneNode *scene;
    QGLSceneNode *cube;
    QGLSceneNode *teapot;
    QGLTexture2D qtlogo;
    QGLFramebufferObject *fbo;
    QGLFramebufferObjectSurface fboSurface;
    QGLCamera *innerCamera;
    qreal tangle;
    qreal cangle;
    qreal oangle;

    void drawCube2(QGLPainter *painter, const QVector3D &posn);
};

#endif
