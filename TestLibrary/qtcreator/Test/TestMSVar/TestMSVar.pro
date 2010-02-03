TEMPLATE = app
CONFIG += console nogui debug
INCLUDEPATH += c:/programs/boost/include # ../../Core

# DEPENDPATH += ../Core
LIBS = -L../../Core -L../../Core/debug -lCore
LIBS += -Lc:/tjog/library/gtest-1.4.0/lib/.libs -lgtest
SOURCES += ../../../Test/testMSVar.cpp 
win32::# SOURCES += c:/tjog/library/gtest-1.4.0/src/gtest-all.cc
INCLUDEPATH += ../../../../../gtest-1.4.0/include
