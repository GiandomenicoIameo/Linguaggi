#include <stdio.h>

int main( void ) {

  int i;
  unsigned char c;

  printf( "%s", "Inserisci intero : " );
  scanf( "%d", &i );

  c = i;
  printf( "Gli interi %d e %d sono congrui modulo 256.\n", i, c );

  return 0;
}
