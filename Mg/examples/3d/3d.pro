TEMPLATE = app
TARGET = Mg3DExample
QT += core \
    gui
MG += mg_core \
    mg_gui \
    mg_3d
include (../../mglibrary.pri)
DESTDIR = $$MGLIBRARY_BIN_DIR
OBJECTS_DIR = $$MGLIBRARY_TEMP_DIR/examples/3d/obj
MOC_DIR = $$MGLIBRARY_TEMP_DIR/examples/3d/moc
SOURCES = src/cubeview.cpp \
    main.cpp
HEADERS = src/cubeview.h
