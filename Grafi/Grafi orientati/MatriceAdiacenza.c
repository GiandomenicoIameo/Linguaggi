#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creaMatrice( int summit, int*** grafo );
void inizializza( int summit, int** grafo );

int main( void ) {

  int** grafo;
  int randomRow, randomCol, summit, side, indice = 0;

  srand( time( NULL ) );

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &summit );
  printf( "Inserisci numero lati : " );
  scanf( "%d", &side );

  creaMatrice( summit, &grafo );
  inizializza( summit, grafo );

  while( indice < side ) {
    randomRow = rand() % summit;
    randomCol = rand() % summit;

    if( grafo[ randomRow ][ randomCol ] ) {
        indice--;
    } else {
        grafo[ randomRow ][ randomCol ] = 1;
    }
    indice = indice + 1;
  }
  puts( "" );

for( int i = 0; i < summit; i++ ) {
  printf(  "     [ %d ]", i );
}
puts( "" );

for( int i = 0; i < summit; i++ ) {
  printf( "[ %d ]  ", i );
  for( int j = 0; j < summit; j++ ) {
    printf( "%d         ", grafo[ i ][ j ] );
  }
  puts( "" );
}

  return 0;
}

void creaMatrice( int summit, int*** grafo ) {

  *grafo = ( int** )calloc( summit, sizeof( int* ) );
  for( int indice = 0; indice < summit; indice++ ) {
      ( *grafo )[ indice ] = ( int* )calloc( summit, sizeof( int ) );
  }
}

void inizializza( int summit, int** grafo ) {

  for( int indiceRow = 0; indiceRow < summit; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < summit; indiceCol++ )
      grafo[ indiceRow ][ indiceCol ] = 0;
  }
}
