#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T10:45:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ProjectItem.cpp \
    ItemsFactory.cpp

HEADERS  += mainwindow.h \
    ItemsFactoryInterface.h \
    ProjectItem.h \
    ProjectItemInterface.h \
    ItemsFactory.h

FORMS    += mainwindow.ui

CONFIG += c++14
