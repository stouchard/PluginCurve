#-------------------------------------------------
#
# Project created by QtCreator 2014-07-25T14:32:48
#
#-------------------------------------------------

TARGET = plugincurve
DESTDIR = ../build-plugincurve
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
CONFIG += staticlib c++11 warn_on
QMAKE_CXXFLAGS += -std=c++11
SOURCES += plugincurve.cpp\
            plugincurvemodel.cpp \
            plugincurvepresenter.cpp \
            plugincurveview.cpp \
            plugincurvepoint.cpp \
            plugincurvesection.cpp \
            plugincurvesectionbezier.cpp \
            plugincurvesectionlinear.cpp \
            plugincurvemap.cpp \
            plugincurvegrid.cpp \
    plugincurvemenupoint.cpp \
    plugincurvemenusection.cpp \
    plugincurvezoomer.cpp

HEADERS += plugincurve.hpp\
           plugincurve2_global.hpp\
           plugincurvemodel.hpp \
           plugincurvepresenter.hpp \
           plugincurveview.hpp \
           plugincurvepoint.hpp \
           plugincurvesection.hpp \
           plugincurvesectionbezier.hpp \
           plugincurvesectionlinear.hpp \
           plugincurvemap.hpp \
           plugincurvegrid.hpp \
    plugincurvemenupoint.h \
    plugincurvemenusection.hpp \
    plugincurvezoomer.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
