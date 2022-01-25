#include <stdio.h> // Passaggio di parametri : in per copia

void swap( int a, int b ) {
  int tmp;

  tmp = a;
  a = b;
  b = tmp;
}

int main( void ) {

  int a, b;

  printf( "%s", "a : " );
  scanf( "%d", &a );

  printf( "%s", "b : " );
  scanf( "%d", &b );

  swap( a, b );

  putchar( '\n' );
  printf( "a : %d\n", a );
  printf( "b : %d\n", b );

  return 0;
}
