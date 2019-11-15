#include <stdio.h>
#include <stdlib.h>

struct StackNode{
  int dato;
  struct StackNode* nextPtr;
};

void StackPush( struct StackNode** topPtr, int value );
int StackPop( struct StackNode** topPtr );
void printfStack( struct StackNode* topPtr );

int main( void ){

  struct StackNode* stackPtr = NULL;
  unsigned int choice;
  int value;
  int a;

  printf( "\nSeleziona operazione 1 = Push, 2 = Pop : " );
  scanf( "%d", &choice );

while( choice > 0 || choice < 3 ) {

  switch( choice ) {

    case 1 :

        printf( "Valore del nodo : " );
        scanf( "%d", &value );
        StackPush( &stackPtr, value );
        printfStack( stackPtr );
        break;

    case 2 :

        StackPop( &stackPtr );
        printfStack( stackPtr );

        break;

    default :
        printf( "Numero non valido\n" );
        break;
  }

  printf( "\nOperazione ? " );
  scanf( "%d", &choice );
}

  return 0;
}

void StackPush( struct StackNode** topPtr, int value ) {

     struct StackNode* newPtr;
     newPtr = malloc( sizeof( struct StackNode ));

     if( newPtr != NULL ) {
        newPtr->dato = value;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
     }
     else {
        printf( "Non c'e' piu' spazio\n" );
     }
}

int StackPop( struct StackNode** topPtr ) {


      struct StackNode* tempPtr;
      int popValue;

      tempPtr = *topPtr;
      popValue = ( *topPtr )->dato;
      *topPtr = ( *topPtr )->nextPtr;
      free( tempPtr );
      return popValue;

}

void printfStack( struct StackNode* topPtr ) {

     if( topPtr == NULL )
         printf( "Lo stack e' vuoto. \n" );
     else {
         printf( "\n\n STACK : \n\n" );

         while( topPtr != NULL ) {
            printf( "  ----->  %d", topPtr->dato );
            topPtr = topPtr->nextPtr;
         }
     }
     printf("\n");
}
