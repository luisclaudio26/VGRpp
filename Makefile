CC = g++
CFLAGS = -g -O2 -std=c++11
CLIBS = -lm $(shell sdl-config --cflags --libs) -lSDL_image
EXEC = render

all: bin/render.o bin/parser.o bin/rect.o bin/vector2.o bin/vector3.o bin/RawElement.o bin/matrix3.o bin/triangle.o bin/parseElements.o bin/RawTriangle.o bin/RawSolid.o
	$(CC) $(CFLAGS) bin/render.o bin/parser.o bin/vector3.o bin/rect.o bin/vector2.o bin/RawElement.o bin/triangle.o bin/parseElements.o bin/matrix3.o bin/RawTriangle.o bin/RawSolid.o -o $(EXEC) main.cpp $(CLIBS)

bin/vector3.o: src/vector/vector3.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/vector3.o -c src/vector/vector3.cpp

bin/triangle.o: src/element/triangle.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/triangle.o -c src/element/triangle.cpp

bin/RawSolid.o: src/RawElement/RawSolid.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/RawSolid.o -c src/RawElement/RawSolid.cpp

bin/RawTriangle.o: src/RawElement/RawTriangle.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/RawTriangle.o -c src/RawElement/RawTriangle.cpp

bin/parseElements.o: src/parser/parseElements.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/parseElements.o -c src/parser/parseElements.cpp

bin/matrix3.o: src/vector/matrix3.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/matrix3.o -c src/vector/matrix3.cpp

bin/RawElement.o: src/RawElement/RawElement.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/RawElement.o -c src/RawElement/RawElement.cpp

bin/vector2.o: src/vector/vector2.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/vector2.o -c src/vector/vector2.cpp

bin/rect.o: src/vector/rect.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/rect.o -c src/vector/rect.cpp

bin/parser.o: src/parser/parser.cpp
	$(CC) $(CFLAGS) $(CLIBS) -o bin/parser.o -c src/parser/parser.cpp

bin/render.o: src/render.cpp
	$(CC) $(CFLAGS) -o bin/render.o -c src/render.cpp $(CLIBS)

clean:
	rm ./bin/*.o
	rm $(EXEC)
