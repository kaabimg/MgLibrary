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
#ifndef MGMESSAGESAREAWIDGET_H_
#define MGMESSAGESAREAWIDGET_H_


//MG_INCLUDE_INFO:MgMessagesAreaWidget

#include <QTableWidget>

class MgMessagesEmitter;
class QIcon;

class MgMessagesAreaWidget : public QTableWidget
{
	Q_OBJECT
public:
	MgMessagesAreaWidget(QWidget * parent=0);
	virtual ~MgMessagesAreaWidget();

public Q_SLOTS:
	void registerSender(MgMessagesEmitter  *);

	void informationMessage(const QString&);
	void warningMessage(const QString&);
	void errorMessage(const QString&);

protected:
	void addMessage(const QIcon &,const QString &);
	void resizeEvent(QResizeEvent *);
	void registerEmitter(QObject *);

private:
	int m_totalMessages;

};

#endif /* MGMESSAGESAREAWIDGET_H_ */
