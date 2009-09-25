CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		PatGen.o

LIBS =

TARGET =	PatGen

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
