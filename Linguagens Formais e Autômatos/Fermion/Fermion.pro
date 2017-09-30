TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    grammar/Constants.cpp \
    grammar/Lexico.cpp \
    grammar/Semantico.cpp \
    grammar/Sintatico.cpp

HEADERS += \
    grammar/AnalysisError.h \
    grammar/Constants.h \
    grammar/LexicalError.h \
    grammar/Lexico.h \
    grammar/SemanticError.h \
    grammar/Semantico.h \
    grammar/Sintatico.h \
    grammar/SyntaticError.h \
    grammar/Token.h
