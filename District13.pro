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
    core/sites/house.cpp

HEADERS  += gui/mainwindow.h \
    core/game.h \
    core/district.h \
    core/sites/building.h \
    core/administration.h \
    core/sites/site.h \
    core/sites/house.h

