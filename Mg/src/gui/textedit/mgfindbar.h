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
#ifndef MGFINDBAR_H_
#define MGFINDBAR_H_
#include <QWidget>

#include <MgCore/MgGlobal>

MG_USE_PRIVATE_CLASS(MgFindBar)

class MgFindBar : public QWidget
{
	Q_OBJECT
public:
	MgFindBar(QWidget * parent=0);
	virtual ~MgFindBar();


Q_SIGNALS:
	void findRequest(const QString &,Qt::CaseSensitivity);
	void findAndReplaceRequest(const QString&,const QString&,Qt::CaseSensitivity);
	void findAndReplaceAllRequest(const QString &,const QString&,Qt::CaseSensitivity);

private:
	MG_PRIVATE_CLASS(MgFindBar)
	Q_DISABLE_COPY(MgFindBar)

};

#endif /* MGFINDBAR_H_ */
