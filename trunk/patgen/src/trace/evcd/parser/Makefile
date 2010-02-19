SYSNAME := $(shell uname -s | sed 's/_NT-5.1//')
MACHINE := $(shell uname -m )
GCC_VER := $(shell gcc --version | head -1 | sed 's/gcc (GCC) \([0-9].[0-9]\).*/\1/')

CC     = gcc
CPP    = g++
CFLAGS = -I.

#LEX   = /home/tjog/local/bin/flex
LEX    = flex
YACC   = bison
ASTYLE = astyle --style=ansi --indent=spaces=4 --convert-tabs \
		 --indent-classes --indent-cases --indent-namespaces --pad=oper

#OPT    = -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -Wall
OPT    = -O2 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -Wall

INCLUDES = -I. -I../../../common -I/usr/local/boost/include
ifeq "$(SYSNAME)" "MINGW32"
	INCLUDES = -I. -I../../../common -Ic:/programs/boost/include
endif

OBJDIR = obj
OBJECTS = $(OBJDIR)/evcd_yacc.o $(OBJDIR)/evcd_lex.o $(OBJDIR)/driver.o

all: $(OBJDIR)/evcdparser

$(OBJDIR)/evcdparser: $(OBJDIR)/evcdparser.o $(OBJECTS)
	$(CPP) -I. $(OPT) -static -o $@ $^

$(OBJDIR)/evcdparser.o: evcdparser.cpp $(OBJECTS)
	$(CPP) $(INCLUDES) $(OPT) -static -o $@ -c $<
	
$(OBJDIR)/driver.o: driver.cpp
	$(CPP) $(INCLUDES) $(OPT) -static -o $@ -c $<
	
$(OBJDIR)/evcd_lex.o: evcd_lex.cpp
	$(CPP) $(INCLUDES) $(OPT) -static -o $@ -c $<
	
$(OBJDIR)/evcd_yacc.o: evcd_yacc.cpp
	$(CPP) $(INCLUDES) $(OPT) -static -o $@ -c $<
	
evcd_lex.cpp: evcd.l
	$(LEX) -d -o$@ $<
	$(ASTYLE) $@
#    $(LEX) -+ -o$@ $<

evcd_yacc.cpp: evcd.y
	$(YACC) -d -o $@ $<
	$(ASTYLE) $@


clean:
	rm -f $(OBJDIR)/*

.PHONY: clean all


