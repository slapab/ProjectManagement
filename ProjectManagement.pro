#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T10:45:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ProjectItem.cpp \
    TimeInterval.cpp \
    TaskItem.cpp \
    SQLiteAccess.cpp \
    UIMainWindow.cpp \
    TreeModel.cpp \
    TreeItemRoot.cpp \
    ItemsHierarchyBuilder.cpp \
    TreeItem.cpp \
    ItemInfoLayoutManager.cpp

HEADERS  += mainwindow.h \
    ProjectItem.h \
    ProjectItemInterface.h \
    TimeIntervalInterface.h \
    TimeInterval.h \
    TaskItemInterface.h \
    TaskItem.h \
    DataStorageAccessInterface.h \
    SQLiteAccess.h \
    UIMainWindow.h \
    TreeItemInterface.h \
    TreeModel.h \
    TreeItemRoot.h \
    ItemsHierarchyBuilder.h \
    ItemInterface.h \
    TreeItem.h \
    ItemInfoLayoutManager.h

FORMS    += mainwindow.ui

CONFIG += c++14
