#-------------------------------------------------
#
# Project created by QtCreator 2018-09-27T17:11:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SimpleGPIO.cpp

HEADERS  += mainwindow.h \
    SimpleGPIO.h

FORMS    += mainwindow.ui
