#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creaMatrice( int summit, int*** graphAdj );
void inizializza( int summit, int** graphAdj );

int main( void ) {

  int** graphAdj;
  int randomRow, randomCol, summit, side, indice = 0;

  srand( time( NULL ) );

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &summit );
  printf( "Inserisci numero lati : " );
  scanf( "%d", &side );

  creaMatrice( summit, &graphAdj );
  inizializza( summit, graphAdj );

  while( indice < side ) {
    randomRow = rand() % summit;
    randomCol = rand() % summit;

    if( graphAdj[ randomRow ][ randomCol ] ) {
        indice--;
    } else {
        graphAdj[ randomRow ][ randomCol ] = 1;
    }
    indice = indice + 1;
  }
  puts( "" );

for( int i = 0; i < summit; i++ ) {
  for( int j = 0; j < summit; j++ ) {
    printf( "%d ", graphAdj[ i ][ j ] );
  }
  puts( "" );
}

  return 0;
}

void creaMatrice( int summit, int*** graphAdj ) {

  *graphAdj = ( int** )calloc( summit, sizeof( int* ) );
  for( int indice = 0; indice < summit; indice++ ) {
      ( *graphAdj )[ indice ] = ( int* )calloc( summit, sizeof( int ) );
  }
}

void inizializza( int summit, int** graphAdj ) {

  for( int indiceRow = 0; indiceRow < summit; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < summit; indiceCol++ )
      graphAdj[ indiceRow ][ indiceCol ] = 0;
  }
}
