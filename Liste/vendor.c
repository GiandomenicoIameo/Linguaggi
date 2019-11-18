#include <stdio.h>
#include <stdlib.h>
#include "vendor.h"

void NewLista( Nodo** TopPtr, char value ){

      Nodo* Newptr;
      Newptr = ( Nodo* )malloc( sizeof( Nodo ));

      *TopPtr = Newptr;
      Newptr->next = NULL;
      Newptr->dato = value;
}

void InsertTesta( Nodo** TestaPtr, char value ){

      Nodo* Newptr;

      Newptr = ( Nodo* )malloc( sizeof( Nodo ));
      Newptr->dato = value;

      if ( TestaPtr != NULL ){
        Newptr->next = *TestaPtr;
        *TestaPtr = Newptr;
      }
}

void Print( Nodo* TestaPtr ){

     Nodo* temp = TestaPtr;

     while( temp != NULL ){
       printf( "-----> %c ", temp->dato );
       temp = temp->next;
     }
}

void InsertCoda( Nodo** TestaPtr, char value ){

      Nodo* temp = *TestaPtr;

      Nodo* Newptr;
      Newptr = ( Nodo* )malloc( sizeof( Nodo ));
      Newptr->dato = value;

      if ( *TestaPtr == NULL )
        *TestaPtr = Newptr;
      else{

         while( temp->next != NULL ){
             temp = temp->next;
         }
         temp->next = Newptr;
      }
}

Nodo* Ordinamento( Nodo* TestaPtr, char value ){

  Nodo* newPtr; // puntatore al nuovo nodo
  Nodo* currentPtr; // puntatore al nodo corrente
  Nodo* previousPtr; // puntatore al nodo precedente

  newPtr = ( Nodo* )malloc( sizeof( Nodo* ));

  if ( newPtr ) {
     newPtr->dato = value;
     newPtr->next = NULL;

     previousPtr = NULL;
     currentPtr = TestaPtr;

     while ( currentPtr != NULL && value > currentPtr->dato ) {
           previousPtr = currentPtr;
           currentPtr = currentPtr->next;
     }

     if ( !previousPtr ) {
        newPtr->next = TestaPtr;
        TestaPtr = newPtr;
     } else {
        previousPtr->next = newPtr;
        newPtr->next = currentPtr;
     }

     } else
        printf( "No memory available. \n" );

     return TestaPtr;
}


int lenList( Nodo* TestaPtr ){

    Nodo* currentPtr = TestaPtr;
    int count = 0;

    while ( currentPtr != NULL ){
          currentPtr = currentPtr->next;
          count = count + 1;
    }
    return count;
}

Nodo* deleteNodo( Nodo* TestaPtr, char value ){

      Nodo* currentPtr = TestaPtr->next;
      Nodo* previousPtr = TestaPtr;
      Nodo* temp;

      if ( value == TestaPtr->dato ) {
         temp = TestaPtr;
         TestaPtr = TestaPtr->next;
         free( temp );
         return TestaPtr;
      } else {

         while ( currentPtr!= NULL && currentPtr->dato != value ) {
               previousPtr = currentPtr;
               currentPtr = currentPtr->next;
         }

         if ( currentPtr->dato == value ) {
            temp = currentPtr;
            previousPtr->next = currentPtr->next;
            free( temp );
         }
       }
      return TestaPtr;
}

void instruction( void ){

     printf( "Enter choice : \n" );
     printf( "1 Inserisci elemento in Testa. \n" );
     printf( "2 Stampa lista. \n" );
     printf( "3 Inserisci elemento in Coda. \n" );
     printf( "4 Inserisci un elemento con Ordinamento. \n" );
     printf( "5 Conta elementi lista. \n" );
     printf( "6 Elimina nodo. \n" );

}
