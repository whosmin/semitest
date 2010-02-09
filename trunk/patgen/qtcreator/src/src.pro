TEMPLATE = app
CONFIG = console nogui debug static
INCLUDEPATH += c:/programs/boost/include ../../src ../../src/common ../../src/trace/evcd/parser ../../src/algorithm
LIBS = -L/usr/local/boost/lib -lboost_program_options -lboost_regex -lboost_filesystem -lboost_system
TARGET = patgen
HEADERS += ../../src/common/common.h
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
            ../../src/patgen.cpp

