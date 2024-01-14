#-------------------------------------------------
#
# Project created by QtCreator 2024-01-09T09:00:45
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGraphicsItem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LOCAL_BIN_DIR="../bin"
LOCAL_BUILD_DIR="../build"


SOURCES += \
        main.cpp \
        TestGraphicsItem.cpp \
    CStageTreeWidget.cpp \
    CStageGraphicsScene.cpp \
    CStageGraphicsItem.cpp \
    CStageGraphicsLineItem.cpp \
    CStageAddItem.cpp \
    CReadXmlFile.cpp \
    CWriteXmlFile.cpp

HEADERS += \
        TestGraphicsItem.h \
    CStageTreeWidget.h \
    CStageGraphicsScene.h \
    CStageGraphicsItem.h \
    CStageEnum.h \
    CStageGraphicsLineItem.h \
    CStageAddItem.h \
    CReadXmlFile.h \
    CWriteXmlFile.h

FORMS += \
    CStageAddItem.ui

UI_DIR = $$LOCAL_BUILD_DIR
RCC_DIR = $$LOCAL_BUILD_DIR
MOC_DIR = $$LOCAL_BUILD_DIR
OBJECTS_DIR = $$LOCAL_BUILD_DIR

DESTDIR = $$LOCAL_BIN_DIR

