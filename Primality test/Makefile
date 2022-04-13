# Synopsis :
#      	    <command declaration> ::= make <target>=<input file>
#           Example : $ make cc=atoms

options = -ansi -Wall -pedantic -std=c11
library = -lm

$(cc):
	gcc -c $(options) $(cc).c
	gcc $(library) $(cc).o -o program.out
clean:
	rm *.o
	rm program.out
