#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funzioni.h"

void Menu( void ) {

  printf( "0 ESCI\n");
  printf( "1 Modifica Prenotazione ( Partenza )\n" );
  printf( "2 Modifica Prenotazione ( Destinazione )\n" );
  printf( "3 Elimina Prenotazione\n" );
  printf( "4 Nuova Prenotazione\n" );
  printf( "---> " );

}

int ricercaMinimo( int* array, int size ) {

    int count = 0;
    for( int indice = 0; indice < 24; indice++ ) {
         if( array[ indice ] == 0 )
             count = count + 1;
    }

    if( count == 24 )
        return -1;

    count = 0;
    int minimo = array[ 0 ];

    for( int indice = 1; indice < size; indice++ ) {
         if( array[ indice ] < minimo ) {
             minimo = array[ indice ];
             count = indice;
         }
    }
    return count;
}

int EmptyFile( int idUtente, FILE** cfPtr ) {

  int value;

  char numero[ 5 ];
  char DButente[] = "dbutente";

  sprintf( numero, "%d", idUtente );
  strcat( DButente, numero );
  strcat( DButente, ".txt");

  *cfPtr = fopen( DButente, "r" );

  if( *cfPtr == NULL ) {
      return 1;
  }
  return 0;
}

int controlloUtente( int idUtente ) {

     FILE* cfPtr;

     char numero[ 5 ];
     char DButente[] = "dbutente";

     sprintf( numero, "%d", idUtente );
     strcat( DButente, numero );
     strcat( DButente, ".txt");

     cfPtr = fopen( DButente, "r" );
     if( cfPtr == NULL ) {
       return 0;
     }
     return 1;
}

void inserisciPrenotazione( char* partenza, char* destinazione, int id, int costoTratta, int idUtente ) {

    FILE* cfPtr;

    char numero[ 5 ];
    char DButente[] = "dbutente";

    sprintf( numero, "%d", idUtente );
    strcat( DButente, numero );
    strcat( DButente, ".txt");

    cfPtr = fopen( DButente, "a+" );
    if( cfPtr == NULL ) {
        puts( "Impossibile aprire file" );
    }
    else
      fprintf( cfPtr, "%d %s %s %d\n", id, partenza, destinazione, costoTratta );

    fclose( cfPtr );
}

int controlloStringa( Prenotazioni* Testa, int id, char* string, int partDest ) {

    int partenza;
    int destinazione;

    if( partDest ) {
      while( Testa != NULL ) {
         if( Testa->idPrenotazione == id ) {
             partenza = strcmp( Testa->destinazione, string );
             if( !partenza )
                 return 1;
         }
      Testa = Testa->next;
     }
     return 0;
    }
    else {
      while( Testa != NULL ) {
         if( Testa->idPrenotazione == id ) {
             destinazione = strcmp( Testa->partenza, string );
             if( !destinazione )
                 return 1;
         }
      Testa = Testa->next;
     }
     return 0;
    }
}

int controlloId( Prenotazioni* Testa, int id ) {

    while( Testa != NULL && Testa->idPrenotazione != id ) {
           Testa = Testa->next;
    }
    if( Testa != NULL )
        return 1;
    else
        return 0;
}

Prenotazioni* creaNodo( int identificativo, int costoTratta, char* partenza, char* destinazione ) {

  Prenotazioni* newPtr = ( Prenotazioni* )malloc( sizeof( Prenotazioni ) );

  newPtr->costoTratta = costoTratta;
  newPtr->idPrenotazione = identificativo;
  strcpy( newPtr->partenza, partenza );
  strcpy( newPtr->destinazione, destinazione );

  return newPtr;
}

void ModificaPrenotazioni( Prenotazioni** Testa, char* partenza, int id ) {

     Prenotazioni* tempTesta = *Testa;

     while( tempTesta != NULL ) {
        if( tempTesta->idPrenotazione == id ) {
            strcpy( tempTesta->partenza, partenza );
            break;
        }
        tempTesta = tempTesta->next;
    }
}

void copiaPrenotazioni( Prenotazioni** Testa, int idUtente, FILE* cfPtr ) {

  char partenza[ 20 ];
  char destinazione[ 20 ];
  int costoTratta, identificativo;
  Prenotazioni* temp = NULL;

  if( *Testa == NULL ) {
      fscanf( cfPtr, "%d%s%s%d", &identificativo, partenza, destinazione, &costoTratta );
      *Testa = creaNodo( identificativo, costoTratta, partenza, destinazione );
  }
  temp = *Testa;
  fscanf( cfPtr, "%d%s%s%d", &identificativo, partenza, destinazione, &costoTratta );

  while( !feof( cfPtr ) ) {
      temp->next = creaNodo( identificativo, costoTratta, partenza, destinazione );

      fscanf( cfPtr, "%d%s%s%d", &identificativo, partenza, destinazione, &costoTratta );
      temp = temp->next;
  }
}

void eliminaNodo( Prenotazioni** Testa, int identificativo ) {

     Prenotazioni* deletePtr;
     Prenotazioni* currentPtr;
     Prenotazioni* previousPtr;

     if( identificativo == ( *Testa )->idPrenotazione ) {
         deletePtr = *Testa;
         *Testa = ( *Testa )->next;
         free( deletePtr );
         return;
     }

     currentPtr = ( *Testa )->next;
     previousPtr = *Testa;

     while( currentPtr != NULL && identificativo != currentPtr->idPrenotazione ) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
     }

     if( currentPtr != NULL ) {
       deletePtr = currentPtr;
       previousPtr->next = currentPtr->next;
       free( deletePtr );
     }
}

void incollaPrenotazioni( Prenotazioni** Testa, int idUtente ) {

     Prenotazioni* tempTesta = *Testa;
     FILE* cfPtr;
     char numero[ 5 ];
     char DButente[] = "dbutente";

     sprintf( numero, "%d", idUtente );
     strcat( DButente, numero );
     strcat( DButente, ".txt");

     cfPtr = fopen( DButente, "w" );
     while( tempTesta != NULL ) {
          fprintf( cfPtr, "%d %s %s %d\n", tempTesta->idPrenotazione, tempTesta->partenza, tempTesta->destinazione, tempTesta->costoTratta );
          tempTesta = tempTesta->next;
     }

     if( EmptyFile( idUtente, &cfPtr ) )
         remove( DButente );
}
