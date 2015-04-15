#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T11:46:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GLHeaderGen

DESTDIR = ../../bin

CONFIG   += console
CONFIG   -= app_bundle

CONFIG(debug, debug|release){
    DEFINES += DEBUG
    #message(debug $$DESTDIR)
 }
TEMPLATE = app

SOURCES += main.cpp \
    glheadergen.cpp

HEADERS += \
    glheadergen.h \
    gltree.h \
    orphanenums.h \
    glheadergen_types.h \
    utils.h


headers.files += ../../include/function.h \
                 ../../include/glbinder.h \
                 ../../include/types.h

headers.path += $$OUT_PWD/../../include

INSTALLS += headers

include(../../paths.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$TinyXML2_lib_path_release/ -l$$TinyXML_lib_name_release
else:win32:CONFIG(debug, debug|release): LIBS += -L$$TinyXML2_lib_path_debug/ -l$$TinyXML_lib_name_debug

INCLUDEPATH += $$TinyXML_include_path
DEPENDPATH += $$TinyXML_include_path

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$TinyXML2_lib_path_release/$$join(TinyXML_lib_name_release,,,.a)
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$TinyXML2_lib_path_debug/$$join(TinyXML_lib_name_debug,,,.a)
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$TinyXML2_lib_path_release/$$join(TinyXML_lib_name_release,,,.lib)
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$TinyXML2_lib_path_debug/$$join(TinyXML_lib_name_debug,,,.lib)
