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
#ifndef MGGLOBALMACROS_H_
#define MGGLOBALMACROS_H_

//MG_INCLUDE_INFO:MgGlobal


#include <QtCore/QtGlobal>
#include <QVariant>
#include <QStringList>
#include <cstdio>

class MgMessagesHandler
{
public:
	static void mgMessagesHandler(QtMsgType type, const char *msg)
	{
#ifdef MG_DEBUG_MSG
		switch (type)
		{
		case QtDebugMsg:
			fprintf(stderr, "Debug   : %s\n", msg);
			break;
		case QtWarningMsg:
			fprintf(stderr, "Warning : %s\n", msg);
			break;
		case QtCriticalMsg:
			fprintf(stderr, "Critical: %s\n", msg);
			break;
		case QtFatalMsg:
			fprintf(stderr, "Fatal   : %s\n", msg);
			abort();
			break;
		}
#else
		Q_UNUSED(type)
		Q_UNUSED(msg)
#endif
	}

};


#if defined(MG_LIBRARY)
#  define MG_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define MG_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

#define MG_STRINGIFY(str) #str

#define MG_MAKE_OBJECT_INSTANTIABLE(Type) Q_SCRIPT_DECLARE_QMETAOBJECT(Type, QObject*)
#define MG_MAKE_WIDGET_INSTANTIABLE(Type) Q_SCRIPT_DECLARE_QMETAOBJECT(Type, QWidget*)


#define MG_REGISTER_TYPE(Type,engine) \
		engine->globalObject().setProperty(#Type, engine->scriptValueFromQMetaObject<Type>())

#define MG_USE_PRIVATE_CLASS(Class) class Class##Private;

#define MG_PRIVATE_CLASS(Class) \
		Class##Private * d_ptr; \
		friend class Class##Private;


#define MG_TEST_FOR_DEBUG_AND_EXIT(condition,message,returnValue) \
		if(condition)\
		{\
			qDebug()<<message;\
			return returnValue;\
		}

#define MG_EXIT_FALSE_IF(condition,message) MG_TEST_FOR_DEBUG_AND_EXIT(condition,message,false)
#define MG_EXIT_NULL_IF(condition,message)  MG_TEST_FOR_DEBUG_AND_EXIT(condition,message,NULL)



#define MG_BEGIN_NAMESPACE(name) namespace name {
#define MG_END_NAMESPACE }


#endif /* MGGLOBALMACROS_H_ */
