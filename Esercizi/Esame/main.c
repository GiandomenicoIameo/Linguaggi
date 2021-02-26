#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

int main( void ) {

  struct elem* top1, *top2, *top3;
  int intero1, intero2, sum;

  sum = 0;
  top1 = top2 = top3 = nuovaLista();

  printf( "%s", "Inserisci primo numero : " );
  scanf( "%d", &intero1 );
  printf( "%s", "Inserisci secondo numero : " );
  scanf( "%d", &intero2 );

  top1 = convertFromIntToList( top1, intero1 );
  top2 = convertFromIntToList( top2, intero2 );

  sum = somma( top1, top2 );
  top3 = convertFromIntToList( top3, sum );

  printf( "%d\n", sum );
  stampaLista( top3 );

  return 0;
}
