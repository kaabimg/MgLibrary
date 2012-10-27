TEMPLATE = lib
TARGET = MgMultimedia
QT += declarative
MG += mg_core
QT += gui \
    phonon
include (../../mglibrary.pri)
HEADERS = videoplayer/mgvideocontroller.h \
    videoplayer/mgvideoplayer.h
SOURCES = videoplayer/mgvideocontroller.cpp \
    videoplayer/mgvideoplayer.cpp
