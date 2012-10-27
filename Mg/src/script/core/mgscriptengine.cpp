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
#include "mgscriptengine.h"


#include <QFile>
#include <QTextStream>
#include <QMetaProperty>
#include <QDebug>

#include "mgscriptengineobjectinfo.h"

MgScriptEngine::MgScriptEngine(QObject * parent):QObject(parent)
{
	setObjectName("scriptEngine");
	registerObject(this);
	registerFunction("showObjectInfo()","return scriptEngine.showObjectInfo(arguments[0]);");
	registerFunction("registeredObjects()","return scriptEngine.registeredObjects;");
}

MgScriptEngine::~MgScriptEngine() {}

void MgScriptEngine::registerObject(QObject * obj)
{
	if( !obj ||
		obj->objectName().isEmpty() ||
		m_registerdObjects.contains(obj->objectName()) )
		return;

	QScriptValue objectValue = m_engine.newQObject(obj);
	m_engine.globalObject().setProperty(obj->objectName(), objectValue);
	m_registerdObjects.insert(obj->objectName(),obj);
	Q_EMIT objectRegistered();
}

void MgScriptEngine::registerFunction(const QString & signature,const QString & code)
{
	m_engine.evaluate("function "+signature+"{"+code+"}");
}

QString MgScriptEngine::execCommand(const QString & cmd)
{
	QString reply = m_engine.evaluate(cmd).toString();
	Q_EMIT commandExecuted(cmd,reply);
	return reply;
}


QString MgScriptEngine::execCachedProgram()
{
	QString reply = m_engine.evaluate(m_cachedProgram).toString();
	Q_EMIT commandExecuted(objectName()+".execCachedProgram();",reply);
	return reply;

}
QString  MgScriptEngine::execFile(const QString &fileName )
{
	 QFile scriptFile(fileName);
	 if (!scriptFile.open(QIODevice::ReadOnly))
	 {
		 Q_EMIT commandExecuted(objectName()+".execFile('"+fileName+"');","Error while opening "+fileName);
		 return "Error while opening "+fileName;
	 }
	 QTextStream stream(&scriptFile);
	 QString contents = stream.readAll();
	 scriptFile.close();

	 QString reply = m_engine.evaluate(contents).toString();
	 Q_EMIT commandExecuted(objectName()+".execFile('"+fileName+"');",reply);
	 return reply;
}

void MgScriptEngine::setProperty(const QString & name ,const QScriptValue & value)
{
	m_engine.globalObject().setProperty(name,value);
}

QString MgScriptEngine::showObjectInfo(QObject * obj)
{
	if(obj==0)
		return "null object";
	QString result;

	result+="object name :\n\t";result+=obj->objectName();result+="\n";
	result+="class name :\n\t";result+=obj->metaObject()->className();result+="\n";
	result+="super class :\n\t";result+=obj->metaObject()->superClass()->className();result+="\n";


	if(obj->metaObject()->propertyCount())
	{
		result+="\n";
		result+=QString("properties : \n");
	}

	for (int i = 0; i < obj->metaObject()->propertyCount(); ++i)
	{
		result+="\t";
		result+=obj->metaObject()->property(i).typeName();
		result+=" ";
		result+=obj->metaObject()->property(i).name();
		result+=";\n";
	}
	QString dynamicProperiesNames;
	int size=obj->dynamicPropertyNames().size();
	result+="dynamic properties : \n";
	result+="\t";
	if(size)
		for (int i = 0; i < size; ++i)
		{
			result+=obj->dynamicPropertyNames()[i];
			result+=" ";
		}
	else
		result+="empty";

//	scriptEngine.showObjectInfo(scriptEngine)
	if(obj->metaObject()->methodCount())
	{
		result+="\n";
		result+="\n";
		result+=QString("public invocable methods : ");
	}
	for (int i = 0; i < obj->metaObject()->methodCount(); ++i)
	{
		if(obj->metaObject()->method(i).access()==QMetaMethod::Public)
		{
			result+="\n";
			result+="\t";
			result+=QString(obj->metaObject()->method(i).typeName()).isEmpty() ? "void" : obj->metaObject()->method(i).typeName() ;
			result+=" ";
			result+=obj->metaObject()->method(i).signature();
			result+=";";
		}
	}

	return result;
}

/******************************************************************************************/

QStringList MgScriptEngine::invokableMethodsOf(const QString & name,const QString & stringBegin)const
{
	QStringList methods;
	QScriptValue objectValue= m_engine.globalObject().property(name);
	if(!objectValue.isValid())
		return methods;
	QObject * theObject = objectValue.toQObject();

	if(!theObject)
		return methods;
	if(stringBegin.isEmpty())
	{
		for (int i = 0; i < theObject->metaObject()->methodCount(); ++i)
			if(theObject->metaObject()->method(i).access()==QMetaMethod::Public)
				methods<<theObject->metaObject()->method(i).signature();
	}
	else
	{
		for (int i = 0; i < theObject->metaObject()->methodCount(); ++i)
			if(theObject->metaObject()->method(i).access()==QMetaMethod::Public)
				if(QString(theObject->metaObject()->method(i).signature()).startsWith(stringBegin,Qt::CaseInsensitive))
					methods<<theObject->metaObject()->method(i).signature();
	}
	return methods;

}
QStringList MgScriptEngine::propertiesOf(const QString & name,const QString & stringBegin)const
{
	QStringList properties;
	QScriptValue objectValue= m_engine.globalObject().property(name);
	if(!objectValue.isValid())
		return properties;
	QObject * theObject = objectValue.toQObject();

	if(!theObject)
		return properties;
	if(stringBegin.isEmpty())
	{
		for (int i = 0; i < theObject->metaObject()->propertyCount(); ++i)
			properties<<QChar('(')+QString(theObject->metaObject()->property(i).typeName())+" "+QString(theObject->metaObject()->property(i).name())+QChar(')');
	}
	else
	{
		for (int i = 0; i < theObject->metaObject()->propertyCount(); ++i)
			if(QString(theObject->metaObject()->property(i).name()).startsWith(stringBegin,Qt::CaseInsensitive))
				properties<<QChar('(')+QString(theObject->metaObject()->property(i).typeName())+" "+QString(theObject->metaObject()->property(i).name())+QChar(')');
	}
	return properties;
}



QStringList MgScriptEngine::exportedSlotsOf(
		const QString & name,
		const QString & prefix,
		Qt::CaseSensitivity cs)const
{
	QObject * obj = m_registerdObjects.value(name);
	if(!obj)
		return QStringList();

	return MgScriptEngineObjectInfo::exportedSlotsOf(obj,prefix,cs);
}
QStringList MgScriptEngine::exportedPropertiesOf(
		const QString & name,
		const QString & prefix,
		Qt::CaseSensitivity cs)const
{
	QObject * obj = m_registerdObjects.value(name);
	if(!obj)
		return QStringList();
	return MgScriptEngineObjectInfo::exportedPropertiesOf(obj,prefix,cs);
}



/***************************************************************************************************/


QStringList MgScriptEngine::commandCompletion(const QString& currentCmd)
{
	if(currentCmd.contains('.'))
	{
		if(currentCmd.contains('('))
		{
			return QStringList();
		}
		if(currentCmd.count('.')!=1)
		{
			return QStringList();
		}
		QString objectName =currentCmd.split('.').first();
		QString methodSignature=currentCmd.split('.').last();
		QStringList properties  = propertiesOf(objectName,methodSignature);
		QStringList methods     = invokableMethodsOf(objectName,methodSignature);
		return properties+methods;
	}
	else
	{
		QStringList completition;
		foreach(QString obj,registeredObjectsNames())
		{
			if(obj.startsWith(currentCmd,Qt::CaseInsensitive))
				completition<<obj;
		}
		return completition;
	}
}
