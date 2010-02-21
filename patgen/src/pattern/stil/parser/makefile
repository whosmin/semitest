COCO = /c/programs/Coco/Coco

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

clean:
	rm stilreader
	rm *.o
	rm Parser.h Parser.cpp Scanner.h Scanner.cpp

.PHONY: clean

