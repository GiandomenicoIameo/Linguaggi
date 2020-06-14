#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999999

struct Coda {
  int vertice;
  int distanza;
  struct Coda* next;
};

typedef struct Coda Coda;
typedef struct Nodo_SL Nodo_SL;

Coda* creaCoda( int vertice, int distanza );
void insertCoda( Coda** Testa, int vertice, int distanza );
int removeCoda( Coda** Testa );
void removeNodo( Coda** Testa, int vertice );
void creaMatrice( int*** grafo, int numVertice );
void inizializza( int** grafo, int numVertice );
void inizializzaArray( int* array, int size, int value );
void stampaMatrice( int** grafo, int numVertice );
void riempiMatrice( int** grafo, int numLato, int numVertice );
int verificaCicli( int numLato, int numVertice );
void calcoloDistanza( Coda** Testa, int** grafo, int verticeSrc, int numVertice, int* distanze, int* predecessori );
void algoritmoDijkstra( Coda** Testa, int** grafo, int verticeSrc, int numVertice, int* distanze, int* predecessori );
void inserimentoAdiacenze( Coda** Testa, int** grafo, int verticeSrc, int numVertice, int* distanze, int* predecessori );
void AggiornaNodo( Coda** Testa, int vertice, int distanze );
void stampaPercorsoMinimo( int verticeSrc, int* predecessori );
void stampaArray( int* array, int size );

int main( void ) {

  Coda* Testa = NULL;
  int** grafo;
  int numVertice, numLato;
  int totLati;
  int* distanze, *predecessori;

  do {

    printf( "Inserisci numero vertici : " );
    scanf( "%d", &numVertice );

    totLati = (( numVertice * numVertice ) - numVertice ) / 2;
    distanze = ( int* )calloc( numVertice, sizeof( int ) );
    predecessori = ( int* )calloc( numVertice, sizeof( int ) );

    inizializzaArray( distanze, numVertice, INF );
    inizializzaArray( predecessori, numVertice, -1 );

    printf( "Inserisci numero lati : " );
    scanf( "%d", &numLato );

    if( numLato > totLati ) {-
      printf( "Capienza superata ripeti !!\n\n" );
    }

  } while( numLato > totLati );

  creaMatrice( &grafo, numVertice );
  inizializza( grafo, numVertice );
  riempiMatrice( grafo, numLato, numVertice );
  stampaMatrice( grafo, numVertice );
  algoritmoDijkstra( &Testa, grafo, 0, numVertice, distanze, predecessori );
  stampaPercorsoMinimo( 2, predecessori );
  puts( "" );
  stampaArray( distanze, numVertice );

  return 0;
}

void creaMatrice( int*** grafo, int numVertice ) {

  *grafo = ( int** )calloc( numVertice, sizeof( int* ) );
  for( int indice = 0; indice < numVertice; indice++ ) {
      ( *grafo )[ indice ] = ( int* )calloc( numVertice, sizeof( int ) );
  }
}

void inizializza( int** grafo, int numVertice ) {

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ )
      grafo[ indiceRow ][ indiceCol ] = 0;
  }
}

void inizializzaArray( int* array, int size, int value ) {

  for( int indice = 0; indice < size; indice++ )
      array[ indice ] = value;
}

void stampaMatrice( int** grafo, int numVertice ) {

  for( int indice = 0; indice < numVertice; indice++ ) {
    printf(  "     [ %d ]", indice );
  }
  puts( "" );

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    printf( "[ %d ]  ", indiceRow );
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ ) {
      printf( "%d         ", grafo[ indiceRow ][ indiceCol ] );
    }
    puts( "" );
  }
}

void riempiMatrice( int** grafo, int numLato, int numVertice ) {

  int indice = 0;
  int randomCol, randomRow, randomValue;

  while( indice < numLato ) {

      randomRow = rand() % numVertice;
      randomCol = rand() % numVertice;

      if( grafo[ randomRow ][ randomCol ] ) {
          indice--;
      } else {
          randomValue = rand() % 20;
          grafo[ randomRow ][ randomCol ] = randomValue;
          grafo[ randomCol ][ randomRow ] = randomValue;
      }
      indice = indice + 1;
  }
}

int verificaCicli( int numLato, int numVertice ) {

  if( numLato == numVertice - 1 ) return 1;
  return 0;
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

void calcoloDistanza( Coda** Testa, int** grafo, int verticeSrc, int numVertice, int* distanze, int* predecessori ) {

  for( int indice = 0; indice < numVertice; indice++ ) {
      if( grafo[ verticeSrc ][ indice ] && indice != verticeSrc ) {
          if( distanze[ verticeSrc ] + grafo[ verticeSrc ][ indice ] < distanze[ indice ] ) {
              distanze[ indice ] = distanze[ verticeSrc ] + grafo[ verticeSrc ][ indice ];
              predecessori[ indice ] = verticeSrc;
              removeNodo( Testa, indice );
              insertCoda( Testa, indice, distanze[ indice ] );
          }
      }
  }
}

void algoritmoDijkstra( Coda** Testa, int** grafo, int verticeSrc, int numVertice, int* distanze, int* predecessori ) {

     int vertice;

     for( int indice = verticeSrc + 1; indice < numVertice; indice++ ) {
          insertCoda( Testa, indice, INF );
     }

     distanze[ verticeSrc ] = 0;
     inserimentoAdiacenze( Testa, grafo, verticeSrc, numVertice, distanze, predecessori );

     while( *Testa != NULL ) {
          vertice = removeCoda( Testa );
          calcoloDistanza( Testa, grafo, vertice, numVertice, distanze, predecessori );
     }
}

void inserimentoAdiacenze( Coda** Testa, int** grafo, int verticeSrc, int numVertice, int* distanze, int* predecessori ) {

    for( int indice = 0; indice < numVertice; indice++ ) {
         if( grafo[ verticeSrc ][ indice ] && indice != verticeSrc ) {
             distanze[ indice ] = grafo[ verticeSrc ][ indice ];
             predecessori[ indice ] = verticeSrc;
             AggiornaNodo( Testa, indice, distanze[ indice ] );
         }
    }
}

void AggiornaNodo( Coda** Testa, int vertice, int distanze ) {

     Coda* tempTesta = *Testa;

     while( tempTesta->next != NULL ) {
        if( tempTesta->vertice == vertice ) {
            tempTesta->distanza = distanze;
            break;
        }
        tempTesta = tempTesta->next;
    }
}

void removeNodo( Coda** Testa, int vertice ) {

     Coda* currentPtr = *Testa;
     Coda* previousPtr = NULL;
     Coda* deletePtr = NULL;

     while( currentPtr != NULL && currentPtr->vertice != vertice ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
     }

     if( !previousPtr ) {
        deletePtr = *Testa;
        *Testa = ( *Testa )->next;
        free( deletePtr );
     }
     else if( currentPtr != NULL ) {
       previousPtr->next = currentPtr->next;
       deletePtr = currentPtr;
       free( deletePtr );
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
