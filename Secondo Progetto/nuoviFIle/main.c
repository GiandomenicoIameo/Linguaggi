#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funzioni.h"

int main( void ) {

  Prenotazioni* Testa = NULL;
  FILE* cfPtr, *ptr = NULL;
  int choice, id, costoTratta;
  char partenza[ 20 ], destinazione[ 20 ];
  int value, ctrlId;
  int meta;
  int vertice = 0;
  Coda* coda = NULL;
  int idUtente, puntiUtente;
  char nodoDestinazione[ 20 ];
  Grafo* graph;
  int costo;
  int chilometri;
  int verticePartenza;
  int verticeDestinazione;
  int* predecessori;
  int* distanze;
  int metaGettonata[ 24 ] = { 0 };
  char* vettore[ 24 ] = { "Palermo", "Catania", "Trapani", "Lamezia",
                          "Taranto", "Cagliari", "Brindisi", "Bari",
                          "Napoli", "Roma", "Pescara", "Firenze", "Pisa",
                          "Bologna", "Genova", "Torino", "Milano", "Bergamo",
                          "Venezia", "Olbia", "Trieste", "Ancona", "Verona", "ReggioC"  };

  graph = creaLista( 24 );
  ptr = fopen( "MappaChilometri.dat", "r" );
  cfPtr = fopen( "MappaPercorsi.dat", "r" );

  fscanf( ptr, "%d", &costo );
  fscanf( cfPtr, "%s", nodoDestinazione );
  while( !feof( cfPtr ) ) {

      for( int indice = 0; indice < 24; indice++ ) {
          value = strcmp( vettore[ indice ], nodoDestinazione );
          if( !value ) {
              insert( &graph, indice, vertice, chilometri, nodoDestinazione, 0 );
          }
      }
      value = fscanf( cfPtr, "%d", &value );
      if( value == 1 ) {
        fseek( cfPtr, sizeof( char ), SEEK_CUR );
        fseek( ptr, sizeof( char ), SEEK_CUR );
        vertice = vertice + 1;
      }
      fscanf( ptr, "%d", &costo );
      fscanf( cfPtr, "%s", nodoDestinazione );
  }

  predecessori = ( int* )calloc( 24, sizeof( int ) );
  distanze = ( int* )calloc( 24, sizeof( int ) );

  for( int indice = 0; indice < 24; indice++ ) {
     distanze[ indice ] = INF;
     predecessori[ indice ] = -1;
  }

  Menu();
  scanf( "%d", &choice );


  while( choice != 0 ) {

   switch( choice ) {

    case 1 :
      printf( "Inserisci ID utente : " );
      scanf( "%d", &idUtente );

      if( EmptyFile( idUtente, &cfPtr ) ) {
          puts( "Non ci sono prenotazioni disponibili" );
          break;
      }
      copiaPrenotazioni( &Testa, idUtente, cfPtr );
      printf( "Inserisci ID prenotazione " );
      scanf( "%d", &id );

      ctrlId = controlloId( Testa, id );
      if( !ctrlId ) {
          puts( "ID non trovato" );
          break;
      }
      printf( "Inserisci nuova partenza : " );
      scanf( "%s", partenza );

      value = controlloStringa( Testa, id, partenza, 1 );
      if( value ) {
          puts( "Tratta Impossibile" );
          break;
      }

      ModificaPrenotazioni( &Testa, partenza, id );
      incollaPrenotazioni( &Testa, idUtente );

    break;

    case 2 :
      printf( "Inserisci ID utente : " );
      scanf( "%d", &idUtente );

      if( EmptyFile( idUtente, &cfPtr ) ) {
          puts( "Non ci sono prenotazioni disponibili" );
          break;
      }
      copiaPrenotazioni( &Testa, idUtente, cfPtr );
      printf( "Inserisci ID prenotazione " );
      scanf( "%d", &id );

      ctrlId = controlloId( Testa, id );
      if( !ctrlId ) {
          puts( " ID non trovato" );
          break;
      }
      printf( "Inserisci nuova destinazione : " );
      scanf( "%s", destinazione );

      value = controlloStringa( Testa, id, partenza, 1 );
      if( value ) {
          puts( "Tratta Impossibile" );
          break;
      }
      for( int indice = 0; indice < 24; indice++ ) {
          value = strcmp( destinazione, vettore[ indice ] );
          if( !value )
              metaGettonata[ indice ]++;
      }
      ModificaPrenotazioni( &Testa, partenza, id );
      incollaPrenotazioni( &Testa, idUtente );
    break;

    case 3 :
      printf( "Inserisci ID utente : " );
      scanf( "%d", &idUtente );

      if( EmptyFile( idUtente, &cfPtr ) ) {
          puts( "Non ci sono prenotazioni disponibili" );
          break;
      }
      printf( "Inserisci id utente : " );
      scanf( "%d", &idUtente );
      printf( "Inserisci ID prenotazione " );
      scanf( "%d", &id );

      copiaPrenotazioni( &Testa, idUtente, cfPtr );
      eliminaNodo( &Testa, id );
      incollaPrenotazioni( &Testa, idUtente );
    break;

    case 4 :
     meta = ricercaMinimo( metaGettonata, 24 );
     if( meta == -1 ) {
         puts( "Al momento non vi sono mete più gettonate, il sistema provvederà ad aggiornarle..\n" );
    }
    else {
         printf( "La meta più gettonata è : %s\n", vettore[ meta ] );
    }

    printf( "Inserisci id utente : " );
    scanf( "%d", &idUtente );
    value = controlloUtente( idUtente );

      if( value ) {
          copiaPrenotazioni( &Testa, idUtente, cfPtr );

          printf( "Inserisci ID prenotazione " );
          scanf( "%d", &id );
          ctrlId = controlloId( Testa, id );
          if( ctrlId ) {
              puts( "ID già presente" );
              break;
          }

          printf( "Inserisci Partenza : " );
          scanf( "%s", partenza );
          printf( "Inserisci Destinazione : " );
          scanf( "%s", destinazione );

          verticePartenza = ricercaMeta( vettore, partenza );
          verticeDestinazione = ricercaMeta( vettore, destinazione );

          algoritmoDijkstra( &coda, graph, verticePartenza, distanze, predecessori );
          printf( "Il percorso minimo per arrivare a destinazione è la tratta : " );
          stampaPercorsoMinimo( verticeDestinazione, verticePartenza, predecessori, vettore, distanze );
          puts( "\n" );
          costoTratta = ricercaCosto( graph, verticePartenza, verticeDestinazione );
          inserisciPrenotazione( partenza, destinazione, id, costoTratta, idUtente );

          for( int indice = 0; indice < 24; indice++ ) {
               value = strcmp( destinazione, vettore[ indice ] );
               if( !value ) {
                   metaGettonata[ indice ]++;
                   printf( "%d\n", indice );
              }
          }

      }
      else {
         printf( "Inserisci ID prenotazione " );
         scanf( "%d", &id );

         printf( "Inserisci Partenza : " );
         scanf( "%s", partenza );
         printf( "Inserisci Destinazione : " );
         scanf( "%s", destinazione );

         verticePartenza = ricercaMeta( vettore, partenza );
         verticeDestinazione = ricercaMeta( vettore, destinazione );

         algoritmoDijkstra( &coda, graph, verticePartenza, distanze, predecessori );
         printf( "Il percorso minimo per arrivare a destinazione è la tratta : " );
         stampaPercorsoMinimo( verticeDestinazione, verticePartenza, predecessori, vettore, distanze );
         puts( "\n" );
         costoTratta = ricercaCosto( graph, verticePartenza, verticeDestinazione );

         for( int indice = 0; indice < 24; indice++ ) {
              value = strcmp( destinazione, vettore[ indice ] );
              if( !value )
                  metaGettonata[ indice ]++;
         }

         inserisciPrenotazione( partenza, destinazione, id, costoTratta, idUtente );
      }
    break;
    default :
      puts( "Operazione non valida" );
  }
  Menu();
  scanf( "%d", &choice );
}

  return 0;
}
