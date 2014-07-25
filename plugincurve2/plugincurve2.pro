#-------------------------------------------------
#
# Project created by QtCreator 2014-07-24T16:05:33
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11 warn_on
TARGET = plugincurve2
TEMPLATE = lib
DEFINES += PLUGINCURVE2_LIBRARY

SOURCES += plugincurve.cpp\
            plugincurvemodel.cpp \
            plugincurvepresenter.cpp \
            plugincurveview.cpp \
            plugincurvepoint.cpp \
            plugincurvesection.cpp \
            plugincurvesectionbezier.cpp \
            plugincurvesectionlinear.cpp \

HEADERS += plugincurve.hpp\
           plugincurve2_global.hpp\
           plugincurvemodel.hpp \
           plugincurvepresenter.hpp \
           plugincurveview.hpp \
           plugincurvepoint.hpp \
           plugincurvesection.hpp \
           plugincurvesectionbezier.hpp \
           plugincurvesectionlinear.hpp \

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

LIBS += -lxml2
