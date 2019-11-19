#include <stdio.h>

int sum( int n );

int main( void ){
    
    int value;
    int result;
    
    puts( "Inserisci numero da calcolare" );
    scanf( "%d", &value );
    
    result = sum( value );
    printf( "%d\n", result );
    
    return 0;
}

int sum( int n ){
    
    if( n == 0 )
        return 0;
        
    return n + sum( n - 1 );
}



