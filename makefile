all: exec

struct.o: struct.c struct.h
	gcc -c struct.c -o struct.o

main.o: main.c struct.h
	gcc -c main.c -o main.o

exec: main.o struct.o
	gcc main.o struct.o -o exec