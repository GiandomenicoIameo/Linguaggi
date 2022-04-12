#include <stdio.h>
#include <math.h>

int atomics( int n );
int primes( int n );

int main( void ) {

  int n;
  do {
          printf( "Inserisci un numero : " );
          scanf( "%d", &n );
  } while( n < 0 );

  if( atomics( n ) ) {
          puts( "Il numero e' primo" );
  } else {
          puts( "Il numero non e' primo" );
  }
  return 0;
}

int atomics( int n ) {

  if( n == 2 ) {
          return 1;
  } else if( n % 2 == 0 ) {
          return 0;
  } else if( n == 1 ) {
                  return 0;
  } else {
          return primes( n );
  }
}

int primes( int n ) {

  int rest, div;
  double square;

  // La funzione verifica se n è un numero primo
  // appartenente all'insieme dei numeri naturali.
  //
  // La complessità dell'algoritmo in termini di tempo : O( 1/2 * sqrt( n ) ).
  // La complessità dell'algoritmo in termini di spazio : Θ( 1 ).

  div = 3;
  square = sqrt( n );

  while( div <= square ) {
      rest = n % div;

      if( !rest ) {
              return 0;
      } div = div + 2;
  }
  return 1;
}
