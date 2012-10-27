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
#ifndef TESTOBJECT_H_
#define TESTOBJECT_H_

#include <QObject>
#include <QStringList>
#include <QVariant>
#include <QVector3D>
#include <QTimer>
#include <QDebug>
#include <MgCore/MgGlobal>

class TestObject : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString parameter1 READ parameter1 WRITE setParameter1 NOTIFY parameter1Changed )
	Q_PROPERTY(QVector3D parameter2 READ parameter2 WRITE setParameter2 NOTIFY parameter2Changed )
	Q_PROPERTY(double parameter3 READ parameter3 WRITE setParameter3 NOTIFY parameter3Changed )
public:
	TestObject(QObject * parent =0):QObject(parent)
	{
		p1= "p1";
		p2 = QVector3D(1,2,3);
		p3 = 3.0;
		QStringList properties;
		MG_EXPOSE_PROPERTIES("parameter1,parameter2,parameter3");
//		MG_SET_ATTRIBUTE("parameter2","minimum",0);
//		MG_SET_ATTRIBUTE("parameter2","maximum",10);

		QTimer * timer =new QTimer(this);
		timer->setInterval(1000);
		timer->setSingleShot(false);
		connect(timer,SIGNAL(timeout()),this,SLOT(incrementP3()));
		timer->start();


	}
	virtual ~TestObject(){}


	Q_INVOKABLE void incrementP3()
	{
		setParameter3(p3+1);
	}

	QString p1;
	QVector3D p2;
	double p3;



	QString parameter1()const{return p1;}
	void setParameter1(const QString & v)
	{
		if(v != p1)
		{
			p1=v;
			qDebug()<<"parameter 1 changed to"<<v;
			Q_EMIT parameter1Changed();
		}

	}


	QVector3D parameter2()const{return p2;}
	void setParameter2(const QVector3D & v)
	{
		if(v != p2)
		{
			p2=v;
			qDebug()<<"parameter 2 changed to"<<v;
			Q_EMIT parameter2Changed();
		}

	}

	double parameter3()const{return p3;}
	void setParameter3(double  v)
	{
		qDebug()<<p3<<"parameter 3 will be changed to"<<v;
		if(v != p3)
		{
			p3=v;
			qDebug()<<"parameter 3 changed to"<<v;
			Q_EMIT parameter3Changed();
		}

	}

Q_SIGNALS:
	void parameter1Changed();
	void parameter2Changed();
	void parameter3Changed();


};

#endif /* TESTOBJECT_H_ */
