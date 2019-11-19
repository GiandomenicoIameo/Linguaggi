#include <stdio.h>

int main( void ){

  char *vector1[ 4 ] = { "Diamonds", "Hearts", "Joker", "Spades" };
  char *vector2[ 4 ] = { "Denari", "Coppe", "Bastoni", "Spade" };
  char *vector3[ 4 ] = { "Cuori", "Picche", "Quadri", "Fiori" };
  char *vector4[ 4 ] = { "King", "Clubs", "Queen", "Ace" };

  char** array1 = vector1;
  char** array2 = vector2;
  char** array3 = vector3;
  char** array4 = vector4;

  char** matrix[ 2 ][ 2 ] = { array1, array2, array3, array4 };
  char** ( *mx )[ 2 ][ 2 ] = &matrix;

  for( int i = 0; i < 2; i++ ){
    for( int j = 0; j < 2; j++ ){
      for( int h = 0; h < 4; h++ ){
        printf( "%-10s", mx[ 0 ][ i ][ j ][ h ] );
      }
      printf( "Matrice %d\n", j );
      puts( "" );
      puts( "" );
    }
  }

  return 0;
}
