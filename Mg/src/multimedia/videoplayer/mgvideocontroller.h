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
#ifndef MGVIDEOCONTROLLER_H_
#define MGVIDEOCONTROLLER_H_


//MG_INCLUDE_INFO:MgVideoController


#include <QObject>
#include <MgCore/MgGlobal>
namespace Phonon {
	class MediaObject;
}
class QToolBar;

MG_USE_PRIVATE_CLASS(MgVideoController)

class MgVideoController : public QObject
{
	Q_OBJECT
public:
	MgVideoController(QObject  * parent= 0);
	virtual ~MgVideoController();

	void setMediaObject(Phonon::MediaObject*);
	QToolBar * toolBar();

Q_SIGNALS:

	void playing();
	void paused();
	void stopped();

private:
	MG_PRIVATE_CLASS(MgVideoController)
	Q_DISABLE_COPY(MgVideoController)

	Q_SLOT void playOrPause();
	Q_SLOT void stop();
	Q_SLOT void onStateChanged();//do not use argument to not include phonon in this header

};

#endif /* MGVIDEOCONTROLLER_H_ */
