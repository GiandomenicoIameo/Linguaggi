#include <stdio.h>
#include <stdlib.h>
#include "vendor.h"

int main( void ){

char value;
int choice, len;
Nodo* TestaPtr = NULL;

NewLista( &TestaPtr, 'T' );
instruction();
puts("");

printf( "----> " );
scanf( "%d", &choice );

while( 1 ){

  switch ( choice ) {

    case 1 :
      printf( "Enter value : " );
      scanf( "\n%c", &value );
      InsertTesta( &TestaPtr, value );
      break;

    case 2 :
      puts("");
      printf( "The list is : \n" );
      puts("");
      Print( TestaPtr );
      puts("");

      break;

    case 3 :
       printf("Enter value : " );
       scanf("\n%c", &value );
       InsertCoda( &TestaPtr, value );
       break;

    case 4 :
       printf( "Enter value : " );
       scanf( "\n%c", &value );
       TestaPtr = Ordinamento( TestaPtr, value );
       break;

    case 5 :
       len = lenList( TestaPtr );
       printf( "The elements of list are : %d\n", len );

    case 6 :
       printf( "Enter value : " );
       scanf( "\n%c", &value  );
       TestaPtr = deleteNodo( TestaPtr, value );

    default :
       printf( "choice invalid. \n" );
       break;
  }

 printf( "choice ? " );
 scanf( "%d", &choice );

}

  return 0;
}
