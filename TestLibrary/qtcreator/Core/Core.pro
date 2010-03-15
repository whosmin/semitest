TEMPLATE = lib
CONFIG += staticlib \
    debug
INCLUDEPATH += c:/programs/boost/include
HEADERS += ../../Core/utility.h \
    ../../Core/array1d.h \
    ../../Core/array2d.h \
    ../../Core/reference.h \
    ../../Core/msvar.h \
    ../../Core/register.h \
    ../../Core/registerMap.h \
    ../../Core/lut.h \
    ../../Core/curve.h
SOURCES += ../../Core/utility.cpp \
    ../../Core/register.cpp \
    ../../Core/registerMap.cpp \
    ../../Core/lut.cpp \
    ../../Core/curve.cpp

