#-------------------------------------------------
#
# Project created by QtCreator 2020-11-16T19:32:59
#
#-------------------------------------------------

QT       += core gui
QT       += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 4X_historical_game
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


SOURCES += \
        main.cpp \
    gui/userinterfacemanager.cpp \
    gui/map/mapview.cpp \
    gui/map/maptile.cpp \
    gui/map/confreader/tilebonus.cpp \
    gui/map/confreader/mapreader.cpp \
    gui/map/confreader/tileconf.cpp \
    gui/map/confreader/tileconfreader.cpp \
    unit/unit.cpp \
    city/city.cpp \
    building/building.cpp \
    engine/gamemanager.cpp \
    engine/playermanager.cpp \
    gui/map/mapmanager.cpp \
    unit/unitreader.cpp \
    unit/unitaction.cpp \
    conf_management/conffilereader.cpp

HEADERS += \
    gui/userinterfacemanager.h \
    gui/map/mapview.h \
    gui/map/maptile.h \
    gui/map/confreader/tilebonus.h \
    gui/map/confreader/mapreader.h \
    gui/map/confreader/tileconf.h \
    gui/map/confreader/tileconfreader.h \
    unit/unit.h \
    city/city.h \
    building/building.h \
    engine/gamemanager.h \
    engine/playermanager.h \
    gui/map/mapmanager.h \
    unit/unitreader.h \
    unit/unitaction.h \
    conf_management/conffilereader.h

FORMS += \
    gui/userinterfacemanager.ui

RESOURCES += \
    ../res/resources.qrc
