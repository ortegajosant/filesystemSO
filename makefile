dependencies:
	mkdir bin

term:
	gcc -o bin/filesystem terminal.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

run:
	./bin/filesystem
