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
#include "mgcameraanimation.h"
#include "mg3dscene.h"

#include <QVector>
#include <QTimer>
#include <QDebug>


struct MgCameraAnimationPrivate
{
	QVector<QVector3D> cameraPositions;
	QVector<QVector3D> cameraCenters;
	Mg3dScene * scene;
	int animationDuration;
	int updateInterval;
	int currentTime;
	QTimer updateTimer;
	int currentUpdateIndex;
};

MgCameraAnimation::MgCameraAnimation(QObject * parent)
	:QObject(parent)
{
	d_ptr = new MgCameraAnimationPrivate;
	d_ptr->scene = 0;
	d_ptr->animationDuration = 5000;
	d_ptr->updateInterval = 100;
	d_ptr->currentUpdateIndex = 0;
	d_ptr->currentTime = 0;
	connect(&d_ptr->updateTimer,SIGNAL(timeout()),this,SLOT(update()));


}

MgCameraAnimation::~MgCameraAnimation()
{
	delete d_ptr;
}

int MgCameraAnimation::animationDuration()const
{
	return d_ptr->animationDuration;
}
void MgCameraAnimation::setAnimationDuration(int d)
{
	if(d_ptr->animationDuration != d)
	{
		d_ptr->animationDuration = d;
		Q_EMIT animationDurationChanged(d);
	}
}

MgCameraAnimation::AnimationType MgCameraAnimation::animationType()const
{
	if(d_ptr->cameraPositions.isEmpty() ||
		d_ptr->cameraCenters.isEmpty())
		return Undefined;

	if(d_ptr->cameraPositions.size()>1)
	{
		if(d_ptr->cameraCenters.size()>1)
			return CameraPositionAndCenterAnimation;
		else
			return CameraPositionAnimation;
	}
	else
	{
		if(d_ptr->cameraCenters.size()>1)
			return CameraCenterAnimation;
		else
			return Undefined;
	}
}

void MgCameraAnimation::setScene(Mg3dScene * scene)
{
	if(d_ptr->scene != scene)
	{
		d_ptr->scene = scene;
		Q_EMIT sceneChanged(scene);
	}
}
Mg3dScene * MgCameraAnimation::scene()const
{
	return d_ptr->scene;
}

void MgCameraAnimation::start()
{
	if(	d_ptr->scene == 0 ||
		animationType()== Undefined  ||
		d_ptr->updateTimer.isActive())
		return;


	d_ptr->cameraPositions.prepend(d_ptr->scene->cameraPosition());
	d_ptr->updateTimer.setInterval(d_ptr->updateInterval);
	d_ptr->updateTimer.start();
	Q_EMIT started();


}
void MgCameraAnimation::pause()
{
	d_ptr->updateTimer.stop();
	Q_EMIT paused();
}
void MgCameraAnimation::stop()
{
	d_ptr->updateTimer.stop();
	d_ptr->currentUpdateIndex = 0;
	d_ptr->currentTime = 0;
	d_ptr->cameraPositions.remove(0);
	Q_EMIT stopped();

}

float remapValue(float value,float origin_low,float origin_high,float dest_low,float dest_high)
{
	return dest_low + (dest_high - dest_low) * (value - origin_low) / (origin_high - origin_low);
}


QVector3D interpolatePosition(const QVector3D & start,const QVector3D & end,float factor)
{
	return start + (end-start) * factor ;
}


void MgCameraAnimation::update()
{
	d_ptr->currentTime += d_ptr->updateInterval;

	if(d_ptr->currentTime >= d_ptr->animationDuration)
	{
		stop();
		return;
	}

	int positionIndex = remapValue(
			d_ptr->currentTime,
			0,
			d_ptr->animationDuration,
			0,
			d_ptr->cameraPositions.size());

	int centerIndex = remapValue(
			d_ptr->currentTime,
			0,
			d_ptr->animationDuration,
			0,
			d_ptr->cameraCenters.size());

	int positionsInterval = d_ptr->animationDuration / d_ptr->cameraPositions.size();
	int centersInterval = d_ptr->animationDuration / d_ptr->cameraCenters.size();

	float positionInterpolationFactor = (float)(d_ptr->currentTime % positionsInterval)/ positionsInterval;
	float centerInterpolationFactor =(float)(d_ptr->currentTime % centersInterval)/ centersInterval;


	d_ptr->scene->setCameraPosition(interpolatePosition(
			d_ptr->cameraPositions.at(positionIndex),
			d_ptr->cameraPositions.at(qMin(positionIndex+1,d_ptr->cameraPositions.size()-1)),
			positionInterpolationFactor));

	d_ptr->scene->setCameraCenter(interpolatePosition(
			d_ptr->cameraCenters.at(centerIndex),
			d_ptr->cameraCenters.at(qMin(centerIndex+1,d_ptr->cameraCenters.size()-1)),
			centerInterpolationFactor));

	static const QVector3D z(0,0,1);

	d_ptr->scene->setCameraUpVector(z);
}

void MgCameraAnimation::addCameraPositionPoint(const QVector3D & p)
{
	d_ptr->cameraPositions.append(p);
}
void MgCameraAnimation::addCameraCenterPoint(const QVector3D & p)
{
	d_ptr->cameraCenters.append(p);
}
void MgCameraAnimation::clearCameraPositionPoints()
{
	d_ptr->cameraPositions.clear();
}
void MgCameraAnimation::clearCameraCenterPoints()
{
	d_ptr->cameraCenters.clear();
}

void MgCameraAnimation::clear()
{
	clearCameraPositionPoints();
	clearCameraCenterPoints();
}


