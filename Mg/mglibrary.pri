DEBUG_SUFFIX   = .debug
RELEASE_SUFFIX =

PROJECT_CONFIG = debug

CONFIG -= debug release debug_and_release
CONFIG += $${PROJECT_CONFIG}
DEFINES += MG_LIBRARY

include (version.pri)
include (mgexternallibs.pri)

CONFIG(debug) {
        SUFFIX_STR = $${DEBUG_SUFFIX}
        DEFINES += MG_DEBUG_MSG
    }
    else {
        SUFFIX_STR = $${RELEASE_SUFFIX}
    }
     
MGLIBRARY_DIR = $$PWD 
MGLIBRARY_LIBS_DIR = $$MGLIBRARY_DIR/bin/lib
MGLIBRARY_BIN_DIR = $$MGLIBRARY_DIR/bin/bin
MGLIBRARY_PLUGINS_DIR = $$MGLIBRARY_DIR/bin/plugins
MGLIBRARY_TEMP_DIR = $$MGLIBRARY_DIR/.tmp_objects

TARGET = $${TARGET}$$SUFFIX_STR

QMAKE_RPATHDIR += $${MGLIBRARY_LIBS_DIR}

contains (TEMPLATE , lib){
	DESTDIR = $$MGLIBRARY_LIBS_DIR
	OBJECTS_DIR = $$MGLIBRARY_TEMP_DIR/$${TARGET}/obj
	MOC_DIR = $$MGLIBRARY_TEMP_DIR/$${TARGET}/moc
	RCC_DIR = $$MGLIBRARY_TEMP_DIR/$${TARGET}/rcc

}

contains( MG , mg_core ){
	INCLUDEPATH += $$MGLIBRARY_DIR/include
	INCLUDEPATH += $$MGLIBRARY_DIR/include/MgCore
	LIBS += -L$$MGLIBRARY_LIBS_DIR  -lMgCore$${SUFFIX_STR} 
}

contains( MG, mg_script ){
	INCLUDEPATH += $$MGLIBRARY_DIR/include
	INCLUDEPATH += $$MGLIBRARY_DIR/include/MgScript
	LIBS += -L$$MGLIBRARY_LIBS_DIR  -lMgScript$${SUFFIX_STR} 
	QT += script
}

contains( MG, mg_gui ){
	INCLUDEPATH += $$MGLIBRARY_DIR/include
	INCLUDEPATH += $$MGLIBRARY_DIR/include/MgGui
	LIBS += -L$$MGLIBRARY_LIBS_DIR  -lMgGui$${SUFFIX_STR} 
	LIBS += -L$$QT_PROPERTY_EDITOR_EDITOR_LIB_DIR -lQtSolutions_PropertyBrowser-head
	QMAKE_RPATHDIR += $${QT_PROPERTY_EDITOR_EDITOR_LIB_DIR}
}

contains( MG, mg_multimedia ){
	INCLUDEPATH += $$MGLIBRARY_DIR/include
	INCLUDEPATH += $$MGLIBRARY_DIR/include/MgMultimedia
	LIBS += -L$$MGLIBRARY_LIBS_DIR  -lMgMultimedia$${SUFFIX_STR} 
	QT += phonon
}

contains( MG, mg_3d ){
	QT += opengl
	INCLUDEPATH += $$MGLIBRARY_DIR/include
	INCLUDEPATH += $$MGLIBRARY_DIR/include/Mg3D
	LIBS += -L$$MGLIBRARY_LIBS_DIR  -lMg3D$${SUFFIX_STR} 
	QMAKE_RPATHDIR += $${QT3D_LIB_DIR}
	
	INCLUDEPATH += $$QT3D_INCLUDE_DIR
	LIBS += -L$${QT3D_LIB_DIR} -lQt3D
}

contains( MG, mg_test ){
	INCLUDEPATH += $$MGLIBRARY_DIR/include
	INCLUDEPATH += $$MGLIBRARY_DIR/include/MgTest
	LIBS += -L$$MGLIBRARY_LIBS_DIR  -lMgTest$${SUFFIX_STR} 
	CONFIG += qtestlib
}

contains( MG, mg_qtopencl ){
	INCLUDEPATH += $$QT_OPENCL_INCLUDE_DIR
	LIBS += -L$$QT_OPENCL_LIB_DIR  -lQtOpenCL
	QMAKE_RPATHDIR += $${QT_OPENCL_LIB_DIR}
}

