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
#ifndef MGCAMERAANIMATION_H_
#define MGCAMERAANIMATION_H_
//MG_INCLUDE_INFO:MgCameraAnimation

#include <MgCore/MgGlobal>
#include <QObject>
#include <QVector3D>

class Mg3dScene;

MG_USE_PRIVATE_CLASS(MgCameraAnimation)

class MgCameraAnimation : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged SCRIPTABLE true)
	Q_PROPERTY(AnimationType animationType READ animationType)
	Q_PROPERTY(Mg3dScene* scene READ scene WRITE setScene NOTIFY sceneChanged SCRIPTABLE true )


	Q_CLASSINFO("MG_PROPERTIES","animationDuration")
	Q_CLASSINFO("MG_SLOTS","start,"
			"pause,"
			"stop,"
			"addCameraPositionPoint,"
			"addCameraCenterPoint,"
			"clearCameraPositionPoints,"
			"clearCameraCenterPoints,"
			"clear")

public:
	enum AnimationType
	{
		Undefined,
		CameraPositionAnimation,
		CameraCenterAnimation,
		CameraPositionAndCenterAnimation
	};
	Q_ENUMS(AnimationType)

	MgCameraAnimation(QObject * parent = 0);
	virtual ~MgCameraAnimation();

	int animationDuration()const;
	void setAnimationDuration(int);
	AnimationType animationType()const;

	void setScene(Mg3dScene *);
	Mg3dScene * scene()const;

public Q_SLOTS:
	void start();
	void pause();
	void stop();

	void addCameraPositionPoint(const QVector3D &);
	void addCameraCenterPoint(const QVector3D &);
	void clearCameraPositionPoints();
	void clearCameraCenterPoints();
	void clear();

Q_SIGNALS:
	void started();
	void paused();
	void stopped();
	void animationDurationChanged(int);
	void sceneChanged(Mg3dScene*);

protected Q_SLOTS:
	void update();



private:
	MG_PRIVATE_CLASS(MgCameraAnimation)
	Q_DISABLE_COPY(MgCameraAnimation)
};

#endif /* MGCAMERAANIMATION_H_ */
