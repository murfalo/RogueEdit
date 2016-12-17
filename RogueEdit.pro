#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T19:31:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RogueEdit
TEMPLATE = app


SOURCES += src/sources/main.cpp\
        src/sources/mainwindow.cpp \
    src/sources/editor.cpp

HEADERS  += src/headers/mainwindow.h \
    src/headers/editor.h \
    src/headers/items.h \
    src/headers/strings.h

FORMS    += src/forms/mainwindow.ui

RESOURCES += \
    src/resources/images/images.qrc
