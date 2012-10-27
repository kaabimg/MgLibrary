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
#include "mgapplicationmonitor.h"

#include <MgScript/MgScriptEngine>

#include <QChildEvent>
#include <QKeyEvent>


#include "mgtestfunctionswrapper.h"



MgApplicationMonitor::MgApplicationMonitor()
{
	m_objectNameSeparator = "__";
	m_scriptEngine = new MgScriptEngine(this);
	connect(this,SIGNAL(registerRequest(QObject*)),
			 this,SLOT(registerObject(QObject*)),Qt::QueuedConnection);
	registerWrapper();
	initEventsStrings();

}

MgApplicationMonitor::~MgApplicationMonitor(){}


void MgApplicationMonitor::registerWrapper()
{
	MgTestFunctionsWrapper * wrapper = new MgTestFunctionsWrapper(this);
	wrapper->setObjectName("testFunctionsWrapper");
	m_scriptEngine->registerObject(wrapper);
	m_scriptEngine->registerFunction("SLEEP()","testFunctionsWrapper.sleep(arguments[0])");
	m_scriptEngine->registerFunction("WAIT()","testFunctionsWrapper.wait(arguments[0])");
	m_scriptEngine->registerFunction("VERIFY()","testFunctionsWrapper.verify(arguments[0],arguments[1])");

	m_scriptEngine->registerFunction("RIGHT_CLICK()","testFunctionsWrapper.mouseRightClick(arguments[0])");
	m_scriptEngine->registerFunction("LEFT_CLICK()","testFunctionsWrapper.mouseLeftClick(arguments[0])");
	m_scriptEngine->registerFunction("DOUBLE_CLICK()","testFunctionsWrapper.mouseDoubleClick(arguments[0])");
}



MgScriptEngine * MgApplicationMonitor::scriptEngine()const
{
	return m_scriptEngine;
}

void MgApplicationMonitor::setRootObject(QObject * root)
{
	m_root = root;
	clear();
	registerObject(root);
}

void MgApplicationMonitor::clear()
{
	//TODO
}


void MgApplicationMonitor::registerObject(QObject* obj)
{

	if(m_registedObjects.contains(obj))
		return;
	if(obj->objectName().startsWith("qt"))
	{
		QString message("Skipping Qt internal object : ");
		message+= obj->metaObject()->className();
		message+= " "+obj->objectName();
		informationMessage(message);
		return;
	}

	if(	obj->objectName().isEmpty())
	{

		QString message("Can not register object of type ");
		message += obj->metaObject()->className();
		if(obj->parent())
		{
			message += " child of ";
			message += obj->parent()->property("hierarchical_name").toString();
			message += " of type ";
			message += obj->parent()->metaObject()->className();
		}
		warningMessage(message);
		return;
	}
	if(obj->parent())
		obj->setProperty("hierarchical_name",obj->parent()->property("hierarchical_name").toString()
				+m_objectNameSeparator+obj->objectName());
	else
		obj->setProperty("hierarchical_name",obj->objectName());


	m_scriptEngine->registerObject(obj);
	obj->installEventFilter(this);
	m_registedObjects.insert(obj);

	emit childAdded(obj->parent(),obj);

	foreach(QObject * child,obj->children())
		registerObject(child);

}

bool MgApplicationMonitor::eventFilter(QObject* obj,QEvent* e)
{
	if(e->type() == QEvent::ChildAdded)
	{
		QChildEvent * childEvent = static_cast<QChildEvent*>(e);
		emit registerRequest(childEvent->child());
		//childAdded signal will be emitted in registerObject
	}
	else if(e->type() == QEvent::ChildRemoved)
	{
		QChildEvent * childEvent = static_cast<QChildEvent*>(e);
		emit childRemoved(obj,childEvent->child());
	}

	monitorEvent(obj,e);
	return QObject::eventFilter(obj,e);
}

void MgApplicationMonitor::monitorEvent(QObject* obj,QEvent* e)
{

	QString event = m_eventsToString.contains(e->type()) ?
			m_eventsToString.value(e->type()) : "Unknown event";
	Q_EMIT eventMessage(
			obj->metaObject()->className(),
			obj->property("hierarchical_name").toString(),
			event
			);

//	switch (e->type())
//	{
//		case QEvent::MouseButtonPress:
//			Q_EMIT eventMessage("MouseButtonPress on "+
//					obj->property("hierarchical_name").toString());
//			break;
//		case QEvent::KeyPress:
//			Q_EMIT eventMessage("KeyPress on "+
//					obj->property("hierarchical_name").toString());
//			break;
//		default:
////			Q_EMIT eventMessage(QString("Event for %0, event code %1 ").arg(
////					obj->property("hierarchical_name").toString()).arg(e->type()));
//			break;
//	}
}

#define REGISTER_EVENT(event) m_eventsToString.insert(event,#event)

void MgApplicationMonitor::initEventsStrings()
{
	REGISTER_EVENT(QEvent::None);
	REGISTER_EVENT(QEvent::AccessibilityDescription);
	REGISTER_EVENT(QEvent::AccessibilityHelp);
	REGISTER_EVENT(QEvent::AccessibilityPrepare);
	REGISTER_EVENT(QEvent::ActionAdded);
	REGISTER_EVENT(QEvent::ActionChanged);
	REGISTER_EVENT(QEvent::ActionRemoved);
	REGISTER_EVENT(QEvent::ActivationChange);
	REGISTER_EVENT(QEvent::ApplicationActivate);
	REGISTER_EVENT(QEvent::ApplicationActivated);
	REGISTER_EVENT(QEvent::ApplicationDeactivate);
	REGISTER_EVENT(QEvent::ApplicationFontChange);
	REGISTER_EVENT(QEvent::ApplicationLayoutDirectionChange);
	REGISTER_EVENT(QEvent::ApplicationPaletteChange);
	REGISTER_EVENT(QEvent::ApplicationWindowIconChange);
	REGISTER_EVENT(QEvent::ChildAdded);
	REGISTER_EVENT(QEvent::ChildPolished);
	REGISTER_EVENT(QEvent::ChildRemoved);
	REGISTER_EVENT(QEvent::Clipboard);
	REGISTER_EVENT(QEvent::Close);
	REGISTER_EVENT(QEvent::CloseSoftwareInputPanel);
	REGISTER_EVENT(QEvent::ContentsRectChange);
	REGISTER_EVENT(QEvent::ContextMenu);
	REGISTER_EVENT(QEvent::CursorChange);
	REGISTER_EVENT(QEvent::DeferredDelete);
	REGISTER_EVENT(QEvent::DragEnter);
	REGISTER_EVENT(QEvent::DragLeave);
	REGISTER_EVENT(QEvent::DragMove);
	REGISTER_EVENT(QEvent::Drop);
	REGISTER_EVENT(QEvent::EnabledChange);
	REGISTER_EVENT(QEvent::Enter);

	REGISTER_EVENT(QEvent::EnterWhatsThisMode);
	REGISTER_EVENT(QEvent::FileOpen);
	REGISTER_EVENT(QEvent::FocusIn);
	REGISTER_EVENT(QEvent::FocusOut);
	REGISTER_EVENT(QEvent::FontChange);
	REGISTER_EVENT(QEvent::GrabKeyboard);
	REGISTER_EVENT(QEvent::GrabMouse);
	REGISTER_EVENT(QEvent::GraphicsSceneContextMenu);
	REGISTER_EVENT(QEvent::GraphicsSceneDragEnter);
	REGISTER_EVENT(QEvent::GraphicsSceneDragLeave);
	REGISTER_EVENT(QEvent::GraphicsSceneDragMove);
	REGISTER_EVENT(QEvent::GraphicsSceneDrop);
	REGISTER_EVENT(QEvent::GraphicsSceneHelp);
	REGISTER_EVENT(QEvent::GraphicsSceneHoverEnter);
	REGISTER_EVENT(QEvent::GraphicsSceneHoverLeave);
	REGISTER_EVENT(QEvent::GraphicsSceneHoverMove);
	REGISTER_EVENT(QEvent::GraphicsSceneMouseDoubleClick);
	REGISTER_EVENT(QEvent::GraphicsSceneMouseMove);
	REGISTER_EVENT(QEvent::GraphicsSceneMousePress);
	REGISTER_EVENT(QEvent::GraphicsSceneMouseRelease);
	REGISTER_EVENT(QEvent::GraphicsSceneMove);
	REGISTER_EVENT(QEvent::GraphicsSceneResize);
	REGISTER_EVENT(QEvent::GraphicsSceneWheel);
	REGISTER_EVENT(QEvent::Hide);
	REGISTER_EVENT(QEvent::HideToParent);
	REGISTER_EVENT(QEvent::HoverEnter);
	REGISTER_EVENT(QEvent::HoverLeave);
	REGISTER_EVENT(QEvent::HoverMove);
	REGISTER_EVENT(QEvent::IconDrag);
	REGISTER_EVENT(QEvent::IconTextChange);
	REGISTER_EVENT(QEvent::InputMethod);
	REGISTER_EVENT(QEvent::KeyPress);
	REGISTER_EVENT(QEvent::KeyRelease);
	REGISTER_EVENT(QEvent::LanguageChange);
	REGISTER_EVENT(QEvent::LayoutDirectionChange);
	REGISTER_EVENT(QEvent::LayoutRequest);
	REGISTER_EVENT(QEvent::Leave);
//	REGISTER_EVENT(QEvent::LeaveEditFocus);
	REGISTER_EVENT(QEvent::LeaveWhatsThisMode);
	REGISTER_EVENT(QEvent::LocaleChange);
	REGISTER_EVENT(QEvent::NonClientAreaMouseButtonDblClick);
	REGISTER_EVENT(QEvent::NonClientAreaMouseButtonPress);
	REGISTER_EVENT(QEvent::NonClientAreaMouseButtonRelease);
	REGISTER_EVENT(QEvent::NonClientAreaMouseMove);
	REGISTER_EVENT(QEvent::MacSizeChange);
	REGISTER_EVENT(QEvent::MenubarUpdated);
	REGISTER_EVENT(QEvent::MetaCall);
	REGISTER_EVENT(QEvent::ModifiedChange);
	REGISTER_EVENT(QEvent::MouseButtonDblClick);
	REGISTER_EVENT(QEvent::MouseButtonPress);
	REGISTER_EVENT(QEvent::MouseButtonRelease);
	REGISTER_EVENT(QEvent::MouseMove);
	REGISTER_EVENT(QEvent::MouseTrackingChange);
	REGISTER_EVENT(QEvent::Move);
	REGISTER_EVENT(QEvent::Paint);
	REGISTER_EVENT(QEvent::PaletteChange);
	REGISTER_EVENT(QEvent::ParentAboutToChange);
	REGISTER_EVENT(QEvent::ParentChange);
	REGISTER_EVENT(QEvent::Polish);
	REGISTER_EVENT(QEvent::PolishRequest);
	REGISTER_EVENT(QEvent::QueryWhatsThis);
	REGISTER_EVENT(QEvent::RequestSoftwareInputPanel);
	REGISTER_EVENT(QEvent::Resize);
	REGISTER_EVENT(QEvent::Shortcut);
	REGISTER_EVENT(QEvent::ShortcutOverride);
	REGISTER_EVENT(QEvent::Show);
	REGISTER_EVENT(QEvent::ShowToParent);
	REGISTER_EVENT(QEvent::SockAct);
	REGISTER_EVENT(QEvent::StateMachineSignal);
	REGISTER_EVENT(QEvent::StateMachineWrapped);
	REGISTER_EVENT(QEvent::StatusTip);
	REGISTER_EVENT(QEvent::StyleChange);
	REGISTER_EVENT(QEvent::TabletMove);
	REGISTER_EVENT(QEvent::TabletPress);
	REGISTER_EVENT(QEvent::TabletRelease);
	REGISTER_EVENT(QEvent::OkRequest);
	REGISTER_EVENT(QEvent::TabletEnterProximity);
	REGISTER_EVENT(QEvent::TabletLeaveProximity);
	REGISTER_EVENT(QEvent::Timer);
	REGISTER_EVENT(QEvent::ToolBarChange);
	REGISTER_EVENT(QEvent::ToolTip);
	REGISTER_EVENT(QEvent::ToolTipChange);
	REGISTER_EVENT(QEvent::UngrabKeyboard);
	REGISTER_EVENT(QEvent::UngrabMouse);
	REGISTER_EVENT(QEvent::UpdateLater);
	REGISTER_EVENT(QEvent::UpdateRequest);
	REGISTER_EVENT(QEvent::WhatsThis);
	REGISTER_EVENT(QEvent::WhatsThisClicked);
	REGISTER_EVENT(QEvent::Wheel);
	REGISTER_EVENT(QEvent::WinEventAct);
	REGISTER_EVENT(QEvent::WindowActivate);
	REGISTER_EVENT(QEvent::WindowBlocked);
	REGISTER_EVENT(QEvent::WindowDeactivate);
	REGISTER_EVENT(QEvent::WindowIconChange);
	REGISTER_EVENT(QEvent::WindowStateChange);
	REGISTER_EVENT(QEvent::WindowTitleChange);
	REGISTER_EVENT(QEvent::WindowUnblocked);
	REGISTER_EVENT(QEvent::ZOrderChange);
	REGISTER_EVENT(QEvent::KeyboardLayoutChange);
	REGISTER_EVENT(QEvent::DynamicPropertyChange);
	REGISTER_EVENT(QEvent::TouchBegin);
	REGISTER_EVENT(QEvent::TouchUpdate);
	REGISTER_EVENT(QEvent::TouchEnd);
	REGISTER_EVENT(QEvent::WinIdChange);
	REGISTER_EVENT(QEvent::Gesture);
	REGISTER_EVENT(QEvent::GestureOverride);
}
