dependencies:
	mkdir bin
	gcc -o bin/disk disk.c
	./bin/disk

disk:
	./bin/disk

term:
	gcc -o bin/filesystem terminal.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -lm -ljson-c

view:
	gcc -o bin/view treeview.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -lm 
	./bin/view

run:
	./bin/filesystem

filesystem:
	gcc -o bin/filesystem filesystem.c -lm -ljson-c 

run-filesystem:
	./bin/filesystem