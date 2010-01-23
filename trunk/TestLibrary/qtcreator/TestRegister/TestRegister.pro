TEMPLATE = app
CONFIG  += console debug

INCLUDEPATH += c:/programs/boost/include #../../Core

#DEPENDPATH += ../Core
LIBS = -L../Core -lCore -lgtest

SOURCES +=  ../../Test/testRegister.cpp
