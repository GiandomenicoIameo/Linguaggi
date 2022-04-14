#include "atoms.h"

// La funzione verifica se n è un numero primo
// appartenente all'insieme dei numeri naturali.
//
// La complessità dell'algoritmo in termini di tempo e' : O( 1/2 * sqrt( n ) ).
// La complessità dell'algoritmo in termini di spazio e' : Θ( 1 ).

static bool primes( int n ) {

    int rest;
    int div = 3;

    while( div <= n / 3 ) {
            rest = n % div;

            if( !rest ) {
                    return false;
            }
            div = div + 2;
    }
    return true;
}

bool atomics( int n ) {

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
