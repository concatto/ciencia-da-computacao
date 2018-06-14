TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -O3
INCLUDEPATH += "$$PWD/LabSFML/include"
LIBS += -L"$$PWD/LabSFML/lib" -lsfml-graphics -lsfml-window -lsfml-system


SOURCES += \
        main.cpp

HEADERS += \
    algoritmo_genetico.h \
    util.h \
    circulos.h
