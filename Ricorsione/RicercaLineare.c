#include <stdio.h>

#define SIZE 10
int linearSearch( const int array[], int key, const int size );

int main( void ){
    
    int array[ SIZE ] = { 1, 1, 1, 2, 4, 5, 6, 8, 9, 18 };
    int value;
    int result;
    
    printf( "Inserisci valore : " );
    scanf( "%d", &value );
    
    result = linearSearch( array, value, SIZE );
    
    if( result != -1 )
        printf( "Valore trovato in posizione : %d\n", result + 1 );
    else
        printf( "Valore non trovato\n" );
    
        
    return 0;
}

int linearSearch( const int array[], int key, const int size ){
    
    if( array[ size ] == key ){
        return size;
    }
    else if( array[ size ] != key && size < 0 ){
        return -1;
    }
    else{
        return linearSearch( array, key, size - 1 );
    }
}

