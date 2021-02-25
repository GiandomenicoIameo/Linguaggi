CFLAGS=-ansi -Wall -pedantic -std=c11
CC=gcc

program: main.o funzioni.o
	$(CC) $(CFLAGS) -o program main.o funzioni.o

main.o: main.c funzioni.h
	$(CC) $(CFLAGS) -c main.c

funzioni.o: funzioni.c funzioni.h
	$(CC) $(CFLAGS) -c funzioni.c

clean:
	rm *.o program
