#include <stdio.h>
#include <stdlib.h>

struct Nodo_SL {
  char data;
  struct Nodo_SL* next;
};

typedef struct Nodo_SL Nodo;

Nodo* NewLista( Nodo* TestaPtr );
Nodo* InsertInTesta( Nodo* TestaPtr, char value );
void printList( Nodo* TestaPtr );
int RicercaValore( Nodo* TestaPtr, char value );
void DeleteElement( Nodo* TestaPtr, char value );
int LenList( Nodo* TestaPtr );
Nodo* InsertCoda( Nodo* TestaPtr, char value );

int main( void ) {

Nodo* TestaPtr = NULL, *NodoPtr = NULL, *CodaPtr = NULL, *ptr = NULL;
int count, choice, len;
char value;
TestaPtr = NewLista( TestaPtr );

printf( "Enter choice: \n" );
printf( "1 to insert an element into the list( Head ). \n" );
printf( "2 to Insert an element into the list( Queue ). \n" );
printf( "3 to end. \n" );
scanf( "%d", &choice );

while( choice > 0 || choice < 5 ){

  switch( choice ){

    case 1 :

       printf( "Inserisci lettera nodo : " );
       scanf( "\n%c", &value );
       NodoPtr = InsertInTesta( NodoPtr, value );
       printList( NodoPtr );
       break;

    case 2:

      printf( "Inserisci lettera nodo : " );
      scanf( "\n%c", &value );
      CodaPtr = InsertCoda( CodaPtr, value );
      printList( CodaPtr );
      break;

    case 3:

      printf( "End of run. \n" );
      exit( 0 );

  }

  printf( "?  " );
  scanf( "%d", &choice );

}

 printf( "Invalid choice. \n" );

  return 0;
}

Nodo* NewLista( Nodo* TestaPtr ){

   Nodo* newptr;
   newptr = ( Nodo* )malloc( sizeof( Nodo ));

   if( newptr != NULL ){      // se c'è spazio disponibile

     TestaPtr = newptr;
     newptr->next = NULL;

   }

   else
     printf( "Spazio non disponibile. \n" );

   return TestaPtr;
}


Nodo* InsertInTesta( Nodo* TestaPtr, char value ){

      Nodo* newptr;
      newptr = ( Nodo* )malloc( sizeof( Nodo ));

      if( newptr != NULL ){

         newptr->next = TestaPtr;
         TestaPtr = newptr;
         newptr->data = value;

      }

      else
         printf( "Spazio non disponibile. \n" );

      return newptr;
}


void printList( Nodo* TestaPtr ){

   Nodo* temp = TestaPtr;

   while( temp != NULL ){

       printf( "------> %c ", temp->data );
       temp = temp->next;
   }
   puts("");
}

int RicercaValore( Nodo* TestaPtr, char value ){

     Nodo* temp = TestaPtr;
     int trovato = 0;

     while( temp != NULL ){

            if( temp->data == value )
                trovato = 1;
            temp = temp->next;
     }
     return trovato;
}

void Sort( Nodo* TestaPtr, char value ){

     Nodo* previousPtr = NULL;
     Nodo* currentPtr = TestaPtr;
     Nodo* newptr;
     Nodo* count;
     Nodo* temp = TestaPtr;

     newptr = ( Nodo* )malloc( sizeof( Nodo ));
     newptr->data = value;

  if( newptr != NULL && temp->next != NULL ) {

      for( count = currentPtr; count != NULL; count = count->next ){
           if( value > count->data ){
               previousPtr = count;
               currentPtr = count->next;
           }
      }

      if( currentPtr == NULL ){
          previousPtr->next = newptr;
          newptr->next = NULL;
      }
      else{
        previousPtr->next = newptr;
        newptr->next = currentPtr;
      }
 }
 else
   printf( "Spazio non disponibile. \n" );

}

int LenList( Nodo* TestaPtr ){

    Nodo* temp = TestaPtr;
    int count = 0;

    while( temp != NULL ){
      count = count + 1;
      temp = temp->next;
    }
    return count;
}

Nodo* InsertCoda( Nodo* TestaPtr, char value ){

  Nodo* newptr;
  static Nodo* temp = NULL;
  Nodo* CodaPtr;

  newptr = ( Nodo* )malloc( sizeof( Nodo ));

  if( TestaPtr == NULL ){
      TestaPtr = newptr;
      newptr->data = value;
      temp = TestaPtr;
      return temp;
  }
  else{
    CodaPtr = TestaPtr;
    while( CodaPtr->next ){
        CodaPtr = CodaPtr->next;
    }
    CodaPtr->next = newptr;
    newptr->data = value;
    return temp;
  }
}
