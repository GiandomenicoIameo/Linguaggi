#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funzioni.h"

int main( void ) {

  FILE* ptrLibri = NULL;
  Biblioteca_SL* Testa = NULL;
  Studente_SL* TestaStudente = NULL;
  int choice;

  inserimentoLibriDaFile( &Testa, ptrLibri );
  instructions();

  printf( "%s", "Inserisci opzione -->  " );
  scanf( "%d", &choice );

  while( choice != 4 ) {

    switch( choice ) {
      case 1 :
          prelevazioneLibri( &Testa, &TestaStudente );
      break;
      
      case 2 :
          restituzioneLibri( &Testa, &TestaStudente );
      break;

      case 3 :
          stampaLibri( &Testa );
      break;

      default :
          puts( "Scelta non valida" );
      break;
    }
    printf( "%s", "Inserisci opzione -->  " );
    scanf( "%d", &choice );
  }

  return 0;
}
