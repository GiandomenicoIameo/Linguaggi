/******************************************************************************

                            Crypto v0.0
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define SIZE 10

void* __crypt(   char* src, char* dst, const int len, int chiave   );
void __decrypt( char* src, const int len, int chiave );

int main( void )
{
    char src[ SIZE ];
    char* cryptstr = NULL;
    char dst[ SIZE ];
    int chiave;
    
    puts( "Inserisci stringa" );
    fgets( src, SIZE + 1, stdin );
    puts( "Inserisci chiave" );
    scanf( "%d", &chiave );
    
    int len = strlen( src );
   
   puts( "Stringa criptata" ); 
   cryptstr = ( char* )__crypt( src, dst, len, chiave );
    puts( "Stringa decriptata" );
   __decrypt( dst, len, chiave );
    
    return 0;
}

void* __crypt( char* src, char* dst, const int len, int chiave ){
    
    int i;

     for( i = 0; i < len; i++ ){
        dst[ i ] = src[ i ] + chiave;
    }
    dst[ i ] = '\0';

    puts( dst );
    return dst;
    
}

void __decrypt( char* src, const int len, int chiave ){
    
    char decryptString[ len ];
    int i;
    
     for( i = 0; i < len; i++ ){
        decryptString[ i ] = src[ i ] - chiave;
    }
    decryptString[ i ] = '\0';
    
    puts( decryptString );
    
}
