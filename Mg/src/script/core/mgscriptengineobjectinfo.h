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
#ifndef MGSCRIPTENGINEOBJECTINFO_H_
#define MGSCRIPTENGINEOBJECTINFO_H_


//TODO : this class should be moved to MgCore to be used in the properties editor

#include <QObject>
#include <QStringList>

class MgScriptEngineObjectInfo
{
public:
	MgScriptEngineObjectInfo(){}
	~MgScriptEngineObjectInfo(){}


	static QStringList exportedPropertiesOf(const QObject *);
	static QStringList exportedPropertiesOf(const QObject *,const QString & prefix,Qt::CaseSensitivity cs);

	static QString typeOf(const QObject * obj,const QString & property);
	static QString notifySignalOf(const QObject * obj,const QString & property);

	static bool isPropertyWritable(const QObject * obj,const QString & property);

	/*!
	 * Returns 'signature : return_type'
	 */
	static QStringList exportedSlotsOf(const QObject *);
	static QStringList exportedSlotsOf(const QObject *,const QString & prefix,Qt::CaseSensitivity cs);
	static QString slotInfoOf(const QObject *,const QString & slotName);
};

#endif /* MGSCRIPTENGINEOBJECTINFO_H_ */
