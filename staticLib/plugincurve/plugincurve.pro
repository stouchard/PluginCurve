#-------------------------------------------------
#
# Project created by QtCreator 2014-07-25T14:32:48
#
#-------------------------------------------------

TARGET = plugincurve
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
CONFIG += staticlib c++11 warn_on
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
