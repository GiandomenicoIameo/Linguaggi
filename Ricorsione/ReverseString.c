#include <stdio.h>
#include <limits.h>

void stringReverse( const char* array );

int main( void ){
    
    char array[] = "Hello";
    
    stringReverse( array );
    puts( "" );
    
    return 0;
}

void stringReverse( const char* array ){
    
     if( *array == '\0' ){
         return; // il controllo ritorna al chiamante
     }
     else{
         stringReverse( array + 1 );
         putchar( *array );
     }
}