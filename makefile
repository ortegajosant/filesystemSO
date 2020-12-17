dependencies:
	mkdir bin

term:
	gcc -o bin/filesystem terminal.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

run:
	./bin/filesystem

disk:
	gcc -o bin/disk disk.c

run-disk:
	./bin/disk

filesystem:
	gcc -o bin/filesystem filesystem.c

run-filesystem:
	./bin/filesystem