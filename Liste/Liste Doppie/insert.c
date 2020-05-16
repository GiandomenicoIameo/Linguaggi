#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo_SL {
  int data;
  struct Nodo_SL* next;
  struct Nodo_SL* prev;
};

typedef struct Nodo_SL Nodo_SL;

Nodo_SL* creaNodo( int data, Nodo_SL* previouPtr );
void inserimento( Nodo_SL** Testa, int data );
int stampaLista( Nodo_SL** Testa );
Nodo_SL* coda( Nodo_SL** Testa );
void stampaListaReverse( Nodo_SL** Coda, const int count );

int main( void ) {

  Nodo_SL *listPtr, *codaPtr;
  int random, choice, count;

  listPtr = NULL;
  codaPtr = NULL;
  srand( time( NULL ) );

  printf( "Inserisci numero nodi : " );
  scanf( "%d", &choice );
  puts( "" );

  for( int indice = 0; indice < choice; indice++ ) {
      random = rand() % 100 + 1;
      inserimento( &listPtr, random );
  }
  count = stampaLista( &listPtr );

  puts( "" );
  codaPtr = coda( &listPtr );
  stampaListaReverse( &codaPtr, count );
  puts( "" );

  return 0;
}

Nodo_SL* creaNodo( int data, Nodo_SL* previouPtr ) {

  Nodo_SL* nuovoNodo = ( Nodo_SL* )malloc( sizeof( Nodo_SL ) );

  nuovoNodo->next = NULL;
  nuovoNodo->prev = previouPtr;
  nuovoNodo->data = data;

  return nuovoNodo;
}

void inserimento( Nodo_SL** Testa, int data ) {

  Nodo_SL* tempTesta = NULL;

  if( *Testa == NULL ) {
    *Testa = creaNodo( data, NULL );
  }
  else {
    tempTesta = *Testa;

    while( tempTesta->next != NULL ) {
      tempTesta = tempTesta->next;
    }

    tempTesta->next = creaNodo( data, tempTesta );
  }
}

int stampaLista( Nodo_SL** Testa ) {

  Nodo_SL* tempTesta = *Testa;
  int count = 0;

  while( tempTesta != NULL ) {
    printf( "Nodo %d = %d\n",count, tempTesta->data );
    count++;
    tempTesta = tempTesta->next;
  }
  return count - 1;
}

void stampaListaReverse( Nodo_SL** Coda, const int count ) {

  Nodo_SL* tempTesta = *Coda;
  int tempCount = count;

  while( tempTesta != NULL ) {
    printf( "Nodo %d = %d\n", tempCount, tempTesta->data );
    tempCount--;
    tempTesta = tempTesta->prev;
  }
}

Nodo_SL* coda( Nodo_SL** Testa ) {

  Nodo_SL* tempTesta = *Testa;

  while( tempTesta->next != NULL ) {
    tempTesta = tempTesta->next;
  }
  return tempTesta;
}
