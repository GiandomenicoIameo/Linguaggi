#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creaMatrice( int*** grafo, int numVertice );
void inizializza( int** grafo, int numVertice );
void stampaMatrice( int** grafo, int numVertice );
void riempiMatrice( int** grafo, int numLato, int numVertice );
int verificaCicli( int numLato, int numVertice );

int main( void ) {

  int** grafo;
  int numVertice, numLato;
  int totLati;

  do {

    printf( "Inserisci numero vertici : " );
    scanf( "%d", &numVertice );

    totLati = (( numVertice * numVertice ) - numVertice ) / 2;

    printf( "Inserisci numero lati : " );
    scanf( "%d", &numLato );

    if( numLato > totLati ) {
      printf( "Capienza superata ripeti !!\n\n" );
    }

  } while( numLato > totLati );

  creaMatrice( &grafo, numVertice );
  inizializza( grafo, numVertice );
  riempiMatrice( grafo, numLato, numVertice );
  stampaMatrice( grafo, numVertice );

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
  int randomCol, randomRow;

  while( indice < numLato ) {

      randomRow = rand() % numVertice;
      randomCol = rand() % numVertice;

      if( grafo[ randomRow ][ randomCol ] ) {
          indice--;
      } else {
          grafo[ randomRow ][ randomCol ] = 1;
          grafo[ randomCol ][ randomRow ] = 1;
      }
      indice = indice + 1;
  }
}

int verificaCicli( int numLato, int numVertice ) {

  if( numLato == numVertice - 1 ) return 1;
  return 0;
}
