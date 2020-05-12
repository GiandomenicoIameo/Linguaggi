#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funzioni.h"

void prelevazioneLibri( Biblioteca_SL** Testa, Studente_SL** TestaStudente ) {

  int libroElenco, libroBiblioteca;
  int libroPrelevato, matricolaStudente, libroRestituito;
  char* nomeDelLibro;

  inputUtente( &nomeDelLibro, &matricolaStudente );
  libroBiblioteca = ricercaLibroBiblioteca( nomeDelLibro );

  if( !libroBiblioteca ) {
      aggiungiMatricola( matricolaStudente, TestaStudente );
      libroPrelevato = prelevaLibro( Testa, nomeDelLibro );
  if( libroPrelevato ) {
      AggiungiLibroStudente( matricolaStudente, nomeDelLibro, TestaStudente );
      printf( "\nIl libro %s è stato prelevato con successo... !!!\n\n", nomeDelLibro );
  } else {
      libroElenco = ricercaLibroElenco( nomeDelLibro, matricolaStudente, TestaStudente );
      if( libroElenco != -1 ) {
          puts( "\nHai gia' prelevato questo libro !!!\n" );
      } else {
          gestioneDeadlock( Testa, TestaStudente, nomeDelLibro, matricolaStudente );
          puts( "\nLibro ottenuto con successo !!! \n" );
      }
    }
  } else puts( "\nIl libro non è presente in biblioteca !!!\n" );
    free( nomeDelLibro );
}


void restituzioneLibri( Biblioteca_SL** Testa, Studente_SL** TestaStudente ) {

  int verifica, delete, libroBiblioteca, matricolaStudente;
  char* nomeDelLibro;

  inputUtente( &nomeDelLibro, &matricolaStudente );

  verifica = verificaMatricola( TestaStudente, matricolaStudente );
  if( verifica ) {
    libroBiblioteca = ricercaLibroBiblioteca( nomeDelLibro );
  if( libroBiblioteca ) {
    puts( "\nIl libro non è presente in biblioteca !!!\n" );
  } else {
    delete = restituireLibri( Testa, matricolaStudente, TestaStudente, nomeDelLibro );
    if( !delete ) {
      puts( "\nIl libro non è presente nell' elenco .... !!!\n" );
    } else if( delete == 1 ) {
      puts( "\nLibro restituito con successo ...!!!\n" );
    } else {
      puts( "\nNon vi sono libri disponibili, cancellazione matricola... !!!\n" );
    }
  }
  } else puts( "\nMatricola non trovata !!!\n" );
  free( nomeDelLibro );
}

static void buffer( void ) {

  while( getchar() != '\n' );
}

void instructions( void ) {

  puts( "\n"
      "	Inserisci una delle seguenti opzioni : \n\n"
      "1 per effettuare un prelievo di un libro\n"
      "2 per restituire un libro preso in prestito\n"
      "3 per visualizzare i libri\n"
      "4 per terminare il programma\n" );
}

static void inputUtente( char** libro, int* matricola ) {

  printf( "Inserire matricola di riconoscimento : " );
  scanf( "%d", matricola );

  buffer();

  *libro = ( char* )malloc( 30 * sizeof( char ) );
  printf( "Inserisci nome del libro : " );
  fgets( *libro, 24, stdin );

}

static void AggiungiLibroStudente( int matricola, char* libro, Studente_SL** TestaStudente ) {

  Studente_SL* tempStudente = *TestaStudente;
  Studente_SL* nodoMatricola = ricercaNodoMatricola( TestaStudente, matricola );
  int indice = 0;

  while( nodoMatricola->libroPrelevato[ indice ] != NULL ) {
    indice++;
  }
  nodoMatricola->libroPrelevato[ indice ] = libro;
  nodoMatricola->numeroLibriPrelevati++;
}

static void rimuoviLibroStudente( int matricola, char* libro, Studente_SL* TestaStudente, int indice ) {

  TestaStudente->libroPrelevato[ indice ] = " ";
  TestaStudente->numeroLibriPrelevati--;
}

static void aggiungiMatricola( int matricola, Studente_SL** TestaStudente ) {

  Studente_SL* temp = *TestaStudente;

  if( *TestaStudente == NULL ) {
      *TestaStudente = creaNodoStudente( matricola );
  } else {
      while( temp->next != NULL ) temp = temp->next;
      temp->next = creaNodoStudente( matricola );
  }
}

void stampaLibri( Biblioteca_SL** Testa ) {

  Biblioteca_SL* temp = *Testa;

  while( temp != NULL ) {
    printf( "%s", temp->titoloLibro );
    temp = temp->next;
  }
}

static Biblioteca_SL* creaNodo( char* titolo ) {

  Biblioteca_SL* nuovoPtr = ( Biblioteca_SL* )malloc( sizeof( Biblioteca_SL ) );
  strcpy( nuovoPtr->titoloLibro, titolo );
  nuovoPtr->next = NULL;

  return nuovoPtr;
}

static Studente_SL* creaNodoStudente( int matricola ) {

  Studente_SL* nuovoPtr = ( Studente_SL* )malloc( sizeof( Studente_SL ) );

  nuovoPtr->numeroLibriPrelevati++;
  nuovoPtr->matricola = matricola;
  nuovoPtr->libroPrelevato[ 30 ] = NULL;
  nuovoPtr->next = NULL;

  return nuovoPtr;
}

void inserimentoLibriDaFile( Biblioteca_SL** Testa, FILE* ptrLibri ) {

  char titolo[ 100 ];
  Biblioteca_SL* temp = NULL;
  ptrLibri = fopen( "biblioteca.dat", "r" );

  if( ptrLibri == NULL ) {
    puts( "Biblioteca chiusa" );
  }
  else {

    if( *Testa == NULL ) {

        fgets( titolo, 24, ptrLibri );
        *Testa = creaNodo( titolo );
    }
    temp = *Testa;
    fgets( titolo, 24, ptrLibri );

    while( !feof( ptrLibri ) ) {
        temp->next = creaNodo( titolo );

        fgets( titolo, 24, ptrLibri );
        temp = temp->next;
    }
  }
}

static int verificaMatricola( Studente_SL** TestaStudente, int matricola ) {

  Studente_SL* temp = *TestaStudente;

  while( temp != NULL ) {
    if( temp->matricola == matricola ) break;
    temp = temp->next;
  }

  if( temp == NULL ) {
    return 0;
  } else {
    return 1;
  }
}

static int prelevaLibro( Biblioteca_SL** Testa, char* libro ) {

    Biblioteca_SL* currentPtr = *Testa;
    Biblioteca_SL* previousPtr = NULL;
    int trovato = 0;

    while( currentPtr->next != NULL ) {
      if( !strcmp( libro, currentPtr->titoloLibro ) ) {
        trovato = 1;
        break;
      }
      previousPtr = currentPtr;
      currentPtr = currentPtr->next;
    }

    if( !strcmp( libro, currentPtr->titoloLibro ) ) {
      if( previousPtr == NULL ) {
          currentPtr = *Testa;
          free( currentPtr );
          *Testa = ( *Testa )->next;
      } else if( currentPtr->next == NULL ) {
          previousPtr->next = NULL;
          free( currentPtr );
      } else {
          previousPtr->next = currentPtr->next;
          free( currentPtr );
      }
    }
    return trovato;
}

static int ricercaLibroElenco( char* libro, int matricola, Studente_SL** TestaStudente ) {

  int indice = 0;
  Studente_SL* temp = *TestaStudente;

  while( temp->matricola != matricola  ) {
    temp = temp->next;
  }
  if( temp == NULL ) {
    return -1;
  }

  while( temp->libroPrelevato[ indice ] != NULL ) {
    if( !strcmp( temp->libroPrelevato[ indice ], libro ) ) {
      return indice;
    }
    indice++;
  }
  return -1;
}

static int ricercaLibroBiblioteca( char* libro ) {

  int value;
  char titolo[ 30 ];
  FILE* cfptr = fopen( "biblioteca.dat", "r" );

  if( cfptr == NULL ) {
    puts( "Impossibile aprire la biblioteca" );
  }
  else {
    fgets( titolo, 24, cfptr );
    value = strcmp( titolo, libro );

    while( !feof( cfptr ) && value ) {
      fgets( titolo, 24, cfptr );
      value = strcmp( titolo, libro );
    }
  }
  return value;
}

static void inserisciInBiblioteca( Biblioteca_SL** Testa, Biblioteca_SL** nodoSL ) {

  ( *nodoSL )->next = *Testa;
  *Testa = *nodoSL;
}

Studente_SL* ricercaNodoMatricola( Studente_SL** TestaStudente, int matricola ) {

  Studente_SL* temp = *TestaStudente;
  while( temp->matricola != matricola && temp != NULL ) {
    temp = temp->next;
  }
  return temp;
}

static void eliminaNodoStudente( Studente_SL** TestaStudente, Studente_SL* deleteNode ) {

  Studente_SL* currentPtr = *TestaStudente;
  Studente_SL* previousPtr = NULL;
  Studente_SL* delete = NULL;

  while( currentPtr != deleteNode && currentPtr->next != NULL ) {
    previousPtr = currentPtr;
    currentPtr = currentPtr->next;
  }

  if( previousPtr == NULL ) {
    delete = *TestaStudente;
    *TestaStudente = ( *TestaStudente )->next;
    free( delete );
  }
  else if( currentPtr->next == NULL ) {
    delete = currentPtr;
    previousPtr->next = NULL;
    free( delete );
  }
  else {
    delete = currentPtr;
    currentPtr = currentPtr->next;
    free( delete );
  }
}

static int restituireLibri( Biblioteca_SL** Testa, int matricola, Studente_SL** TestaStudente, char* libro ) {

    int indiceLibro = 0;
    Biblioteca_SL* newPtr = NULL;
    Studente_SL* studenteMatricola = NULL;

    studenteMatricola = ricercaNodoMatricola( TestaStudente, matricola );
    indiceLibro = ricercaLibroElenco( libro, matricola, TestaStudente );

    if( studenteMatricola->numeroLibriPrelevati && indiceLibro == -1 ) {
        return 0;

    } else if( studenteMatricola->numeroLibriPrelevati ) {

      rimuoviLibroStudente( matricola, libro, studenteMatricola, indiceLibro );
      newPtr = creaNodo( libro );
      inserisciInBiblioteca( Testa, &newPtr );
      return 1;
    } else {

      eliminaNodoStudente( TestaStudente, studenteMatricola );
      return 2;
    }
}

static void gestioneDeadlock( Biblioteca_SL** Testa, Studente_SL** TestaStudente, char* libro, int matricola ) {

  Studente_SL* tempStudente = *TestaStudente;
  int indice = 0;

  AggiungiLibroStudente( matricola, libro, TestaStudente );

  while( tempStudente != NULL ) {
    if( tempStudente->matricola == matricola ) continue;
      if( !strcmp( tempStudente->libroPrelevato[ indice ], libro ) ) break;
    indice++;
  }
  rimuoviLibroStudente( matricola, libro, tempStudente, indice );
}
