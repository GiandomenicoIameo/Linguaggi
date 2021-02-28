#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

static void gestioneErrore( void ) {

  printf( "%s\n", "Errore." );
  exit( 0 );
}

struct elem* nuovaLista( void ) {
  return NULL;
}

static struct elem* creaNodo( int dato ) {

  struct elem* nodo;

  nodo = ( struct elem* )malloc( sizeof( struct elem ) );
  if( nodo == NULL ) return nodo;

  nodo->dato = dato;
  nodo->next = NULL;

  return nodo;
}

static struct elem* inserisciInCoda( struct elem* top, struct elem* nodo ) {

  struct elem* res;

  if( top == NULL )
      // caso base
      res = nodo;
  else {
      // passo induttivo
      top->next = inserisciInCoda( top->next, nodo );
      res = top;
  }
  return res;
}

struct elem* convertFromIntToList( struct elem* top, int intero ) {

  void gestioneErrore( void );
  struct elem* creaNodo( int dato );
  struct elem* inserisciInCoda( struct elem* top, struct elem* nodo );

  int resto;
  struct elem* nodo;

  do {
      resto = intero % 10;
      nodo = creaNodo( resto );

      if( nodo == NULL ) gestioneErrore();
      top = inserisciInCoda( top, nodo );
      intero = intero / 10;

  } while( intero != 0 );

  return top;
}

int convertFromListToInt( struct elem* top ) {

  int intero, numero, potenza;

  intero = 0;   // inizializzazione
  potenza = 1; // inizializzazione

  while( top != NULL ) {
    numero = potenza * top->dato;
    intero = intero + numero;

    potenza = potenza * 10;
    top = top->next;
  }

  return intero;
}

void stampaLista( struct elem* top ) {

  if( top == NULL )
    printf( "%s\n", "Lista vuota." );
  else {
      printf( "L " );
      while( top != NULL ) {
      printf( "-> %d ", top->dato );
      top = top->next;
    }
    putchar( '\n' );
  }
}

int somma( struct elem* top1, struct elem* top2 ) {

  int somma, res, num1, num2, potenza;

  potenza = 1; // inizializzazione
  somma = 0;     // inizializzazione

  while( top1 != NULL && top2 != NULL ) {
      // trasformo i numeri nel sistema decimale
      num1 = potenza * top1->dato;
      num2 = potenza * top2->dato;

      // sommo i numeri ottenuti
      res = num1 + num2;
      somma = somma + res;
      potenza = potenza * 10;

      // passo alla posizione successiva
      top1 = top1->next;
      top2 = top2->next;
  }

  if( top1 == NULL ) {

    while( top2 != NULL ) {
        // il secondo numero possiede un numero di cifre superiore
        num2 = potenza * top2->dato;
        somma = somma + num2;

        potenza = potenza * 10;
        top2 = top2->next;
    }
  }
  else {

    while( top1 != NULL ) {
        // il primo numero possiede un numero di cifre superiore
        num1 = potenza * top1->dato;
        somma = somma + num1;

        potenza = potenza * 10;
        top1 = top1->next;
    }
  }
  return somma;
}
