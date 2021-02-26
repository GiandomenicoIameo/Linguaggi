main : costiMinimi.o creazioneGrafo.o gestionePrenotazioni.o percorsiMinimi.o main.o
	gcc -o main costiMinimi.o creazioneGrafo.o gestionePrenotazioni.o percorsiMinimi.o main.o

main.o : main.c funzioni.h
	gcc -c main.c

percorsiMinimi.o : percorsiMinimi.c funzioni.h
	gcc -c percorsiMinimi.c

creazioneGrafo.o : creazioneGrafo.c funzioni.h
	gcc -c creazioneGrafo.c

costiMinimi.o : costiMinimi.c funzioni.h
	gcc -c costiMinimi.c

gestionePrenotazioni.o : gestionePrenotazioni.c funzioni.h
	gcc -c gestionePrenotazioni.c
