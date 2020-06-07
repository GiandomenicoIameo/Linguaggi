#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ListAdiacenza {
  int key;
  struct ListAdiacenza* next;
};

struct Grafo {
  int numeroVertici;
  struct ListAdiacenza** summit;
};

typedef struct Grafo Grafo;
typedef struct ListAdiacenza ListAdiacenza;

Grafo* creaLista( int vertici, int lati );
void insert( Grafo** graph , int key, int vertice );
void stampaLista( Grafo* graph );
ListAdiacenza* creaNodo( int key );
void riempiLista( Grafo* graph, int lato, int vertice );
int isDuplicate( ListAdiacenza* nodePtr, int key, int vertice );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );

int main( void ) {

  Grafo* graph = NULL;
  int vertice, lato;

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &vertice );

  printf( "Inserisci numero lati : " );
  scanf( "%d", &lato );

  graph = creaLista( vertice, lato );
  riempiLista( graph, lato, vertice );
  stampaLista( graph );

  return 0;
}

void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice ) {

  nodePtr->next = *vertice;
  *vertice = nodePtr;
}


int isDuplicate( ListAdiacenza* nodePtr, int key, int vertice ) {

  while( nodePtr != NULL ) {
    if( nodePtr->key == key || vertice == key ) {
        return 1;
    }
    nodePtr = nodePtr->next;
  }
  return 0;
}


ListAdiacenza* creaNodo( int key ) {

  ListAdiacenza* newPtr = ( ListAdiacenza* )malloc( sizeof( ListAdiacenza ) );
  newPtr->key = key;
  newPtr->next = NULL;

  return newPtr;
}

Grafo* creaLista( int vertici, int lati ) {

  Grafo* graph = ( Grafo* )malloc( sizeof( Grafo ) );

  graph->numeroVertici = vertici;
  graph->summit = ( ListAdiacenza** )calloc( vertici, sizeof( ListAdiacenza* ) );

  for( int indice = 0; indice < vertici; indice++ ) {
       graph->summit[ indice ] = NULL;
  }

  return graph;
}

void insert( Grafo** graph, int key, int vertice ) {

  ListAdiacenza** list = ( *graph )->summit;
  ListAdiacenza* newPtrVertice = NULL;
  ListAdiacenza* newPtrKey = NULL;
  int True;

  if( list[ vertice ] == NULL && list[ key ] == NULL ) {
      if( vertice == key ) {
          return;
      }
      list[ vertice ] = creaNodo( key );
      list[ key ] = creaNodo( vertice );
  }
  else {

    if( !list[ vertice ] ) {
      list[ vertice ] = creaNodo( key );

      True = isDuplicate( list[ key ], key, vertice );
      if( True ) {
        return;
      }
      newPtrKey = creaNodo( vertice );
      insertTesta( newPtrKey, &( list[ key ] ) );

    } else if( !list[ key ] ) {
      list[ key ] = creaNodo( vertice );

      True = isDuplicate( list[ vertice ], key, vertice );
      if( True ) {
        return;
      }
      newPtrVertice = creaNodo( key );
      insertTesta( newPtrVertice, &( list[ vertice ] ) );
    }
  }
}

void stampaLista( Grafo* graph ) {

  ListAdiacenza** list = graph->summit;

  for( int indiceVertice = 0; indiceVertice < graph->numeroVertici; indiceVertice++ ) {
       if( list[ indiceVertice ] == NULL ) {
         printf( "Vertice [ %d ] : \n", indiceVertice );
       }
       else {
            printf( "Vertice [ %d ] : ", indiceVertice );
            while( list[ indiceVertice ] != NULL ) {
                  printf( "%d ", list[ indiceVertice ]->key );
                  list[ indiceVertice ] = list[ indiceVertice ]->next;
            }
            puts( "" );
      }
  }
}

void riempiLista( Grafo* graph, int lato, int vertice ) {

  int randomVertice, nodoDestinazione;
  srand( time( NULL ) );

  for( int indice = 0; indice < lato; indice++ ) {

    nodoDestinazione = rand() % vertice;
    randomVertice = rand() % vertice;

    insert( &graph, nodoDestinazione, randomVertice );
  }
}
