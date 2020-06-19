#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Coda_SL {
  char* username;
  struct Coda_SL* next;
};

typedef struct Coda_SL Coda_SL;

Coda_SL* CreaNodo_SL( char* username, int size );
void InserisciInCoda_SL( Coda_SL** topPtr, char* username, int size );
void StampaCoda_SL( Coda_SL* topPtr );
void CancellazioneNodo( Coda_SL** topPtr, char* username );
void InserisciStringheArray( char** arrayStringhe, Coda_SL* topPtr );
void CancellazioneDuplicati( char** arrayStringhe, int* occorrenze, Coda_SL** topPtr );
int ConfrontaStringa( char** arrayStringhe, char* string );
void* AttraversaCoda_SL( Coda_SL* topPtr );

int main( void ) {

  Coda_SL* topPtr = NULL;
  char** arrayStringhe, *username;
  int* occorrenze;
  int numeroNodi, len;

  printf( "Inserisci il numero di nodi : " );
  scanf( "%d", &numeroNodi );

  for( int indice = 0; indice < numeroNodi; indice++ ) {
       printf( "Inserisci username : " );
       scanf( "%s", username );

       len = strlen( username );
       InserisciInCoda_SL( &topPtr, username, len );
  }
  puts( "\nLista Originale\n" );
  StampaCoda_SL( topPtr );

  arrayStringhe = AttraversaCoda_SL( topPtr );
  occorrenze = AttraversaCoda_SL( topPtr );

  InserisciStringheArray( arrayStringhe, topPtr );
  CancellazioneDuplicati( arrayStringhe, occorrenze, &topPtr );

  puts( "Lista modificata\n" );
  StampaCoda_SL( topPtr );

  return 0;
}

Coda_SL* CreaNodo_SL( char* username, int size ) {

   Coda_SL* nodoCoda = ( Coda_SL* )malloc( sizeof( Coda_SL ));

   nodoCoda->username = ( char* )calloc( size, sizeof( char ));
   strcpy( nodoCoda->username, username );

   nodoCoda->next = NULL;
   return nodoCoda;
}

void InserisciInCoda_SL( Coda_SL** topPtr, char* username, int size ) {

     Coda_SL* temp = *topPtr;

     if( *topPtr == NULL ) {
         *topPtr = CreaNodo_SL( username, size );
     }
     else
         InserisciInCoda_SL( &( temp->next ), username, size );
}

void StampaCoda_SL( Coda_SL* topPtr ) {

     while( topPtr != NULL ) {
        puts( topPtr->username );
        topPtr = topPtr->next;
     }
     puts( "" );
}

void CancellazioneNodo( Coda_SL** topPtr, char* username ) {

     Coda_SL* currentPtr = *topPtr;
     Coda_SL* previousPtr = NULL;
     Coda_SL* deletePtr;
     int value;

     value = strcmp( username, currentPtr->username );

     while( currentPtr != NULL && value ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
        value = strcmp( username, currentPtr->username );
     }

     if( !previousPtr ) {
       deletePtr = *topPtr;
       *topPtr = ( *topPtr )->next;
       free( deletePtr );
     }

     else if( currentPtr != NULL ) {
        deletePtr = currentPtr;
        previousPtr->next = currentPtr->next;
        free( deletePtr );
     }
}

void InserisciStringheArray( char** arrayStringhe, Coda_SL* topPtr ) {

     int indice = 0;

     while( topPtr != NULL ) {
        arrayStringhe[ indice ] = topPtr->username;
        topPtr = topPtr->next;
        indice = indice + 1;
     }
}

void CancellazioneDuplicati( char** arrayStringhe, int* occorrenze, Coda_SL** topPtr ) {

     Coda_SL* tempPtr = *topPtr;
     int indice;

     while( tempPtr != NULL ) {
        indice = ConfrontaStringa( arrayStringhe, tempPtr->username );
        occorrenze[ indice ]++;

        if( occorrenze[ indice ] > 1 )
            CancellazioneNodo( topPtr, tempPtr->username );
        tempPtr = tempPtr->next;
     }
}

int ConfrontaStringa( char** array, char* string ) {

    int value, indice;

    indice = 0;
    value = strcmp( array[ indice ], string );

    while( value ) {
      value = strcmp( array[ indice ], string );
      indice = indice + 1;
    }
    return indice;
}

void* AttraversaCoda_SL( Coda_SL* topPtr ) {

     int sizeArray = 0;
     void* array;

     while( topPtr != NULL ) {
       sizeArray = sizeArray + 1;
       topPtr = topPtr->next;
     }

    array = calloc( sizeArray, sizeof( void* ));
    return array;
}
