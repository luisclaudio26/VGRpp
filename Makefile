CC = g++
CFLAGS = -g -O0 -std=c++11
CLIBS = -lSDL -lm
EXEC = render

all: render.o parser.o rect.o vector2.o
	$(CC) $(CFLAGS) $(CLIBS) render.o parser.o rect.o vector2.o -o $(EXEC) main.cpp
	make clean

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