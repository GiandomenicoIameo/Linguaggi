#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool atomics( int n );

bool positive( int n );
void choice_number( int *pointer );

int main( void ) {

    int n;
    choice_number( &n );

    if( atomics( n ) ) {
            puts( "Il numero e' primo" );
    } else {
            puts( "Il numero non e' primo" );
    }

    return 0;
}

bool positive( int n ) {

    if( n < 0 ) {
            return false;
    } return true;
}

void choice_number( int *pointer ) {

    printf( "Inserisci un numero : " );
    scanf( "%d", pointer );

    switch( positive( *pointer ) ) {
    case true:
            break;
    case false:
            choice_number( pointer );
            break;
    }
}

bool primes( int n ) {

    int rest, div;
    double square;

    // La funzione verifica se n è un numero primo
    // appartenente all'insieme dei numeri naturali.
    //
    // La complessità dell'algoritmo in termini di tempo e' : O( 1/2 * sqrt( n ) ).
    // La complessità dell'algoritmo in termini di spazio e' : Θ( 1 ).

    div = 3;
    square = sqrt( n );

    while( div <= square ) {
            rest = n % div;

            if( !rest ) {
                    return false;
            }
            div = div + 2;
     }
     return true;
}

bool atomics( int n ) {

    bool primes( int n );

    if( n == 2 ) {
            return true;
    } else if( n % 2 == 0 ) {
            return false;
    } else if( n == 1 ) {
            return false;
    } else {
            return primes( n );
    }
}
