#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T10:47:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app
CONFIG += c++11 warn_on

SOURCES += main.cpp\
            mainwindow.cpp\


HEADERS  += mainwindow.hpp\

FORMS    += mainwindow.ui

INCLUDEPATH += ../../plugincurve2




LIBS += -lxml2\
        -L../../staticLib/build-plugincurve-Desktop_Qt_5_1_1_clang_64bit-Debug -lplugincurve
