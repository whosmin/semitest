TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += c:/programs/boost/include

HEADERS += ../../Core/utility.h \
            ../../Core/array1d.h \
            ../../Core/array2d.h \
            ../../Core/reference.h \
            ../../Core/msvar.h \
            ../../Core/register.h \
            ../../Core/registerBank.h

SOURCES +=  ../../Core/utility.cpp \
            ../../Core/register.cpp \
            ../../Core/registerBank.cpp


