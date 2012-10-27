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
#ifndef MGVIDEOPLAYER_H_
#define MGVIDEOPLAYER_H_

//MG_INCLUDE_INFO:MgVideoPlayer

#include <QWidget>

#include <MgCore/MgGlobal>

MG_USE_PRIVATE_CLASS(MgVideoPlayer)

class MgVideoPlayer : public QWidget
{
	Q_OBJECT

public:
	MgVideoPlayer(QWidget * parent = 0);
	virtual ~MgVideoPlayer();

private:
	MG_PRIVATE_CLASS(MgVideoPlayer)
	Q_DISABLE_COPY(MgVideoPlayer)

};

#endif /* MGVIDEOPLAYER_H_ */
