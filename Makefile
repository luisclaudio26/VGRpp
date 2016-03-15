CC = g++
CFLAGS = -g -O0 -std=c++11
CLIBS = -lSDL -lm
EXEC = render

all: render.o
	$(CC) $(CFLAGS) $(CLIBS) render.o -o $(EXEC) main.cpp
	make clean

render.o: src/render.cpp
	$(CC) $(CFLAGS) $(CLIBS) -c src/render.cpp

clean:
	rm *.o