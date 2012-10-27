TEMPLATE = lib
TARGET = MgTest
CONFIG += qtestlib
MG += mg_core \
    mg_gui \
    mg_script
    
include (../../mglibrary.pri)
HEADERS = gui/mgeventsview.h \
    core/mgtestfunctionswrapper.h \
    gui/mgqobjecttreeinfo.h \
    gui/mgqobjecttreeview.h \
    gui/mgqobjecttreemodel.h \
    core/mgapplicationmonitor.h \
    core/mgqobjectinfo.h
SOURCES = gui/mgeventsview.cpp \
    core/mgtestfunctionswrapper.cpp \
    gui/mgqobjecttreeinfo.cpp \
    gui/mgqobjecttreeview.cpp \
    gui/mgqobjecttreemodel.cpp \
    core/mgapplicationmonitor.cpp
