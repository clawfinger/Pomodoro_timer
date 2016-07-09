#-------------------------------------------------
#
# Project created by QtCreator 2016-06-29T21:17:21
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LazyAssProject
TEMPLATE = app

win32 {
QMAKE_LFLAGS += -static-libgcc
}

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
RC_ICONS += tomato.ico

DISTFILES +=
