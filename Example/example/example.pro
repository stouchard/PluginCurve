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
            ../../plugincurve/sources/plugincurvemodel.cpp \
            ../../plugincurve/sources/plugincurvepresenter.cpp \
            ../../plugincurve/sources/plugincurveview.cpp \
            ../../plugincurve/sources/plugincurvepoint.cpp \
            ../../plugincurve/sources/plugincurvesection.cpp \
            ../../plugincurve/sources/plugincurvesectionbezier.cpp \
            ../../plugincurve/sources/plugincurvesectionlinear.cpp \
            ../../plugincurve/sources/plugincurve.cpp

HEADERS  += mainwindow.hpp\
            ../../plugincurve/headers/plugincurvemodel.hpp \
            ../../plugincurve/headers/plugincurvepresenter.hpp \
            ../../plugincurve/headers/plugincurveview.hpp \
            ../../plugincurve/headers/plugincurvepoint.hpp \
            ../../plugincurve/headers/plugincurvesection.hpp \
            ../../plugincurve/headers/plugincurvesectionbezier.hpp \
            ../../plugincurve/headers/plugincurvesectionlinear.hpp \
            ../../plugincurve/headers/plugincurve.hpp

FORMS    += mainwindow.ui

INCLUDEPATH += ../../plugincurve/headers\


LIBS += -lxml2
