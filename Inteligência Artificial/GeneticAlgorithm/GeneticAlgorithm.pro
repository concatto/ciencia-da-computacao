TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -O3

SOURCES += \
        main.cpp

HEADERS += \
    algoritmo_genetico.h \
    util.h \
    leitor_tsp.h
