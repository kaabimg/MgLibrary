TEMPLATE = lib
TARGET = MgScript
QT += script
MG += mg_core
include (../../mglibrary.pri)
HEADERS = gui/mgcommandcompleter.h \
    gui/mgcommandline.h \
    core/mgscriptengineobjectinfo.h \
    gui/mgscriptengineobjectsinfowidget.h \
    core/mgmessagesscriptbindings.h \
    core/mgmathscriptbindings.h \
    gui/mgscriptwidget.h \
    gui/mgjavascriptsyntaxhighlighter.h \
    gui/mgjavascripteditor.h \
    core/mgscriptengine.h \
    gui/mgcommandprompt.h
SOURCES = gui/mgcommandcompleter.cpp \
    gui/mgcommandline.cpp \
    core/mgscriptengineobjectinfo.cpp \
    gui/mgscriptengineobjectsinfowidget.cpp \
    gui/mgscriptwidget.cpp \
    gui/mgjavascriptsyntaxhighlighter.cpp \
    gui/mgjavascripteditor.cpp \
    core/mgscriptengine.cpp \
    gui/mgcommandprompt.cpp
