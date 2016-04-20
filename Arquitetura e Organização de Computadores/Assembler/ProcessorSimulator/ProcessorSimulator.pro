#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T23:34:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcessorSimulator
TEMPLATE = app
CONFIG += c++11
CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    processor.cpp \
    instruction.cpp \
    program.cpp

HEADERS  += mainwindow.h \
    processor.h \
    instruction.h \
    program.h

FORMS    += mainwindow.ui
