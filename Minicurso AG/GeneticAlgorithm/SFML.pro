TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp

INCLUDEPATH += "$$PWD/LabSFML/include"
LIBS += -L"$$PWD/LabSFML/lib" -lsfml-graphics -lsfml-window -lsfml-system
