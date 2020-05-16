#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo_SL {
  int data;
  struct Nodo_SL* next;
};

typedef struct Nodo_SL Nodo_SL;

Nodo_SL* creaNodo( int data );
void inserimento( Nodo_SL** Testa, int nodi );
void stampaLista( Nodo_SL** Testa, int nodi );

int main( void ) {

  Nodo_SL *listPtr, *codaPtr;
  int nodi;

  listPtr = NULL;

  printf( "Inserisci numero nodi : " );
  scanf( "%d", &nodi );

  inserimento( &listPtr, nodi );
  stampaLista( &listPtr, nodi );

  return 0;
}

Nodo_SL* creaNodo( int data ) {

  Nodo_SL* nuovoNodo = ( Nodo_SL* )malloc( sizeof( Nodo_SL ) );

  nuovoNodo->next = NULL;
  nuovoNodo->data = data;

  return nuovoNodo;
}

void inserimento( Nodo_SL** Testa, int nodi ) {

  Nodo_SL* tempTesta = NULL;
  int count, random;

  srand( time( NULL ) );
  count = 0;

  if( *Testa == NULL ) {
    random = rand() % 100 + 1;
    *Testa = creaNodo( random );
  }
  tempTesta = *Testa;

  while( count < nodi ) {
    random = rand() % 100 + 1;
    tempTesta->next = creaNodo( random );

    count++;
    tempTesta = tempTesta->next;
  }

  tempTesta->next = *Testa;
}

void stampaLista( Nodo_SL** Testa, int nodi ) {

  Nodo_SL* tempTesta = *Testa;
  int count = 0;

  while( count < nodi ) {
    printf( "%d\n", tempTesta->data );
    count++;
    tempTesta = tempTesta->next;
  }
}
