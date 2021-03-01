#ifndef _FUNZIONI_H
#define _FUNZIONI_H

struct elem {
  int data;
  struct elem *next;
};

struct elem *nuovaLista( void );
struct elem *creaNodo( int data );
struct elem *inputDaFile( struct elem *top, FILE *fptr );
void outputFile( struct elem *top, FILE *fptr );
struct elem *inserisciInOrdine( struct elem *top, struct elem *nodo );
struct elem* inserisciNuovi( struct elem* prec, struct elem* succ );
void stampaLista( struct elem *top );

#endif
