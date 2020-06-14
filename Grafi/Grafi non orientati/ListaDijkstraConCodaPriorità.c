#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999999

struct ListAdiacenza {
  int key;
  int peso;
  struct ListAdiacenza* next;
};

struct Grafo {
  int numeroVertici;
  struct ListAdiacenza** summit;
};

struct Coda {
  int vertice;
  int distanza;
  struct Coda* next;
};

typedef struct Coda Coda;
typedef struct Grafo Grafo;
typedef struct ListAdiacenza ListAdiacenza;

Coda* creaCoda( int vertice, int distanza );
void insertCoda( Coda** Testa, int vertice, int distanza );
int removeCoda( Coda** Testa );
void removeNodo( Coda** Testa, int vertice );
Grafo* creaLista( int vertice, int lato );
void stampaLista( Grafo* graph );
void insert( Grafo** graph , int key, int vertice );
ListAdiacenza* creaNodo( int key, int peso );
void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst );
int verificaCicli( Grafo* graph, int lato );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );
int isDuplicate( ListAdiacenza* nodePtr, int key );
void calcoloDistanza( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void algoritmoDijkstra( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void inserimentoAdiacenze( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void AggiornaNodo( Coda** Testa, int vertice, int distanze );
void stampaPercorsoMinimo( int verticeSrc, int* predecessori );
void stampaArray( int* array, int size );

int main( void ) {

  Grafo* graph = NULL;
  Coda* Testa = NULL;
  int* predecessori, *distanze;
  int vertice, lato, nodoDestinazione, randomVertice, grado;

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &vertice );
  printf( "Inserisci numero lati : " );
  scanf( "%d", &lato );

  graph = creaLista( vertice, lato );
  srand( time( NULL ) );
  predecessori = ( int* )calloc( vertice, sizeof( int ) );
  distanze = ( int* )calloc( vertice, sizeof( int ) );

  for( int indice = 0; indice < vertice; indice++ ) {
     distanze[ indice ] = INF;
     predecessori[ indice ] = -1;
  }

  for( int indice = 0; indice < lato; indice++ ) {

    nodoDestinazione = rand() % vertice;
    randomVertice = rand() % vertice;

    insert( &graph, nodoDestinazione, randomVertice );
  }

  puts( "" );
  stampaLista( graph );
  puts( "" );
  puts( "" );

  algoritmoDijkstra( &Testa, graph, 0, distanze, predecessori );
  stampaArray( distanze, vertice );

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

ListAdiacenza* creaNodo( int key, int peso ) {

  ListAdiacenza* newPtr = ( ListAdiacenza* )malloc( sizeof( ListAdiacenza ) );
  newPtr->key = key;
  newPtr->peso = peso;
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
 int peso;

 if( vertice == key ) return;

 peso = ( rand() % 20 ) + 1;

 if( isDuplicate( list[ vertice ], key ) ) {
     rimuoviLato( graph, vertice, key );
     rimuoviLato( graph, key, vertice );
 }
 else {
   nodeKey = creaNodo( vertice, peso );
   insertTesta( nodeKey, &( list[ key ] ) );

   nodeVertice = creaNodo( key, peso );
   insertTesta( nodeVertice, &( list[ vertice ] ) );
 }
}

Coda* creaCoda( int vertice, int distanza ) {

  Coda* newPtr = ( Coda* )malloc( sizeof( Coda ) );
  newPtr->vertice = vertice;
  newPtr->distanza = distanza;
  newPtr->next = NULL;

  return newPtr;
}

void insertCoda( Coda** Testa, int vertice, int distanza ) {

  Coda* newPtr = NULL;
  Coda* currentPtr = NULL;
  Coda* previousPtr = NULL;

  if( *Testa == NULL )
      *Testa = creaCoda( vertice, distanza );

  else {
    currentPtr = *Testa;
    previousPtr = NULL;

    while( currentPtr != NULL && distanza > currentPtr->distanza ) {
       previousPtr = currentPtr;
       currentPtr = currentPtr->next;
    }

    if( !previousPtr ) {
      newPtr = creaCoda( vertice, distanza );
      newPtr->next = *Testa;
      *Testa = newPtr;
    }
    else {
      newPtr = creaCoda( vertice, distanza );
      previousPtr->next = newPtr;
      newPtr->next = currentPtr;
    }
  }
}

int removeCoda( Coda** Testa ) {

  Coda* deletePtr = NULL;
  int vertice = ( *Testa )->vertice;

  deletePtr = *Testa;
  *Testa = ( *Testa )->next;
  free( deletePtr );

  return vertice;
}

void removeNodo( Coda** Testa, int vertice ) {

     Coda* currentPtr;
     Coda* previousPtr;
     Coda* deletePtr;

     if( *Testa == NULL ) {
       return;
     }

     if( vertice == ( *Testa )->vertice ) {
         deletePtr = *Testa;
         *Testa = ( *Testa )->next;
         free( deletePtr );
     }
     else {
       previousPtr = *Testa;
       currentPtr = ( *Testa )->next;

     while( currentPtr != NULL && currentPtr->vertice != vertice ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
     }

     if( currentPtr != NULL ) {
        deletePtr = currentPtr;
        previousPtr->next = currentPtr->next;
        free( deletePtr );
     }
   }
}

void stampaLista( Grafo* graph ) {

  ListAdiacenza* tempTesta = NULL;

  for( int indiceVertice = 0; indiceVertice < graph->numeroVertici; indiceVertice++ ) {
       tempTesta = graph->summit[ indiceVertice ];
       if( tempTesta == NULL ) {
         printf( "Vertice [ %d ] : \n", indiceVertice );
       }
       else {
            printf( "Vertice [ %d ] : ", indiceVertice );
            while( tempTesta != NULL ) {
                  printf( "[ %d ] peso -> %d ", tempTesta->key, tempTesta->peso );
                  tempTesta = tempTesta->next;
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

void calcoloDistanza( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

     ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

     while( tempTesta != NULL ) {
        if( distanze[ verticeSrc ] + tempTesta->peso < distanze[ tempTesta->key ] ) {
            distanze[ tempTesta->key ] = distanze[ verticeSrc ] + tempTesta->peso;
            predecessori[ tempTesta->key ] = verticeSrc;
            removeNodo( Testa, tempTesta->key );
            insertCoda( Testa, tempTesta->key, distanze[ tempTesta->key ] );
        }
        tempTesta = tempTesta->next;
     }
}

void AggiornaNodo( Coda** Testa, int vertice, int distanze ) {

     Coda* tempTesta = *Testa;

     while( tempTesta != NULL ) {
        if( tempTesta->vertice == vertice ) {
            tempTesta->distanza = distanze;
            return;
        }
        tempTesta = tempTesta->next;
    }
}

void inserimentoAdiacenze( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

    ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

    while( tempTesta != NULL ) {
        distanze[ tempTesta->key ] = tempTesta->peso;
        predecessori[ tempTesta->key ] = verticeSrc;
        AggiornaNodo( Testa, tempTesta->key, distanze[ tempTesta->key ] );
        tempTesta = tempTesta->next;
    }
}

void algoritmoDijkstra( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

    int vertice;

    for( int indice = verticeSrc + 1; indice < graph->numeroVertici; indice++ )
          insertCoda( Testa, indice, INF );

  distanze[ verticeSrc ] = 0;
  inserimentoAdiacenze( Testa, graph, verticeSrc, distanze, predecessori );

  while( *Testa != NULL ) {
       vertice = removeCoda( Testa );
       calcoloDistanza( Testa, graph, vertice, distanze, predecessori );
  }
}

void stampaPercorsoMinimo( int verticeSrc, int* predecessori ) {

     if( predecessori[ verticeSrc ] == 0 ) {
         printf( "%d\n", verticeSrc );
         return;
     }
     else {
        printf( "%d\n", verticeSrc );
        stampaPercorsoMinimo( predecessori[ verticeSrc ], predecessori );
    }
}

void stampaArray( int* array, int size ) {

   for( int indice = 1; indice < size; indice++ )
       printf( "%d\n", array[ indice ] );
}
