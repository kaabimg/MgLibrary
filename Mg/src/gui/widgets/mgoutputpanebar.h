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
#ifndef MGOUTPUTPANEBAR_H_
#define MGOUTPUTPANEBAR_H_

//MG_INCLUDE_INFO:MgOutputPaneBar

#include <QtGui/QWidget>
#include <MgCore/MgGlobal>
class MgOutputPaneToggleButton;

MG_USE_PRIVATE_CLASS(MgOutputPaneBar)

class MgOutputPaneBar : public QWidget
{
	Q_OBJECT
public:
	MgOutputPaneBar(QWidget * parent =0);
	virtual ~MgOutputPaneBar();

	void addWidget(QWidget *);
	void addPane(const QString &text );

public Q_SLOTS:
	void untoggleButton(const QString&);

Q_SIGNALS:
	void showRequest(QString);
	void hideRequest(QString);

protected:
	void paintEvent(QPaintEvent *event);

protected Q_SLOTS:
	void paneButtonToggled(bool);

private:
	MG_PRIVATE_CLASS(MgOutputPaneBar)

};

#endif /* MGOUTPUTPANEBAR_H_ */
