TEMPLATE = app
TARGET = MgIncludesBuilder
QT += core
include (../../mglibrary.pri)
DESTDIR = $$MGLIBRARY_BIN_DIR
OBJECTS_DIR = $$MGLIBRARY_TEMP_DIR/tools/includesbuilder/obj
MOC_DIR = $$MGLIBRARY_TEMP_DIR/tools/includesbuilder/moc

SOURCES = main.cpp
