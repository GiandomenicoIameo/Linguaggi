#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ListAdiacenza {
  int key;
  int peso;
  struct ListAdiacenza* next;
};

struct Grafo {
  int numeroVertici;
  struct ListAdiacenza** summit;
};

typedef struct Grafo Grafo;
typedef struct ListAdiacenza ListAdiacenza;

Grafo* creaLista( int vertici, int lati );
void insert( Grafo** graph, int key, int vertice );
void stampaLista( Grafo* graph );
ListAdiacenza* creaNodo( int key, int peso );
void riempiLista( Grafo* graph, int lato, int vertice );
int isDuplicate( ListAdiacenza* nodePtr, int key, int vertice );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );
void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst );

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

ListAdiacenza* creaNodo( int key, int peso ) {

  ListAdiacenza* newPtr = ( ListAdiacenza* )malloc( sizeof( ListAdiacenza ) );
  newPtr->key = key;
  newPtr->peso = peso;
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
  ListAdiacenza* nodeVertice = NULL;
  ListAdiacenza* nodeKey = NULL;
  int peso;

      if( vertice == key ) {
          return;
      }

      peso = ( rand() % 20 ) + 1;

      if( isDuplicate( list[ vertice ], vertice, key ) ) {
          rimuoviLato( graph, vertice, key );
          rimuoviLato( graph, key, vertice );
      }

      nodeKey = creaNodo( vertice, peso );
      insertTesta( nodeKey, &( list[ key ] ) );

      nodeVertice = creaNodo( key, peso );
      insertTesta( nodeVertice, &( list[ vertice ] ) );

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
                  printf( "[ %d ] peso -> %d ", list[ indiceVertice ]->key, list[ indiceVertice ]->peso );
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

void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst ) {

    ListAdiacenza** list = ( *graph )->summit;
    ListAdiacenza* currentPtr = ( *graph )->summit[ verticeSrc ]->next;
    ListAdiacenza* previousPtr = ( *graph )->summit[ verticeSrc ];
    ListAdiacenza* delete = NULL;

    if( ( *graph )->summit[ verticeSrc ]->key == verticeDst ) {
      delete = ( *graph )->summit[ verticeSrc ];
      ( *graph )->summit[ verticeSrc ] = ( *graph )->summit[ verticeSrc ]->next;
      free( delete );
      return;
    }

    while( currentPtr->key != verticeDst ) {
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
