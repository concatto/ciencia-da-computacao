TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
        main.cpp

HEADERS += \
    algoritmo_genetico.h \
    util.h \
    circulos.h
