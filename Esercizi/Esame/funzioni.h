#ifndef FUNZIONI
#define FUNZIONI

#include <stdio.h>

struct elem {
  int dato;
  struct elem* next;
};

struct elem* nuovaLista( void );
struct elem* convertFromIntToList( struct elem* top, int intero );
int convertFromListToInt( struct elem* top );
int somma( struct elem* top1, struct elem* top2 );
void stampaLista( struct elem* top );

#endif
