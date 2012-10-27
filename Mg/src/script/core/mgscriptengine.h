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
#ifndef MGSCRIPTENGINE_H_
#define MGSCRIPTENGINE_H_

#include <QString>
#include <QScriptEngine>
#include <QUrl>
#include <QObject>
#include <QStringList>
#include <QScriptable>
#include <QHash>

//MG_INCLUDE_INFO:MgScriptEngine

class MgScriptEngine : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList registeredObjects READ registeredObjectsNames)
	Q_PROPERTY(QString cachedProgram READ cachedProgram WRITE setCachedProgram)

	Q_CLASSINFO("MG_SLOTS",""
			"execCommand,"
			"execFile,"
			"execCachedProgram")


public:
	MgScriptEngine(QObject * parent=0);
	virtual ~MgScriptEngine();
	QStringList registeredObjectsNames()const{return m_registerdObjects.keys();}

	QScriptEngine *  engine(){return &m_engine;}

	QString cachedProgram()const
	{
		return m_cachedProgram;
	}
	void setCachedProgram(const QString & p)
	{
		m_cachedProgram = p;
	}
	QStringList commandCompletion(const QString&);
	QList<QObject*> registerdObjects()const{return m_registerdObjects.values();}
	virtual QString showObjectInfo(QObject * );

	QStringList invokableMethodsOf(const QString & name,const QString & stringBegin="")const;
	QStringList propertiesOf(const QString & name,const QString & stringBegin="")const;

	QStringList exportedSlotsOf(const QString & name,const QString & prefix,Qt::CaseSensitivity cs)const;
	QStringList exportedPropertiesOf(const QString & name,const QString & prefix,Qt::CaseSensitivity cs)const;



public Q_SLOTS:

	QString execCommand(const QString & cmd);
	QString execFile(const QString &);
	QString execCachedProgram();
	void registerObject(QObject * );
	void registerFunction(const QString & ,const QString &);


Q_SIGNALS:
	void objectRegistered();
	void commandExecuted(const QString & cmd,const QString & reply);

protected:
	virtual void setProperty(const QString & ,const QScriptValue & value);
private:
	QScriptEngine m_engine;
	QString m_cachedProgram;
	QHash<QString,QObject*> m_registerdObjects;

};


#endif /* MGSCRIPTENGINE_H_ */
