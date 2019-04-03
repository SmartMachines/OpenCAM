#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T11:21:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XUXUCAM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



LIBS += -LE:\\XU_HSU\\201904\\XUXUCAM\\exLibs\\libdxflib.a
 #LIBS += -LE:\\X_HSU\\xuxu_CAM\\XUXUCAM\\exLibs\\debug\\dxflib.lib
 #LIBS += -LE:\\X_HSU\\xuxu_CAM\\XUXUCAM\\exLibs\\release\\dxflib.lib
INCLUDEPATH += E:\\XU_HSU\\201904\\XUXUCAM\\dxfSrc
INCLUDEPATH += C:\\boost_1_63_0
 INCLUDEPATH += E:\Program Files\vs2015\VC\include


SOURCES += main.cpp\
        camexpert.cpp \
    cam_newmaterial.cpp \
    cam_importmat.cpp \
    FileIO/cam_fileio.cpp \
    StringOperation/stringoperation.cpp \
    CamDxf/camdxf.cpp \
    CamDxf/qpointfwithparent.cpp \
    CamDxf/campart.cpp \
    CamDxf/camleads.cpp \
    CamDxf/camswap.cpp \
    CamDxf/camscene.cpp \
    cam_newprt.cpp \
    cam_importprt.cpp \
    CamUi/CamUiBasic/cam_workshop.cpp \
    CamUi/CamUiForms/cam_blockdlg.cpp \
    CamDxf/camdxf.cpp \
    CamDxf/camleads.cpp \
    CamDxf/campart.cpp \
    CamDxf/camscene.cpp \
    CamDxf/camswap.cpp \
    CamDxf/qpointfwithparent.cpp \
    dxfSrc/dl_dxf.cpp \
    dxfSrc/dl_writer_ascii.cpp \





HEADERS  += camexpert.h \
    cam_newmaterial.h \
    cam_importmat.h \
    FileIO/cam_fileio.h \
    StringOperation/stringoperation.h \
    CamDxf/camdxf.h \
    CamDxf/qpointfwithparent.h \
    CamDxf/campart.h \
    CamDxf/camleads.h \
    CamDxf/camswap.h \
    CamDxf/camscene.h \
    cam_newprt.h \
    cam_importprt.h \
    CamUi/CamUiBasic/cam_workshop.h \
    CamUi/CamUiForms/cam_blockdlg.h \
    CamDxf/camdxf.h \
    CamDxf/camleads.h \
    CamDxf/campart.h \
    CamDxf/camscene.h \
    CamDxf/camswap.h \
    CamDxf/qpointfwithparent.h \
    dxfSrc/dl_attributes.h \
    dxfSrc/dl_codes.h \
    dxfSrc/dl_creationadapter.h \
    dxfSrc/dl_creationinterface.h \
    dxfSrc/dl_dxf.h \
    dxfSrc/dl_entities.h \
    dxfSrc/dl_exception.h \
    dxfSrc/dl_extrusion.h \
    dxfSrc/dl_writer.h \
    dxfSrc/dl_writer_ascii.h \







FORMS    += camexpert.ui \
    cam_newmaterial.ui \
    cam_importmat.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    Scripts/Edits/App/App.js \
    Scripts/Files/File.js

SUBDIRS += \
    CamThirdParty/muparser/muparser.pro
