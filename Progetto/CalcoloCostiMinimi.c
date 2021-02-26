#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INF 9999999
#define vertici 20

struct ListAdiacenza {
  int vertice;
  char citta[ vertici ];
  int costo;
  struct ListAdiacenza* next;
};

struct Grafo {
  int numeroVertici;
  struct ListAdiacenza** summit;
};

struct Coda {
  char citta[ vertici ];
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
void insert( Grafo** graph , int vertice, int numVertice, char** citta );
void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst );
ListAdiacenza* creaNodo( int vertice, int costo, char* citta );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );
int isDuplicate( ListAdiacenza* nodePtr, int costo );
void calcoloDistanza( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void algoritmoDijkstra( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void inserimentoAdiacenze( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void AggiornaNodo( Coda** Testa, int vertice, int distanze );
int stampaArray( int* array, int size, int verticeDst );
void stampaPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze );
int ricercaMeta( char** citta, char* meta );
void buffer( void );

int main( void ) {

  Grafo* graph = NULL;
  Coda* Testa = NULL;
  int* predecessori, *distanze;
  int verticePartenza, verticeDestinazione, nodoDestinazione, randomVertice, grado;
  char partenza[ vertici ], destinazione[ vertici ];
  char* nomeCitta[ vertici ] = { "Napoli", "Roma", "Trapani", "Palermo", "Catania", "Messina", "Taranto", "Lamezia", "Bari", "Pescara", "Ancona",
                                 "Cagliari", "Cibia", "Firenze", "Bologna", "Genova", "Milano", "Torino", "Venezia", "Trieste" } ;

  graph = creaLista( vertici, vertici );
  srand( time( NULL ) );
  predecessori = ( int* )calloc( vertici, sizeof( int ) );
  distanze = ( int* )calloc( vertici, sizeof( int ) );

  for( int indice = 0; indice < vertici; indice++ ) {
     distanze[ indice ] = INF;
     predecessori[ indice ] = -1;
  }

  for( int indice = 0; indice < vertici; indice++ ) {

    nodoDestinazione = rand() % vertici;
    insert( &graph, indice, nodoDestinazione, nomeCitta );
  }

  printf( "Scegli partenza : " );
  scanf( "%s", partenza );
  buffer();
  printf( "Scegli destinazione : " );
  scanf( "%s", destinazione );

  verticePartenza = ricercaMeta( nomeCitta, partenza );
  verticeDestinazione = ricercaMeta( nomeCitta, destinazione );

  algoritmoDijkstra( &Testa, graph, verticePartenza, distanze, predecessori );
  printf( "Il costo totale è : " );
  stampaArray( distanze, vertici, verticeDestinazione );

  puts( "" );

  return 0;
}

void buffer( void ) {
  while( getchar() != '\n' );
}

int ricercaMeta( char** citta, char* meta ) {

    int value;

    for( int indice = 0; indice < vertici; indice++ ) {
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

ListAdiacenza* creaNodo( int vertice, int costo, char* citta ) {

  ListAdiacenza* newPtr = ( ListAdiacenza* )malloc( sizeof( ListAdiacenza ) );

  newPtr->vertice = vertice;
  newPtr->costo = costo;

  strcpy( newPtr->citta, citta );
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

void insert( Grafo** graph, int vertice, int numVertice, char** citta ) {

 ListAdiacenza** list = ( *graph )->summit;
 ListAdiacenza* nodeVertice = NULL;
 ListAdiacenza* nodeKey = NULL;
 int costo;

 if( vertice == numVertice ) return;

 costo = ( rand() % vertici ) + 1;

 if( isDuplicate( list[ vertice ], numVertice ) ) {
     rimuoviLato( graph, vertice, numVertice );
     rimuoviLato( graph, numVertice, vertice );
 }
 else {
   nodeKey = creaNodo( vertice, costo, citta[ vertice ] );
   insertTesta( nodeKey, &( list[ numVertice ] ) );

   nodeVertice = creaNodo( numVertice, costo, citta[ numVertice ] );
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

int verificaCicli( Grafo* graph, int lato ) {

    int vertice = graph->numeroVertici;

    if( lato == vertice - 1 ) return 1;
    return 0;
}

void calcoloDistanza( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

     ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

     while( tempTesta != NULL ) {
        if( distanze[ verticeSrc ] + tempTesta->costo < distanze[ tempTesta->vertice ] ) {
            distanze[ tempTesta->vertice ] = distanze[ verticeSrc ] + tempTesta->costo;
            predecessori[ tempTesta->vertice ] = verticeSrc;
            removeNodo( Testa, tempTesta->vertice );
            insertCoda( Testa, tempTesta->vertice, distanze[ tempTesta->vertice ] );
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
        distanze[ tempTesta->vertice ] = tempTesta->costo;
        predecessori[ tempTesta->vertice ] = verticeSrc;
        AggiornaNodo( Testa, tempTesta->vertice, distanze[ tempTesta->vertice ] );
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

void stampaPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze ) {

     if( distanze[ verticeDst ] == INF ) {
         puts( "NULL" );
         return;
     }

     if( predecessori[ verticeDst ] == verticeSrc ) {
         printf( " %s", citta[ verticeSrc ] );
         return;
     }
     else {
        printf( "%s < ", citta[ verticeDst ] );
        stampaPercorsoMinimo( predecessori[ verticeDst ], verticeSrc, predecessori, citta, distanze );
    }
}

int stampaArray( int* array, int size, int verticeDst ) {

   for( int indice = 0; indice < size; indice++ ) {
        if( verticeDst == indice ) {
            if( array[ indice ] == INF )
                 return -1;
            else
                return array[ indice ];
        }
   }
}
