# Synopsis :
#       <command declaration> ::= make <target>=<input file>
#       Example : $ make cc=atoms

options = -ansi -Wall -pedantic -std=c99
lib = -lm

$(cc):
	gcc -c $(options) $(cc).c
	gcc $(lib) $(cc).o -o program.out

clean:
	rm *.o
	rm program.out
