CC=gcc

all:
	mkdir -p bin
	$(CC) src/*.c -o bin/engine -Wall -lSDL2
dist:
	echo "TODO: statically compile sdl into binary and build for all platforms"
