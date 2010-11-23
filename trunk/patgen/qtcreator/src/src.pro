TEMPLATE = app
CONFIG = console nogui debug static
win32 {
    INCLUDEPATH += c:/programs/boost/include ../../src ../../src/common ../../src/trace/evcd/parser ../../src/algorithm
    #LIBS = -Lc:/programs/boost/lib -lboost_program_options -lboost_regex -lboost_filesystem -lboost_system
    LIBS = c:/programs/boost/lib/libboost_program_options-mgw34.lib c:/programs/boost/lib/libboost_regex-mgw34-mt-s.lib c:/programs/boost/lib/libboost_filesystem-mgw34.lib c:/programs/boost/lib/libboost_system-mgw34.lib c:/programs/boost/lib/libboost_iostreams-mgw34.lib c:/mingw/lib/libstdc++.a
}
unix {
    INCLUDEPATH += /usr/include ../../src ../../src/common ../../src/trace/evcd/parser ../../src/algorithm
    LIBS = -L/usr/lib -L/usr/local/lib -lboost_program_options -lboost_regex -lboost_filesystem -lboost_system -lboost_iostreams -lglog -lmuparser
}

TARGET = patgen
HEADERS += ../../src/common/common.h \
           ../../src/common/cycleData.h \
            ../../src/common/eventData.h \
            ../../src/common/waveformTable.h \
            ../../src/trace/traceWriter.h \
            ../../src/trace/evcd/evcdReader.h \
            ../../src/trace/evcd/evcdWriter.h \
            ../../src/trace/verilog/verilogWriter.h \
            ../../src/algorithm/cyclize.h \
            ../../src/algorithm/transform.h \
            ../../src/pattern/patternWriter.h \
            ../../src/pattern/stil/stilWriter.h \
            ../../src/pattern/patternReader.h \
            ../../src/pattern/stil/stilReader.h \
    ../../src/pattern/stil/parser/Expr.h \
    ../../src/pattern/stil/parser/Parser.h \
    ../../src/pattern/stil/parser/Scanner.h \
    ../../src/pattern/stil/parser/Stil.h \
    ../../src/pattern/stil/parser/Singleton.h

SOURCES +=  ../../src/common/common.cpp  \
            ../../src/common/cycleData.cpp  \
            ../../src/common/eventData.cpp  \
            ../../src/common/waveformTable.cpp  \
            ../../src/trace/traceWriter.cpp  \
            ../../src/trace/evcd/evcdReader.cpp  \
            ../../src/trace/evcd/evcdWriter.cpp  \
            ../../src/trace/evcd/parser/evcd_yacc.cpp  \
            ../../src/trace/evcd/parser/evcd_lex.cpp  \
            ../../src/trace/evcd/parser/driver.cpp  \
            ../../src/trace/verilog/verilogWriter.cpp  \
            ../../src/algorithm/cyclize.cpp \
            ../../src/algorithm/transform.cpp \
            ../../src/pattern/patternWriter.cpp \
            ../../src/pattern/stil/stilWriter.cpp \
            ../../src/pattern/patternReader.cpp \
            ../../src/pattern/stil/stilReader.cpp \
            ../../src/patgen.cpp \
    ../../src/pattern/stil/parser/Stil.cpp \
    ../../src/pattern/stil/parser/Scanner.cpp \
    ../../src/pattern/stil/parser/Parser.cpp \
    ../../src/pattern/stil/parser/Expr.cpp
