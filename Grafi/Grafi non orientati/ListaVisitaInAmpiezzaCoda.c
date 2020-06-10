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

struct Coda {
  int dato;
  struct Coda* next;
};

typedef struct Coda Coda;
typedef struct Grafo Grafo;
typedef struct ListAdiacenza ListAdiacenza;

Grafo* creaLista( int vertice, int lato );
void stampaLista( Grafo* graph );
void insert( Grafo** graph , int key, int vertice );
Coda* creaNodoCoda( int dato );
void insertCoda( Coda** Testa, int dato );
void removeCoda( Coda** Testa );
ListAdiacenza* creaNodo( int key );
void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst );
int verificaCicli( Grafo* graph, int lato );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );
int isDuplicate( ListAdiacenza* nodePtr, int key );
void inserimentoAdiacenze( Coda** Testa, Grafo* graph, int verticeSrc, int* arrayVisite );
int verificaVertici( Grafo* graph, int verticeSrc );
void visitaInAmpiezza( Grafo* graph, int numVertice, int verticeSrc, Coda** Testa );

int main( void ) {

  Grafo* graph = NULL;
  Coda* Testa = NULL;
  int vertice, lato, nodoDestinazione, randomVertice, grado;

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &vertice );
  printf( "Inserisci numero lati : " );
  scanf( "%d", &lato );

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
  visitaInAmpiezza( graph, vertice, 0, &Testa );

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

Coda* creaNodoCoda( int dato ) {

  Coda* newPtr = ( Coda* )malloc( sizeof( Coda ) );
  newPtr->dato = dato;
  newPtr->next = NULL;

  return newPtr;
}

void insertCoda( Coda** Testa, int dato ) {

  Coda* tempPtr = NULL;

  if( *Testa == NULL ) {
      *Testa = creaNodoCoda( dato );
  }
  else {

    tempPtr = *Testa;
    while( tempPtr->next != NULL ) {
      tempPtr = tempPtr->next;
    }
    tempPtr->next = creaNodoCoda( dato );
  }
}


void removeCoda( Coda** Testa ) {

  Coda* deletePtr = NULL;
  int value;

  if( *Testa == NULL ) {
    return;
  }
  else {
    deletePtr = *Testa;
    *Testa = ( *Testa )->next;
    free( deletePtr );
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

void inserimentoAdiacenze( Coda** Testa, Grafo* graph, int verticeSrc, int* arrayVisite ) {

  if( arrayVisite[ verticeSrc ] == 0 ) {
    insertCoda( Testa, verticeSrc );
    arrayVisite[ verticeSrc ] = 2; // nodo colorato di nero perché verranno inseriti in Coda
    // i vertici adiacenti
  }
    while( graph->summit[ verticeSrc ] != NULL ) {
        if( !arrayVisite[ graph->summit[ verticeSrc ]->key ] ) {
          insertCoda( Testa, graph->summit[ verticeSrc ]->key );
          arrayVisite[ graph->summit[ verticeSrc ]->key ] = 1; // nodi colorati di grigio
        }
        graph->summit[ verticeSrc ] = graph->summit[ verticeSrc ]->next;
    }
}

int verificaVertici( Grafo* graph, int verticeSrc ) {

    while( graph->summit[ verticeSrc ] != NULL ) {
         if( graph->summit[ verticeSrc ] ) {
             return 1;
         }
         graph->summit[ verticeSrc ] = graph->summit[ verticeSrc ]->next;
    }
    return 0;
}

void visitaInAmpiezza( Grafo* graph, int numVertice, int verticeSrc, Coda** Testa ) {

  Coda* tempPtr = *Testa;
  int* arrayVisite = ( int* )calloc( numVertice, sizeof( int ) );
  int esistenzaElementi;

  if( verificaVertici( graph, verticeSrc ) )
      inserimentoAdiacenze( Testa, graph, verticeSrc, arrayVisite );
  else {
    for( int indice = 0; indice < graph->numeroVertici; indice++ ) {
         if( verificaVertici( graph, indice ) ) {
             inserimentoAdiacenze( Testa, graph, indice, arrayVisite );
             break;
      }
    }
  }

  while( *Testa != NULL ) {
    if( arrayVisite[ ( *Testa )->dato ] == 2 ) {
      printf( "%d\n", ( *Testa )->dato );
      removeCoda( Testa );
    }
    else if( arrayVisite[ ( *Testa )->dato ] == 1 ) {
      arrayVisite[ ( *Testa )->dato ] = 2;
      inserimentoAdiacenze( Testa, graph, ( *Testa )->dato, arrayVisite );
    }
  }
  free( arrayVisite );
}
