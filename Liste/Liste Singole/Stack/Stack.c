#include <stdio.h>
#include <stdlib.h>

struct StackNode{
  int dato;
  struct StackNode* next;
};

typedef struct StackNode StackNode;

StackNode* CreaNodo_SL( int value );
void StackPush( StackNode** topPtr, int value );
void StackPop( StackNode** topPtr );
void StampaStack( StackNode* topPtr );
void instructions( void );

int main( void ){

  StackNode* stackPtr = NULL;
  int choice;
  int dato;

  instructions();
  scanf( "%d", &choice );

  while( choice != 3 ) {

    switch( choice ) {

      case 1 :
         printf( "Valore del nodo : " );
         scanf( "%d", &dato );
         StackPush( &stackPtr, dato );
         StampaStack( stackPtr );
         break;
     case 2 :
         if( !stackPtr ) {
             puts( "Lo Stack è vuoto. " );
             break;
         }
         StackPop( &stackPtr );
         StampaStack( stackPtr );
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

void instructions( void ) {

   puts( "1) Push" );
   puts( "2) Pop" );
   puts( "3) to end program" );
}

StackNode* CreaNodo_SL( int dato ) {

   StackNode* newPtr = ( StackNode* )malloc( sizeof( StackNode ));
   newPtr->dato = dato;
   newPtr->next = NULL;

   return newPtr;
}

void StackPush( StackNode** topPtr, int dato ) {

    StackNode* newPtr;

    if( *topPtr == NULL ) {
        *topPtr = CreaNodo_SL( dato );
    }
    else {
        newPtr = CreaNodo_SL( dato );
        newPtr->next = *topPtr;
        *topPtr = newPtr;
    }
}

void StackPop( StackNode** topPtr ) {

    StackNode* tempPtr;

    tempPtr = *topPtr;
    *topPtr = ( *topPtr )->next;
    free( tempPtr );
}

void StampaStack( StackNode* topPtr ) {

     if( topPtr == NULL )
         puts( "Lo stack e' vuoto. " );
     else {
         printf( "\n\n STACK : \n\n" );

         while( topPtr != NULL ) {
            printf( "  ----->  %d", topPtr->dato );
            topPtr = topPtr->next;
         }
     }
     puts( "" );
}
