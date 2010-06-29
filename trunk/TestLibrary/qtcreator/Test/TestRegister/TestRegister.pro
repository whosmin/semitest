TEMPLATE = app
CONFIG += console \
    nogui debug
INCLUDEPATH += c:/programs/boost/include # ../../Core

# DEPENDPATH += ../Core
LIBS = -L../../Core \
    -L../../Core/debug \
    -lCore
LIBS += -Lc:/tjog/library/gtest-1.4.0/lib/.libs \
    -lgtest
SOURCES += ../../../Test/testRegister.cpp

win32:: SOURCES += c:/tjog/library/googletest/src/gtest-all.cc
win32:: INCLUDEPATH += c:/tjog/library/googletest/include c:/tjog/library/googletest
win32:: LIBS += -Lc:/tjog/library/googletest
