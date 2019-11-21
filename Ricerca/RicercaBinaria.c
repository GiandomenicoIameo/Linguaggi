#include <stdio.h>

#define SIZE 10

int main( void )
{
 int a;
 int array[ SIZE ];
 size_t count, posizione;
 int trovato;
 int searchKey;
 int middle, low = 0, high = SIZE - 1;

 trovato = 0;

 printf( "Enter integer search key : " );
 scanf( "%d", &searchKey );

 for( count = 0; count < SIZE; count++ )
      array[ count ] =  2 * count;

 for( count = 0; count < SIZE; count++ )
      printf( "Array[ %ld ] = %d\n", count, array[ count ] );

 while( low <= high ){
   middle = ( low + high ) / 2;

   if( searchKey == array[ middle ] ){
     trovato = 1;
     posizione = middle;
   }
   if( searchKey < array[ middle ]){
     high = middle - 1;
   }
   else{
     low = middle + 1;
   }
 }

 if( trovato )
     printf( "Valore trovato in posizione %ld\n", posizione + 1 );
 else
     printf( "Valore non trovato\n" );

 return 0;
}
