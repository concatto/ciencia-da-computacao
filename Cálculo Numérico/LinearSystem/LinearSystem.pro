TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
SOURCES += main.cpp \
    linearsystem.cpp \
    interpolation.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    linearsystem.h \
    interpolation.h \
    definitions.h

