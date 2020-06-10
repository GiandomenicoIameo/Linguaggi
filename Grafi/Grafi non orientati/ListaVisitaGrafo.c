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

Grafo* creaLista( int vertice, int lato );
void stampaLista( Grafo* graph );
void insert( Grafo** graph , int key, int vertice );
ListAdiacenza* creaNodo( int key );
void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst );
int verificaCicli( Grafo* graph, int lato );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );
int isDuplicate( ListAdiacenza* nodePtr, int key );
void colorazioneVertici( Grafo* graph, int verticeSrc, int* arrayVisite );
void visita( Grafo* graph, int numVertice, int verticeSrc, int* arrayVisite );

int main( void ) {

  Grafo* graph = NULL;
  int vertice, lato, nodoDestinazione, randomVertice;
  int* arrayVisite;

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &vertice );
  printf( "Inserisci numero lati : " );
  scanf( "%d", &lato );

  arrayVisite = ( int* )calloc( vertice, sizeof( int ) );
  graph = creaLista( vertice, lato );
  srand( time( NULL ) );

  for( int indice = 0; indice < lato; indice++ ) {

    nodoDestinazione = rand() % vertice;
    randomVertice = rand() % vertice;

    insert( &graph, nodoDestinazione, randomVertice );
  }

  puts( "" );
  stampaLista( graph );
  puts( "" );
  visita( graph, vertice, 0, arrayVisite );

  return 0;
}

int isDuplicate( ListAdiacenza* nodePtr, int key ) {

  while( nodePtr != NULL ) {
    if( nodePtr->key == key ) {
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

ListAdiacenza* creaNodo( int key ) {

  ListAdiacenza* newPtr = ( ListAdiacenza* )malloc( sizeof( ListAdiacenza ) );
  newPtr->key = key;
  newPtr->next = NULL;

  return newPtr;
}

Grafo* creaLista( int vertice, int lato ) {

  Grafo* graph = ( Grafo* )malloc( sizeof( Grafo ) );

  graph->numeroVertici = vertice;
  graph->summit = ( ListAdiacenza** )calloc( vertice, sizeof( ListAdiacenza* ) );

  for( int indice = 0; indice < vertice; indice++ ) {
       graph->summit[ indice ] = NULL;
  }

  return graph;
}

void insert( Grafo** graph, int key, int vertice ) {

 ListAdiacenza** list = ( *graph )->summit;
 ListAdiacenza* nodeVertice = NULL;
 ListAdiacenza* nodeKey = NULL;

 if( vertice == key ) return;

 if( isDuplicate( list[ vertice ], key ) ) {
     rimuoviLato( graph, vertice, key );
     rimuoviLato( graph, key, vertice );
 }
 else {
   nodeKey = creaNodo( vertice );
   insertTesta( nodeKey, &( list[ key ] ) );

   nodeVertice = creaNodo( key );
   insertTesta( nodeVertice, &( list[ vertice ] ) );
 }
}

void stampaLista( Grafo* graph ) {

  ListAdiacenza* vertice = NULL;

  for( int indiceVertice = 0; indiceVertice < graph->numeroVertici; indiceVertice++ ) {
       if( graph->summit[ indiceVertice ] == NULL )
           printf( "Vertice [ %d ] : \n", indiceVertice );
       else {
            vertice = graph->summit[ indiceVertice ];
            printf( "Vertice [ %d ] : ", indiceVertice );
            while( vertice != NULL ) {
                  printf( "%d ", vertice->key );
                  vertice = vertice->next;
            }
            puts( "" );
      }
  }
}

void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst ) {

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

int verificaCicli( Grafo* graph, int lato ) {

    int vertice = graph->numeroVertici;

    if( lato == vertice - 1 ) return 1;
    return 0;

}

void colorazioneVertici( Grafo* graph, int verticeSrc, int* arrayVisite ) {

  ListAdiacenza* vertice = graph->summit[ verticeSrc ];

  while( vertice != NULL && !arrayVisite[ vertice->key ]  ) {
         arrayVisite[ vertice->key ] = 1;
         vertice = vertice->next;
  }
}

void visita( Grafo* graph, int numVertice, int verticeSrc, int* arrayVisite ) {

      ListAdiacenza** vertice = graph->summit;

      for( int indice = 0; indice < graph->numeroVertici; indice++ ) {
           if( arrayVisite[ indice ] )
               continue;
           else {
               arrayVisite[ indice ] = 1;
               colorazioneVertici( graph, indice, arrayVisite );
           }
      }
      free( arrayVisite );
}
