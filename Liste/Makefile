#
# Makefile compilazione
# Sistema operativo Linux con complilatore gcc
#

main : vendor.o lista.o
	gcc -o main vendor.o lista.o
#

lista.o : lista.c
	gcc -c lista.c -o lista.o

#

vendor.o : vendor.c
	gcc -c vendor.c -o vendor.o

