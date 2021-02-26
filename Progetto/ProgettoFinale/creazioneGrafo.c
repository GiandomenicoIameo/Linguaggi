#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funzioni.h"

void buffer( void ) {
  while( getchar() != '\n' );
}

int ricercaCosto( Grafo* graph, int verticeSrc, int verticeDst ) {

    ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

    while( tempTesta != NULL && tempTesta->vertice != verticeDst ) {
        tempTesta = tempTesta->next;
    }
    if( tempTesta != NULL ) {
        return tempTesta->costo;
    }
}

int ricercaMeta( char** citta, char* meta ) {

    int value;

    for( int indice = 0; indice < 24; indice++ ) {
         value = strcmp( citta[ indice ], meta );
         if( !value )
             return indice;
    }
    return -1;
}

int isDuplicate( ListAdiacenza* nodePtr, int vertice ) {

  while( nodePtr != NULL ) {
    if( nodePtr->vertice == vertice ) {
        return 1;
    }
    nodePtr = nodePtr->next;
  }
  return 0;
}

void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice ) {

  nodePtr->next = *vertice;
  *vertice = nodePtr;
}

ListAdiacenza* creaNodoGrafo( int vertice, int costo, char* citta, int prezzo ) {

  ListAdiacenza* newPtr = ( ListAdiacenza* )malloc( sizeof( ListAdiacenza ) );

  newPtr->vertice = vertice;
  newPtr->costo = costo;
  newPtr->prezzo = prezzo;

  strcpy( newPtr->citta, citta );
  newPtr->next = NULL;

  return newPtr;
}

Grafo* creaLista( int vertice ) {

  Grafo* graph = ( Grafo* )malloc( sizeof( Grafo ) );

  graph->numeroVertici = vertice;
  graph->summit = ( ListAdiacenza** )calloc( vertice, sizeof( ListAdiacenza* ) );

  for( int indice = 0; indice < vertice; indice++ ) {
       graph->summit[ indice ] = NULL;
  }

  return graph;
}

void insert( Grafo** graph, int vertice, int verticeDst, int costo, char* cittaDestinazione, int prezzo ) {

 ListAdiacenza** list = ( *graph )->summit;
 ListAdiacenza* nodeVertice = NULL;
 ListAdiacenza* nodeKey = NULL;

 nodeKey = creaNodoGrafo( vertice, costo, cittaDestinazione, prezzo );
 insertTesta( nodeKey, &( list[ verticeDst ] ) );

}

void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst ) {

    ListAdiacenza* currentPtr;
    ListAdiacenza* previousPtr;
    ListAdiacenza* delete = NULL;

    if( ( *graph )->summit[ verticeSrc ]->vertice == verticeDst ) {
      delete = ( *graph )->summit[ verticeSrc ];
      ( *graph )->summit[ verticeSrc ] = ( *graph )->summit[ verticeSrc ]->next;
      free( delete );
      return;
    }

    currentPtr = ( *graph )->summit[ verticeSrc ]->next;
    previousPtr = ( *graph )->summit[ verticeSrc ];

    while( currentPtr->vertice != verticeDst ) {
      previousPtr = currentPtr;
      currentPtr = currentPtr->next;
    }

    if( currentPtr != NULL ) {
       delete = currentPtr;
       previousPtr->next = currentPtr->next;
       free( delete );
       return;
    }
}

void stampaListaGrafo( Grafo* graph ) {

  ListAdiacenza* tempTesta = NULL;

  for( int indiceVertice = 0; indiceVertice < graph->numeroVertici; indiceVertice++ ) {
       tempTesta = graph->summit[ indiceVertice ];
       if( tempTesta == NULL ) {
         printf( "Vertice [ %d ] : \n", indiceVertice );
       }
       else {
            printf( "citta [ %d ] : ", indiceVertice );
            while( tempTesta != NULL ) {
                  printf( "[ %s ] -> %d", tempTesta->citta, tempTesta->costo );
                  tempTesta = tempTesta->next;
            }
            puts( "" );
      }
  }
}

void inizializzaArray( int* array, int size, int value ) {

    for( int indice = 0; indice < size; indice++ )
         array[ indice ] = value;
}
