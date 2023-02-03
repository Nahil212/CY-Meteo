all: exec

structm.o: structm.c structm.h
	gcc -c structm.c -o structm.o

struct1.o: struct1.c struct1.h
	gcc -c struct1.c -o struct1.o

main.o: main.c struct1.h structm.h
	gcc -c main.c -o main.o

exec: main.o struct1.o structm.o
	gcc main.o struct1.o structm.o -o exec