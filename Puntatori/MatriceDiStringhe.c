#include <stdio.h>
#include <stdlib.h>

void printArray( char* ( *ptr )[ 3 ], char* string, const int size );

int main( void ){

  char* Mx[ 3 ][ 3 ] = { NULL };
  printArray( Mx , "Giandomenico", 3 );

  for( int i = 0; i < 3; i++ ){
    for( int j = 0; j < 3; j++ ){
      printf( "%s  ", Mx[ i ][ j ] );
    }
    puts( "" );
  }
  return 0;
}

void printArray( char* ( *ptr )[ 3 ], char* string, const int size ){

  for( int i = 0; i < size; i++ )
    for( int j = 0; j < 3; j++ )
        ptr[ i ][ j ] = string;
}
