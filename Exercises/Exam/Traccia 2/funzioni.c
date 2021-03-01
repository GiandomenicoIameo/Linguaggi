#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

struct elem *nuovaLista( void ) {
  return NULL;
}

struct elem *creaNodo( int data ) {

  struct elem *nodo;

  nodo = ( struct elem* )malloc( sizeof( struct elem ) );
  if( nodo == NULL ) return nodo;

  nodo->data = data;
  nodo->next = NULL;

  return nodo;
}

struct elem *inserisciInOrdine( struct elem *top, struct elem *nodo ) {

  struct elem *res;

  if( top == NULL )
      res = nodo;
  else {
      if( top->data > nodo->data ) {
          nodo->next = top;
          res = nodo;
      }
      else {
          top->next = inserisciInOrdine( top->next, nodo );
          res = top;
      }
  }
  return res;
}

void stampaLista( struct elem *top ) {

  if( top == NULL ) {
      printf( "%s\n", "Lista vuota." );
  }
  else {
      while( top != NULL ) {
        printf( "%d ", top->data );
        top = top->next;
      }
      putchar( '\n' );
  }
}

struct elem *inputDaFile( struct elem *top, FILE* fptr ) {

  struct elem *nodo = NULL;
  int data;

  fptr = fopen( "input.txt", "r" );
  if( fptr == NULL ) return top;

  fscanf( fptr, "%d", &data );

  while( !feof( fptr ) ) {
    nodo = creaNodo( data );
    top = inserisciInOrdine( top, nodo );

    fscanf( fptr, "%d", &data );
  }

  return top;
}

struct elem* inserisciNuovi( struct elem* prec, struct elem* succ ) {

  struct elem* nodo;
  struct elem* res;

  if( succ == NULL )
    res = prec;
  else {

    if( prec == NULL )
        res = inserisciNuovi( succ, succ->next );
    else {

        if( prec->data + 1 == succ->data ) {
            prec->next = inserisciNuovi( succ, succ->next );
            res = prec;
        }
        else {
            nodo = creaNodo( prec->data + 1 );
            prec->next = inserisciNuovi( nodo, succ );
            res = prec;
        }
    }
  }
  return res;
}

void outputFile( struct elem *top, FILE *fptr ) {

  fptr = fopen( "output.txt", "w" );

  while( top != NULL ) {
    fprintf( fptr, "%d ", top->data );
    top = top->next;
  }
  fprintf( fptr, "%c", '\n' );
  fclose( fptr );
}
