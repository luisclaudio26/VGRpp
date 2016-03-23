CC = g++
CFLAGS = -g -O0 -std=c++11
CLIBS = -lSDL -lm
EXEC = render

all: render.o parser.o rect.o vector2.o RawElement.o matrix3.o triangle.o parseElements.o RawTriangle.o RawSolid.o
	$(CC) $(CFLAGS) $(CLIBS) render.o parser.o rect.o vector2.o RawElement.o triangle.o parseElements.o matrix3.o RawTriangle.o RawSolid.o -o $(EXEC) main.cpp
	make clean

triangle.o: src/element/triangle.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/element/triangle.cpp

RawSolid.o: src/RawElement/RawSolid.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/RawElement/RawSolid.cpp

RawTriangle.o: src/RawElement/RawTriangle.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/RawElement/RawTriangle.cpp

parseElements.o: src/parser/parseElements.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/parser/parseElements.cpp

matrix3.o: src/vector/matrix3.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/vector/matrix3.cpp

RawElement.o: src/RawElement/RawElement.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/RawElement/RawElement.cpp

vector2.o: src/vector/vector2.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/vector/vector2.cpp

rect.o: src/vector/rect.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/vector/rect.cpp

parser.o: src/parser/parser.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/parser/parser.cpp

render.o: src/render.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/render.cpp

clean:
	rm *.o