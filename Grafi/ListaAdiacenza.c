#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ListAdj {
  int key;
  struct ListAdj* next;
};

struct Grafo {
  int numeroVertici;
  struct ListAdj** adj;
};

typedef struct Grafo Grafo;
typedef struct ListAdj ListAdj;

Grafo* creaLista( int vertici, int lati );
void insert( Grafo** graph, int key, int vertice );
void stampaLista( Grafo* graph );
ListAdj* creaNodo( int key );

int main( void ) {

  Grafo* graph = NULL;
  int vertice, lato, value, randomVertice;

  srand( time( NULL ) );

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &vertice );

  printf( "Inserisci numero lati : " );
  scanf( "%d", &lato );

  graph = creaLista( vertice, lato );

  for( int indice = 0; indice < lato; indice++ ) {
    value = rand() % 100;
    randomVertice = rand() % vertice;
    insert( &graph, value, randomVertice );
  }

  puts( "" );
  stampaLista( graph );

  return 0;
}

ListAdj* creaNodo( int key ) {

  ListAdj* newPtr = ( ListAdj* )malloc( sizeof( ListAdj ) );
  newPtr->key = key;
  newPtr->next = NULL;

  return newPtr;
}

Grafo* creaLista( int vertici, int lati ) {

  Grafo* graph = ( Grafo* )malloc( sizeof( Grafo ) );
  int indice = 0;

  graph->numeroVertici = vertici;
  graph->adj = ( ListAdj** )calloc( vertici, sizeof( ListAdj* ) );

  while( indice < vertici ) {
    graph->adj[ indice ] = NULL;
    indice++;
  }

  return graph;
}

void insert( Grafo** graph, int key, int vertice ) {

  Grafo* tempGraph = *graph;
  ListAdj* newPtr = creaNodo( key );

  if( tempGraph->adj[ vertice ] == NULL ) {
      tempGraph->adj[ vertice ] = creaNodo( key );
  }
  else {
    newPtr->next = tempGraph->adj[ vertice ];
    tempGraph->adj[ vertice ] = newPtr;
  }
}

void stampaLista( Grafo* graph ) {

  int indiceVertice = 0;

  while( indiceVertice < graph->numeroVertici ) {
      if( graph->adj[ indiceVertice ] == NULL ) {
        indiceVertice++;
        continue;
      } else {
        while( graph->adj[ indiceVertice ] != NULL ) {
            printf( "%d ", graph->adj[ indiceVertice ]->key );
            graph->adj[ indiceVertice ] = graph->adj[ indiceVertice ]->next;
        }
      }
      puts( "" );
      indiceVertice++;
    }
}
