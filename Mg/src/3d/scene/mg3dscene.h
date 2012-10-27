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
#ifndef MG3DSCENE_H_
#define MG3DSCENE_H_

//MG_INCLUDE_INFO:Mg3dScene

#include <Qt3D/qglview.h>

#include <MgCore/MgGlobal>

class MgCoordinatesManager;
class QGLSceneNode ;
class QGLFramebufferObjectSurface;

MG_USE_PRIVATE_CLASS(Mg3dScene)


class Mg3dScene : public QGLView
{
	Q_OBJECT

	Q_PROPERTY(bool showReference READ showReference WRITE setShowReference NOTIFY referenceShown)
	Q_CLASSINFO("showReference_uname","Show reference")

	Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid NOTIFY gridShown)
	Q_CLASSINFO("showGrid_uname","Show grid")

	Q_PROPERTY(QVector3D cameraPosition READ cameraPosition WRITE setCameraPosition NOTIFY cameraPositionChanged)
	Q_CLASSINFO("cameraPosition_uname","Camera position")

	Q_PROPERTY(QVector3D cameraCenter READ cameraCenter WRITE setCameraCenter NOTIFY cameraCenterChanged)
	Q_CLASSINFO("cameraCenter_uname","Camera center")

	Q_PROPERTY(QVector3D cameraUpVector READ cameraUpVector WRITE setCameraUpVector NOTIFY cameraUpVectorChanged)
	Q_CLASSINFO("cameraUpVector_uname","Camera up vector")

	Q_CLASSINFO("MG_PROPERTIES","showReference,showGrid,cameraPosition,cameraCenter,cameraUpVector")

public:
	explicit Mg3dScene(QWidget*parent=0);
	virtual ~Mg3dScene();


	bool showReference()const;
	void setShowReference(bool);

	bool showGrid()const;
	void setShowGrid(bool);

	void setCameraPosition(const QVector3D &);
	QVector3D cameraPosition()const;

	void setCameraCenter(const QVector3D &);
	QVector3D cameraCenter()const;

	void setCameraUpVector(const QVector3D &);
	QVector3D cameraUpVector()const;


	static float remapVal(float value,float origin_low,float origin_high,float dest_low,float dest_high);

Q_SIGNALS:
	void gridShown(bool);
	void referenceShown(bool);

	void cameraPositionChanged(const QVector3D &);
	void cameraCenterChanged(const QVector3D &);
	void cameraUpVectorChanged(const QVector3D &);

public Q_SLOTS:

protected Q_SLOTS:
	void updateGLContent();

protected:
	void paintGL();
    void initializeGL(QGLPainter * );

    void keyPressEvent(QKeyEvent*);

    QGLFramebufferObjectSurface * createFboSurface(const QSize &)const;
    void destroyFboSurface(QGLFramebufferObjectSurface *);

    void resizeFbo(QGLFramebufferObjectSurface * &,const QSize &);

    void clearStateText();
    void setStateTextSize(int);
    void setStateText(int,const QString&);

    void updateFps();
    void drawStateText(QGLPainter *painter);
    void drawText(QGLPainter *painter,const QStringList& str);

    void drawFboVertices(QGLPainter * painter);

    void drawGridAndReference(QGLPainter *);


    void drawFboSurface(QGLFramebufferObjectSurface *  ,QGLPainter *);
    void drawFboSurface(QGLFramebufferObjectSurface *,const QVector2D &,const QVector2D & ,QGLPainter *);


private:
    MG_PRIVATE_CLASS(Mg3dScene)
    Q_DISABLE_COPY(Mg3dScene)

};


///////: helpers

#define MG_START_SURFACE(painter,surface) painter->pushSurface(surface)
#define MG_END_SURFACE(painter) painter->popSurface()
#define CHECK_GL_ERROR if(GLenum error = glGetError()!=GL_NO_ERROR)qDebug()<<"Gl error"<<error<<"!!!";



#endif /* MG3DSCENE_H_ */
