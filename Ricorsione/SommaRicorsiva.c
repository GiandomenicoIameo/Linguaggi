#include <stdio.h>

int sommaRicorsiva( int n );

int main( void ){
    
    int val;
    int res;
    
    puts( "Inserisci numero da calcolare" );
    scanf( "%d", &val );
    
    res = sommaRicorsiva( val );
    printf( "%d\n", res );
    
    return 0;
}

int sommaRicorsiva( int n ){
    
    if( n == 0 ) 
        return n;        
    return n + sommaRicorsiva( n - 1 );
}



