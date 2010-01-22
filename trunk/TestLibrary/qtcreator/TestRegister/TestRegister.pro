TEMPLATE = app
CONFIG  += console

INCLUDEPATH += c:/programs/boost/include ../../Core

#DEPENDPATH += ../Core
LIBS = -L../Core -lCore

SOURCES +=  ../../Test/testRegister.cpp
