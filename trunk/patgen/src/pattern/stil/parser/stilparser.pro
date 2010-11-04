TEMPLATE = app

CONFIG = console nogui debug static

TARGET = stilreader
LIBS = -lmuparser

HEADERS += Stil.h

SOURCES += Stil.cpp \
           Scanner.cpp \
           Parser.cpp \
           Expr.cpp \
           stilreader.cpp
