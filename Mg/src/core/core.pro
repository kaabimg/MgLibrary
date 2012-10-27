TEMPLATE = lib
TARGET = MgCore
include (../../mglibrary.pri)
QT -= gui
QT += script
HEADERS = thread/mglockableobject.h \
    messages/mgmessagesemitter.h \
    thread/mgthread.h \
    files/mgfilemanager.h \
    application/mgenvironmentvariablesmanager.h \
    application/mgapplicationargumentsmanager.h \
    tools/mgobjectsset.h \
    mgglobalmacros.h \
    genericplugins/mgclassescollection.h \
    genericplugins/mgplugin.h \
    genericplugins/mgpluginsloader.h \
    log/mgfilelogger.h \
    log/mgabstractlogger.h \
    log/mgapplicationlogmanager.h \
    thread/mgtasksmanager.h \
    thread/mgtask.h
SOURCES = messages/mgmessagesemitter.cpp \
    thread/mgthread.cpp \
    files/mgfilemanager.cpp \
    application/mgenvironmentvariablesmanager.cpp \
    application/mgapplicationargumentsmanager.cpp \
    genericplugins/mgpluginsloader.cpp \
    log/mgfilelogger.cpp \
    log/mgapplicationlogmanager.cpp \
    thread/mgtasksmanager.cpp \
    thread/mgtask.cpp
