test.out:	atoms.o test.o
		gcc atoms.o test.o -o test.out

test.o:		atoms.h test.c
		gcc -c -pedantic -Wall test.c

atoms.o:	atoms.h atoms.c
		gcc -c -pedantic -Wall atoms.c

clean:
	rm *.o
	rm *.out
