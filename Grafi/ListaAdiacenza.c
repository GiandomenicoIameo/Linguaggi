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

int main( void ) {

  Grafo* graph = NULL;
  int vertice, lato, nodoDestinazione, randomVertice;

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &vertice );

  printf( "Inserisci numero lati : " );
  scanf( "%d", &lato );

  graph = creaLista( vertice, lato );
  srand( time( NULL ) );

  for( int indice = 0; indice < lato; indice++ ) {

    nodoDestinazione = rand() % vertice;
    randomVertice = rand() % vertice;

    insert( &graph , nodoDestinazione, randomVertice );
  }

  puts( "" );
  stampaLista( graph );

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
  ListAdiacenza* tempTesta = NULL;
  ListAdiacenza* newPtr = NULL;

  if( list[ vertice ] == NULL ) {
      if( vertice == key ) return;
      list[ vertice ] = creaNodo( key );
  }
  else {
    tempTesta = list[ vertice ];

    while( tempTesta != NULL ) {
      if( tempTesta->key == key || vertice == key ) {
          return;
      }
      tempTesta = tempTesta->next;
    }

    newPtr = creaNodo( key );
    newPtr->next = list[ vertice ];
    list[ vertice ] = newPtr;
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
