#include <stdio.h>

#define SIZE 10
void PrintArray( int array[], size_t size );

int main( void ){
    
    int array[ SIZE ] = { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
    
    PrintArray( array, SIZE );
    
    
    return 0;
}

void PrintArray( int array[], size_t size ){
    
    if( size <= 0 ){
        return;
    }
    else{
        printf( "%d\n", array[ size - 1 ] );
        PrintArray( array, size - 1 );
    }
}