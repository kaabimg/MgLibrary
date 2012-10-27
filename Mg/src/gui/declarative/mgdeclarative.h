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
#ifndef MGDECLARATIVE_H_
#define MGDECLARATIVE_H_

#include <QGraphicsProxyWidget>


#define MG_QML_EXTENSION(Class) \
		class Class##Proxy : public QGraphicsProxyWidget \
		{\
     	 	 \
  	  	  public:\
      		Class##Proxy(QGraphicsItem* parent = 0): QGraphicsProxyWidget(parent)\
    		{\
      			widget = new Class();\
      			setWidget(widget);\
    		}\
  	  	  private:\
      		Class *widget;\
      	};\
\
		class Class##Proxy##Registrer\
		{\
		 	private:\
		 	Class##Proxy##Registrer()\
			{\
				qmlRegisterType<Class##Proxy>("MgLibrary",(int) MG_LIBRARY_MAJOR_VERSION,(int) MG_LIBRARY_MINOR_VERSION, #Class);\
			}\
			~Class##Proxy##Registrer(){}\
			static Class##Proxy##Registrer * privateInstance;\
		};\
		Class##Proxy##Registrer * Class##Proxy##Registrer::privateInstance = new Class##Proxy##Registrer;



#endif /* MGDECLARATIVE_H_ */
