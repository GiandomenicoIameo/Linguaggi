#include <assert.h>
#include <stdio.h>
#include "atoms.h"

void test_prime( void );

int main( void ) {

		test_prime();
		return 0;
}

void test_prime() {

		assert( atomics( -1 ) == false );

		assert( atomics( 1 )  == false );
		assert( atomics( 2 )  == true  );

		assert( atomics( 93 ) == false );
		assert( atomics( 73 ) == true  );

		printf( "%s\n", "[OK] Test sui numeri primi superati!" );
}
