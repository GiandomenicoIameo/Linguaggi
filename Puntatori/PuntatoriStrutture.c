#include <stdio.h>
#include <stdlib.h>

typedef struct card{
  char *suit[ 2 ];
} Card;

int main( void ){

  Card vector_1[ 3 ] = { {"Clubs", "Diamond"}, {"Hearts", "Spades"}, {"King", "Queen"} };
  Card vector_2[ 3 ] = { {"Denari", "Spade" }, {"Coppe", "Bastoni"}, {"King", "Queen"} };
  Card vector_3[ 3 ] = { {"Picche", "Fiori" }, {"Quadri", "Cuori" }, {"King", "Queen"} };

  Card *ptrVector[ 3 ] = { vector_1, vector_2, vector_3 };
  Card* ( *ptr )[ 3 ] = { &ptrVector };

  puts( "" );
  for( int i = 0; i < 3; i++ ){
    for( int j = 0; j < 3; j++ ){
      for( int h = 0; h < 2; h++ ){
        printf( "%-10s", ptr[ 0 ][ i ][ j ].suit[ h ] );
      }
    }
    puts( "" );
  }
  puts( "" );

  return 0;
}
