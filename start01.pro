#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T17:10:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = start01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    student.cpp \
    studentsdatalayer.cpp

HEADERS  += mainwindow.h \
    student.h \
    studentsdatalayer.h

FORMS    += mainwindow.ui
