#-------------------------------------------------
#
# Project created by QtCreator 2017-09-13T21:26:22
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = District13
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    core/game.cpp \
    core/district.cpp \
    core/sites/building.cpp \
    core/administration.cpp \
    core/sites/site.cpp \
    core/sites/house.cpp \
    gui/minimap.cpp \
    core/factor.cpp \
    gui/siteinfodialog.cpp \
    core/events/event.cpp \
    gui/eventlogger.cpp \
    core/sites/publicbuilding.cpp \
    gui/builddialog.cpp

HEADERS  += gui/mainwindow.h \
    core/game.h \
    core/district.h \
    core/sites/building.h \
    core/administration.h \
    core/sites/site.h \
    core/sites/house.h \
    gui/minimap.h \
    core/factor.h \
    gui/siteinfodialog.h \
    core/events/event.h \
    gui/eventlogger.h \
    core/sites/publicbuilding.h \
    gui/builddialog.h

RESOURCES += \
    res/resources.qrc
