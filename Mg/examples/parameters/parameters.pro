TEMPLATE = app
TARGET = MgParametersEditorExample
QT += core \
    gui
MG += mg_core \
    mg_gui
include (../../mglibrary.pri)
DESTDIR = $$MGLIBRARY_BIN_DIR
OBJECTS_DIR = $$MGLIBRARY_TEMP_DIR/examples/parameters/obj
MOC_DIR = $$MGLIBRARY_TEMP_DIR/examples/parameters/moc
SOURCES = main.cpp
HEADERS = testobject.h
