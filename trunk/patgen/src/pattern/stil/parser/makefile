SYSNAME := $(shell uname -s | sed 's/_NT-5.1//')
MACHINE := $(shell uname -m )
GCC_VER := $(shell gcc --version | head -1 | sed 's/gcc (GCC) \([0-9].[0-9]\).*/\1/' | sed 's/[.]//')


ifeq "$(SYSNAME)" "Linux"
COCO = ~/bin/Coco
endif
ifeq "$(SYSNAME)" "MINGW32"
COCO = /c/programs/Coco/Coco
endif



all: stilreader

stilreader: Parser.o Scanner.o Stil.o stilreader.o
	g++ -o stilreader $^

stilreader.o: stilreader.cpp
	g++ -c $<

Stil.o: Stil.cpp
	g++ -c $<

Scanner.o: Scanner.cpp
	g++ -c $<
Parser.o: Parser.cpp
	g++ -c $<

Parser.cpp: stil.atg
	$(COCO) stil.atg
	#sed -i 's/(L\"/("/g' Scanner.cpp
	sed 's/(L\"/("/g' Scanner.cpp > temp.cpp
	mv temp.cpp Scanner.cpp
	#sed -i 's/wchar_t/char/g' Scanner.cpp
	sed 's/wchar_t/char/g' Scanner.cpp > temp.cpp
	mv temp.cpp Scanner.cpp
	#sed -i 's/%ls/%s/g' Parser.cpp
	sed 's/%ls/%s/g' Parser.cpp > temp.cpp
	mv temp.cpp Parser.cpp
	#sed -i 's/(L\"/("/g' Parser.cpp
	sed 's/(L\"/("/g' Parser.cpp > temp.cpp
	mv temp.cpp Parser.cpp

clean:
	rm stilreader
	rm *.o
	rm Parser.h Parser.cpp Scanner.h Scanner.cpp

.PHONY: clean

