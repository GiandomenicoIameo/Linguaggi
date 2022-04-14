#include "atoms.h"
#include <math.h>

// La funzione verifica se n è un numero primo
// appartenente all'insieme dei numeri naturali.
//
// La complessità dell'algoritmo in termini di tempo e' : O( n/6 ).
// La complessità dell'algoritmo in termini di spazio e' : Θ( 1 ).

static bool primes( int n ) {

    int rest, div;
    double square;

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
