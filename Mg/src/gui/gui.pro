TEMPLATE = lib
TARGET = MgGui
MG += mg_core
include (../../mglibrary.pri)
HEADERS = widgets/mgnavigationbar.h \
    textedit/mgbasetextedit.h \
    textedit/mgfindbar.h \
    textedit/mgfoldingextraarea.h \
    textedit/mglinesnumbersextraarea.h \
    properties/mgmultiobjectspropertieseditor.h \
    properties/mgobjectpropertiesmanager.h \
    properties/mgpropertywatcher.h \
    properties/mgobjectpropertieseditor.h \
    widgets/mgmessagesareawidget.h \
    widgets/dynamicwidget/mgsubwidget.h \
    widgets/dynamicwidget/mgdynamicwidget.h \
    task/mgtaskviewer.h \
    widgets/mgmultiwidgets.h \
    stylesheets/mgstylesheets.h \
    curves/mgcurvesplotter.h \
    curves/mgcurve.h \
    curves/mgcurvedata.h \
    global/mgguiparameters.h \
    widgets/mgoutputpanebar.h \
    widgets/mgoutputpanetogglebutton.h \
    widgets/mgfadeelement.h \
    widgets/mglistview.h \
    graphicsview/mgviewgridlayout.h \
    graphicsview/mggridgraphicsview.h \
    graphicsview/mgrectgraphicsobject.h \
    widgets/mgfadewidget.h \
    widgets/mgpushbutton.h \
    widgets/mgstylehelper.h \
    widgets/mgactionbar.h \
    widgets/mgtoolbutton.h \
    widgets/mgtabbar.h \
    widgets/mgtabwidget.h \
    widgets/mgutils.h \
    declarative/mgdeclarative.h \
    mainwindow/mgmainwindow.h
SOURCES = widgets/mgnavigationbar.cpp \
    textedit/mgbasetextedit.cpp \
    textedit/mgfindbar.cpp \
    textedit/mgfoldingextraarea.cpp \
    textedit/mglinesnumbersextraarea.cpp \
    properties/mgmultiobjectspropertieseditor.cpp \
    properties/mgobjectpropertiesmanager.cpp \
    properties/mgpropertywatcher.cpp \
    properties/mgobjectpropertieseditor.cpp \
    widgets/mgmessagesareawidget.cpp \
    widgets/dynamicwidget/mgsubwidget.cpp \
    widgets/dynamicwidget/mgdynamicwidget.cpp \
    task/mgtaskviewer.cpp \
    widgets/mgmultiwidgets.cpp \
    stylesheets/mgstylesheets.cpp \
    curves/mgcurvesplotter.cpp \
    global/mgguiparameters.cpp \
    widgets/mgoutputpanebar.cpp \
    widgets/mgoutputpanetogglebutton.cpp \
    widgets/mgfadeelement.cpp \
    widgets/mglistview.cpp \
    graphicsview/mgviewgridlayout.cpp \
    graphicsview/mggridgraphicsview.cpp \
    graphicsview/mgrectgraphicsobject.cpp \
    widgets/mgfadewidget.cpp \
    widgets/mgpushbutton.cpp \
    widgets/mgstylehelper.cpp \
    widgets/mgactionbar.cpp \
    widgets/mgtoolbutton.cpp \
    widgets/mgtabbar.cpp \
    widgets/mgtabwidget.cpp \
    mainwindow/mgmainwindow.cpp
INCLUDEPATH += $$QT_PROPERTY_EDITOR_EDITOR_INCLUDE_DIR
LIBS += -L$$QT_PROPERTY_EDITOR_EDITOR_LIB_DIR \
    -lQtSolutions_PropertyBrowser-head
