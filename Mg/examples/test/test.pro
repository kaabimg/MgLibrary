TEMPLATE = app
TARGET = MgTestExample
QT += core \
    gui \
    script
MG += mg_core \
    mg_gui \
    mg_script \
    mg_test
include (../../mglibrary.pri)
DESTDIR = $$MGLIBRARY_BIN_DIR
OBJECTS_DIR = $$MGLIBRARY_TEMP_DIR/examples/test/obj
MOC_DIR = $$MGLIBRARY_TEMP_DIR/examples/test/moc
SOURCES = guitestclass.cpp \
    main.cpp
HEADERS = guitestclass.h
