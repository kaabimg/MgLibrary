TEMPLATE = lib
TARGET = Mg3D
QT += opengl
MG += mg_core
include (../../mglibrary.pri)
HEADERS = shaders/filters/mgcolorfiltershader.h \
    scene/mgcameraanimation.h \
    shaders/bumpmapping/mgbumpmappingshader.h \
    shaders/antialiasing/mgantialiasingshader.h \
    shaders/fbodisplay/mgfbodisplayshader.h \
    shaders/fbodisplay/mgtexturedrawshader.h \
    shaders/blend/mgblendshader.h \
    shaders/filters/mgalphafilter.h \
    shaders/blur/mgvblurshader.h \
    shaders/blur/mghblurshader.h \
    shaders/test/mgtestshader.h \
    shaders/tubeglow/mgtubeglowshader.h \
    shaders/texture/mgtextureshader.h \
    shaders/hdr/mghdrshader.h \
    utils/mg3dhelpers.h \
    shaders/mgabstractshader.h \
    utils/mgparametriccurves.h \
    scenebuilder/mgparametericlinebuilder.h \
    scenebuilder/mgabstractnodebuilder.h \
    coordinates/mg3dreference.h \
    scene/mg3dscene.h \
    scenebuilder/mggeometriesdata.h
SOURCES = shaders/filters/mgcolorfiltershader.cpp \
    scene/mgcameraanimation.cpp \
    shaders/bumpmapping/mgbumpmappingshader.cpp \
    shaders/antialiasing/mgantialiasingshader.cpp \
    shaders/fbodisplay/mgfbodisplayshader.cpp \
    shaders/fbodisplay/mgtexturedrawshader.cpp \
    shaders/blend/mgblendshader.cpp \
    shaders/filters/mgalphafilter.cpp \
    shaders/blur/mgvblurshader.cpp \
    shaders/blur/mghblurshader.cpp \
    shaders/test/mgtestshader.cpp \
    shaders/tubeglow/mgtubeglowshader.cpp \
    shaders/texture/mgtextureshader.cpp \
    shaders/hdr/mghdrshader.cpp \
    shaders/mgabstractshader.cpp \
    utils/mgparametriccurves.cpp \
    scenebuilder/mgparametericlinebuilder.cpp \
    coordinates/mg3dreference.cpp \
    scene/mg3dscene.cpp \
    scenebuilder/mggeometriesdata.cpp
RESOURCES = shaders/mg_shaders_src.qrc
