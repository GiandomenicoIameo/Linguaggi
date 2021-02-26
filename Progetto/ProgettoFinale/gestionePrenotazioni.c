#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funzioni.h"

void prendiDaFile( Grafo** graph, char** citta ) {

  FILE* cfPtr, *ptrKm, *ptrCosti;
  int vertice, chilometri, value, prezzo;
  char nodoDestinazione[ 20 ];

  vertice = 0;
  ptrCosti = fopen( "MappaPrezzi.dat", "r" );
  ptrKm = fopen( "MappaChilometri.dat", "r" );
  cfPtr = fopen( "MappaPercorsi.dat", "r" );

  fscanf( ptrCosti, "%d", &prezzo );
  fscanf( ptrKm, "%d", &chilometri );
  fscanf( cfPtr, "%s", nodoDestinazione );

  while( !feof( cfPtr ) ) {

      for( int indice = 0; indice < 24; indice++ ) {
          value = strcmp( citta[ indice ], nodoDestinazione );
          if( !value ) {
              insert( graph, indice, vertice, chilometri, nodoDestinazione, prezzo );
          }
      }
      value = fscanf( cfPtr, "%d", &value );
      if( value == 1 ) {
        fseek( cfPtr, sizeof( char ), SEEK_CUR );
        fseek( ptrKm, sizeof( char ), SEEK_CUR );
        fseek( ptrCosti, sizeof( char ), SEEK_CUR );
        vertice = vertice + 1;
      }
      fscanf( ptrCosti, "%d", &prezzo );
      fscanf( ptrKm, "%d", &chilometri );
      fscanf( cfPtr, "%s", nodoDestinazione );
  }
}

void prenotazioneEffettutata( Utente* utente, int* metaGettonata ) {

  Prenotazioni* Testa = NULL;
  Coda* coda = NULL;
  Coda* Head = NULL;

  FILE* cfPtr;
  int choice, id, costoTratta;
  char partenza[ 20 ], destinazione[ 20 ];
  int value, ctrlId;
  int meta;
  char DButente[ 20 ] = "dbutente";
  int puntiUtente;
  Grafo* graph;
  int verticePartenza;
  int verticeDestinazione;
  int* predecessori, *predecessoriCosti;
  int* distanze, *distanzeCosti;
  char* vettoreCitta[ 24 ] = { "Palermo", "Catania", "Trapani", "Lamezia",
                          "Taranto", "Cagliari", "Brindisi", "Bari",
                          "Napoli", "Roma", "Pescara", "Firenze", "Pisa",
                          "Bologna", "Genova", "Torino", "Milano", "Bergamo",
                          "Venezia", "Olbia", "Trieste", "Ancona", "Verona", "ReggioC"  };

  graph = creaLista( 24 );
  prendiDaFile( &graph, vettoreCitta );

   printf( "1) Modifica prenotazioni ( Partenza )\n" );
   printf( "2) Modifica prenotazioni ( Destinazione )\n" );
   printf( "3) Elimina Prenotazione\n" );
   printf( "4) Inserisci nuova prenotazione\n" );
   printf( "5) Visualizza punti\n" );
   printf( "6) Termina\n");
   printf( "Inserisci opzione : " );
   scanf( "%d", &choice );

   switch( choice ) {

    case 1 :

      predecessoriCosti = ( int* )calloc( 24, sizeof( int ) );
      distanzeCosti = ( int* )calloc( 24, sizeof( int ) ),

      inizializzaArray( predecessoriCosti, 24, -1 );
      inizializzaArray( distanzeCosti, 24, INF );

      if( EmptyFile( utente->username ) ) {
          system("clear");
          puts( "" );
          puts( " !!! Non ci sono prenotazioni disponibili !!! " );
          puts( "\n" );
          break;
      }
      system( "clear" );
      copiaPrenotazioni( &Testa, utente->username, cfPtr );
      printf( "Inserisci ID prenotazione " );
      scanf( "%d", &id );

      ctrlId = controlloId( id, utente->username );
      if( !ctrlId ) {
          system( "clear" );
          puts( "!!! ID non trovato !!! " );
          puts( "" );
          break;
      }
      printf( "Inserisci nuova partenza : " );
      scanf( "%s", partenza );

      value = controlloStringa( Testa, id, partenza, 1 );
      if( value ) {
          system( "clear" ),
          puts( " !!! Tratta Impossibile !!! " );
          puts( "" );
          break;
      }

      ModificaPrenotazioni( &Testa, partenza, id );
      verticePartenza = ricercaMeta( vettoreCitta, partenza );
      algoritmoDijkstraCosto( &Head, graph, verticePartenza, distanzeCosti, predecessoriCosti );
      costoTratta = stampaArray( distanzeCosti, 24, verticeDestinazione );
      incollaPrenotazioni( &Testa, utente->username, costoTratta, id );

      system( "clear" );
      puts( "!! Tratta modificata con successo !!" );
      puts( "" );

    break;

    case 2 :

      predecessoriCosti = ( int* )calloc( 24, sizeof( int ) );
      distanzeCosti = ( int* )calloc( 24, sizeof( int ) ),

      inizializzaArray( predecessoriCosti, 24, -1 );
      inizializzaArray( distanzeCosti, 24, INF );

      if( EmptyFile( utente->username ) ) {
          system("clear");
          puts( "" );
          puts( " !!! Non ci sono prenotazioni disponibili !!! " );
          puts( "\n" );
          break;
      }
      system( "clear" );
      copiaPrenotazioni( &Testa, utente->username, cfPtr );
      printf( "Inserisci ID prenotazione " );
      scanf( "%d", &id );

      ctrlId = controlloId( id, utente->username );
      if( !ctrlId ) {
          system( "clear" );
          puts( " !!! ID non trovato !!! " );
          puts( "" );
          break;
      }
      printf( "Inserisci Partenza : " );
      scanf( "%s", partenza );
      printf( "Inserisci nuova destinazione : " );
      scanf( "%s", destinazione );

      value = controlloStringa( Testa, id, partenza, 1 );
      if( value ) {
          system( "clear" );
          puts( "Tratta Impossibile" );
          break;
      }
      for( int indice = 0; indice < 24; indice++ ) {
          value = strcmp( destinazione, vettoreCitta[ indice ] );
          if( !value ) {
              metaGettonata[ indice ] = metaGettonata[ indice ] + 1;
          }
      }

      ModificaPrenotazioni( &Testa, partenza, id );
      verticeDestinazione = ricercaMeta( vettoreCitta, destinazione );
      verticePartenza = ricercaMeta( vettoreCitta, partenza );
      algoritmoDijkstraCosto( &Head, graph, verticePartenza, distanzeCosti, predecessoriCosti );
      costoTratta = stampaArray( distanzeCosti, 24, verticeDestinazione );
      incollaPrenotazioni( &Testa, utente->username, costoTratta, id );

    break;

    case 3 :
      if( EmptyFile( utente->username ) ) {
          system( "clear" );
          puts( " !!! Non ci sono prenotazioni disponibili !!!! " );
          puts( "" );
          break;
      }
      else {
        system( "clear" );
        printf( "Inserisci ID prenotazione " );
        scanf( "%d", &id );

        ctrlId = controlloId( id, utente->username );
        if( !ctrlId ) {
            system( "clear" );
            puts( " !!! ID non trovato !!! " );
            puts( "" );
            break;
        }

        copiaPrenotazioni( &Testa, utente->username, cfPtr );
        eliminaNodo( &Testa, id );
        incollaPrenotazioni( &Testa, utente->username, 0, id );
        system( "clear" );
        puts( "!! Prenotazione ELiminata con Successo !!" );
        puts( "" );
    }
    break;

    case 4 :

     predecessoriCosti = ( int* )calloc( 24, sizeof( int ) );
     distanzeCosti = ( int* )calloc( 24, sizeof( int ) ),
     predecessori = ( int* )calloc( 24, sizeof( int ) ),
     distanze = ( int* )calloc( 24, sizeof( int ) ),

     inizializzaArray( predecessoriCosti, 24, -1 );
     inizializzaArray( distanzeCosti, 24, INF );
     inizializzaArray( distanze, 24, INF );
     inizializzaArray( predecessori, 24, INF );

     system( "clear" );
     meta = ricercaMinimo( metaGettonata, 24 );
     printf( " !!! La meta più gettonata è : %s !!!!\n", vettoreCitta[ meta ] );
     puts( "" );

      value = controlloUtente( utente->username );

      if( !value ) {
          copiaPrenotazioni( &Testa, utente->username, cfPtr );

          printf( "Inserisci ID prenotazione " );
          scanf( "%d", &id );
          ctrlId = controlloId( id, utente->username );
          if( ctrlId ) {
              system( "clear" );
              puts( " !!! ID già presente !!! " );
              puts( "" );
              break;
          }

          printf( "Inserisci Partenza : " );
          scanf( "%s", partenza );
          printf( "Inserisci Destinazione : " );
          scanf( "%s", destinazione );

          verticePartenza = ricercaMeta( vettoreCitta, partenza );
          verticeDestinazione = ricercaMeta( vettoreCitta, destinazione );

          algoritmoDijkstra( &coda, graph, verticePartenza, distanze, predecessori );
          algoritmoDijkstraCosto( &Head, graph, verticePartenza, distanzeCosti, predecessoriCosti );

          costoTratta = stampaArray( distanzeCosti, 24, verticeDestinazione );
          if( costoTratta != INF ) {
              inserisciPrenotazione( partenza, destinazione, id, costoTratta, utente->username, utente );
          }

          system( "clear" );
          printf( "Il percorso minimo per arrivare a destinazione è la tratta : " );
          stampaPercorsoMinimo( verticeDestinazione, verticePartenza, predecessori, vettoreCitta, distanze );
          printf( "Mentre la tratta più economica è : " );
          stampaCostoPercorsoMinimo( verticeDestinazione, verticePartenza, predecessoriCosti, vettoreCitta, distanzeCosti );
          puts( "" );

          for( int indice = 0; indice < 24; indice++ ) {
               value = strcmp( destinazione, vettoreCitta[ indice ] );
               if( !value ) {
                   metaGettonata[ indice ] = metaGettonata[ indice ] + 1;
              }
          }
      }
      else {

         printf( "Inserisci ID prenotazione " );
         scanf( "%d", &id );

         ctrlId = controlloId( id, utente->username );
         if( ctrlId ) {
           system( "clear" );
           puts( "!!! ID già presente !!!" );
           puts( "" );
           break;
         }

         printf( "Inserisci Partenza : " );
         scanf( "%s", partenza );
         printf( "Inserisci Destinazione : " );
         scanf( "%s", destinazione );

         system( "clear" );
         verticePartenza = ricercaMeta( vettoreCitta, partenza );
         verticeDestinazione = ricercaMeta( vettoreCitta, destinazione );

         algoritmoDijkstra( &coda, graph, verticePartenza, distanze, predecessori );
         algoritmoDijkstraCosto( &Head, graph, verticePartenza, distanzeCosti, predecessoriCosti );

         system( "clear" ),
         printf( "Il percorso minimo per arrivare a destinazione è la tratta : " );
         stampaPercorsoMinimo( verticeDestinazione, verticePartenza, predecessori, vettoreCitta, distanze );
         printf( "Mentre la tratta più economica è : " );
         stampaCostoPercorsoMinimo( verticeDestinazione, verticePartenza, predecessoriCosti, vettoreCitta, distanzeCosti );
         puts( "" );

         for( int indice = 0; indice < 24; indice++ ) {
              value = strcmp( destinazione, vettoreCitta[ indice ] );
              if( !value )
                  metaGettonata[ indice ] = metaGettonata[ indice ] + 1;
         }
         costoTratta = stampaArray( distanzeCosti, 24, verticeDestinazione );
         if( costoTratta != INF ) {
              inserisciPrenotazione( partenza, destinazione, id, costoTratta, utente->username, utente );
         }
      }
    break;
    case 5 :
      utente->punti = contaPunti( utente->username );
      system( "clear" );
      printf( " !!! Hai un totale di %d punti !!! \n", utente->punti );
      puts( "" );
    break;
    default :
      puts( "Operazione non valida" );
  }
  puts( "" );
}

int contaPunti( char* username ) {

    FILE* cfPtr;
    char start[ 20 ], end[ 20 ];
    int prezzo, punti, id, value;
    char DButente[ 20 ] = "dbutente";
    strcat( DButente, username );
    strcat( DButente, ".txt" );

    cfPtr = fopen( DButente, "r" );

    if( cfPtr == NULL ) {
      return 0;
    }
    fscanf( cfPtr, "%d", &id );
    if( value == EOF ) {
        return 1;
    }

    fscanf( cfPtr, "%d %s %s %d %d", &id, start, end, &prezzo, &punti );
    while( !feof( cfPtr ) ) {
      fscanf( cfPtr, "%d %s %s %d %d", &id, start, end, &prezzo, &punti );
    }
    return punti;
}


struct utente LoginUtente(){

	FILE *dbUtenti;
	Utente user;
	Utente tmpUser;
	int res;

	// apre il file
	dbUtenti = fopen("dbUtenti.txt", "a+");

	if(dbUtenti == NULL) {
		dbUtenti = fopen("dbUtenti.txt", "w+");
		system( "clear" );
		printf( "** Impossibile effettuare il login **\n" );
		exit( 0 );
	}

	printf( "Username: " );
	scanf( "%s", user.username );
	printf( "Password: " );
	scanf( "%s", user.password );

	while( 1 ){
		res = fscanf( dbUtenti,"%s %s %d\n", &tmpUser.username, &tmpUser.password, &tmpUser.punti );
		if(res != EOF){
			if(strcmp(user.username, tmpUser.username) == 0){ //Se == 0 stringhe uguali
				if(strcmp(user.password, tmpUser.password) == 0){
					system("clear");
					printf("** Login effettuato con successo **\n");
					printf("\n Felice di rivederti %s !\n\n", tmpUser.username, tmpUser.punti);
					user.isLogged = true;
					break;
				}
			}
		} else {
			system("clear");
			printf("** Impossibile effettuare il login **\n");
			exit( 0 );
		}
	}
	return user;
}

void RegistraUtente(){

	FILE *dbUtenti;
	Utente utente;

	// apre il file
	dbUtenti = fopen( "dbUtenti.txt", "a+" );

	if(dbUtenti == NULL) {
		dbUtenti = fopen( "dbUtenti.txt", "w+" );
	}

	printf("** Registrazione Utente **\n\n");
	printf("Inserire Username: ");
	scanf("%s", utente.username);

	printf("Inserire Password: ");
	scanf("%s", utente.password);

  utente.punti = 0;

	while( Search_in_File( "dbUtenti.txt", utente.username ) ) {
		system("clear");
		printf("** Username non disponibile, riprova **\n\n");
		printf("Inserire Username: ");
		scanf("%s", utente.username);
	}

	fprintf( dbUtenti, "%s %s %d\n", utente.username, utente.password, 0 );

	system( "clear" );
	printf( "\n **Registrazione effettuata **\n\n" );
	fclose( dbUtenti );

}

int Search_in_File(char *fname, char *strUsername ) {

	FILE *fp;
	int user_line_num = 1;
	int psw_line_num = 1;
	int find_result = 0;
	char temp[ 512 ];

	if((fp = fopen(fname, "r")) == NULL) {
		return(-1);
	}

	while(fgets(temp, sizeof(strUsername), fp) != NULL) {
		if((strstr(temp, strUsername)) != NULL) {
			printf("A match found on line: %d\n", user_line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		user_line_num++;
	}

	if(find_result == 0) {
		printf("\nUtente non trovato\n");
	}
	if(fp) {
		fclose(fp);
	}
	return(find_result);
}

void Menu(){

	int opz, opzPrenotazione;
	Utente loggedUser;
	Prenotazioni myPrenotazione;
	loggedUser.isLogged = false;
  int metaGettonata[ 24 ] = { 0 };


  printf("Scegliere una delle seguenti opzioni:\n");

  if( loggedUser.isLogged == false ){
  	printf("1) Effettuare il Login\n");
  	printf("2) Effettuare una Registrazione\n");
  } else {
  	printf("3) Visualizza le prenotazioni attive\n");
  	printf("4) Effettua una prenotazione\n");
  	printf("5) Effettua il logout\n");
  }

  printf("6) Termina\n");
  printf("Esegui operazione numero: ");
  scanf( "%d" ,&opz );

	while( opz != 6 ) {

		switch( opz ){

			case 1 :
				if( loggedUser.isLogged == false ){

					system( "clear" );
					printf("** Effettua Login **\n\n");
					loggedUser = LoginUtente();

				} else {

					system( "clear" );
					printf( "** Utente loggato **\n\n" );

				}
			break;
			case 2 :

				if( loggedUser.isLogged == false ){
					system("clear");
					RegistraUtente();
				} else {
					system("clear");
				}

				break;
        case 3:

          system( "clear" );
					VisualizzaPrenotazioni( &loggedUser );
          puts( "" );

				break;
			case 4 :

					system( "clear" );
          prenotazioneEffettutata( &loggedUser, metaGettonata );

				break;
			case 5 :
				system("clear");

				if( loggedUser.isLogged == true ){
					printf( "** Hai effettuato il logout **\n\n" );
					loggedUser.isLogged = false;
				} else {
					system( "clear" );
				}

				break;
			case 6:
				exit( 0 );
	    break;
			default:
				system( "clear" );
				printf("Operazione non valida\n");
		}
    printf("Scegliere una delle seguenti opzioni:\n");

		if( loggedUser.isLogged == false ){
			printf("1) Effettuare il Login\n");
			printf("2) Effettuare una Registrazione\n");
		} else {
			printf("3) Visualizza le prenotazioni attive\n");
			printf("4) Effettua una prenotazione\n");
			printf("5) Effettua il logout\n");
		}
     printf("6) Termina\n");
  	 printf("Esegui operazione numero: ");
	   scanf( "%d" ,&opz );

	}
}

int ricercaMinimo( int* array, int size ) {

    int count = 0;
    int massimo = array[ 0 ];

    for( int indice = 1; indice < size; indice++ ) {
         if( array[ indice ] > massimo ) {
             massimo = array[ indice ];
             count = indice;
         }
    }
    return count;
}

int controlloUtente( char* username ) {

    FILE* cfPtr;
    char DBUtente[ 20 ] = "dbutene";
    strcat( DBUtente, username );
    strcat( DBUtente, ".txt" );

    cfPtr = fopen( DBUtente, "r" );

    if( cfPtr == NULL ) {
      return 1;
    }
    return 0;
}


int EmptyFile( char* username ) {

  int value;
  char DButente[ 20 ] = "dbutente";
  FILE* cfPtr;

  strcat( DButente, username );
  strcat( DButente, ".txt");

  cfPtr = fopen( DButente, "r" );
  if( cfPtr == NULL ) {
    return 1;
  }

  value = fscanf( cfPtr, "%d", &value );
  if( value == EOF ) {
      return 1;
  }
  return 0;
}

void VisualizzaPrenotazioni( Utente* utente ) {

     FILE* cfPtr;

     char DButente[ 20 ] = "dbutente";
     char partenza[ 20 ], destinazione[ 20 ];
     int prezzo, identificativo;

     strcat( DButente, utente->username );
     strcat( DButente, ".txt" );
     if( EmptyFile( utente->username ) ) {

         system( "clear" );
         puts( " !!! Non ci sono prenotazioni disponibili !!! " );
         puts( "" );
     }
     else {

       cfPtr = fopen( DButente, "r" );
       fscanf( cfPtr, "%d %s %s %d %d", &identificativo, partenza, destinazione, &prezzo, &utente->punti );

       while( !feof( cfPtr ) ) {
            printf( "ID Prenotazione : %d\n", identificativo );
            printf( "Partenza : %s\n", partenza );
            printf( "Destinazione : %s\n", destinazione );
            printf( "Prezzo : %d€\n", prezzo );
            fscanf( cfPtr, "%d %s %s %d %d", &identificativo, partenza, destinazione, &prezzo, &utente->punti );
            puts( "" );
       }
       printf( "Il totale dei punti è : %d\n\n", utente->punti );
       fclose( cfPtr );
   }
}

void inserisciPrenotazione( char* partenza, char* destinazione, int id, int costoTratta, char* username, Utente* utente ) {

    FILE* cfPtr, *ptrDB;
    char DButente[ 20 ] = "dbutente";
    char start[ 20 ], end[ 20 ];
    int value, punti = 0, ident, sconto;
    int doSconto = 0, prezzo;

    strcat( DButente, username );
    strcat( DButente, ".txt");

    cfPtr = fopen( DButente, "a+" );

    if( cfPtr == NULL ) {
       cfPtr = fopen( DButente, "w" );
       utente->punti = utente->punti + costoTratta * 0.1;
       fprintf( cfPtr, "%d %s %s %d %d\n", id, partenza, destinazione, costoTratta, utente->punti );
    }
    else {

      ptrDB = fopen( DButente, "r" );
      fscanf( ptrDB, "%d %s %s %d %d\n", &ident, start, end, &prezzo, &utente->punti );
      while( !feof( ptrDB ) ) {
         fscanf( ptrDB, "%d %s %s %d %d\n", &ident, start, end, &prezzo, &utente->punti );
      }

      if( utente->punti != 0 ) {

         if( utente->punti >= 5 && utente->punti < 10 ) {

               do {
                    puts( "" );
                    printf( "Hai diritto ad uno sconto del 5%, applicarlo ?\n" );
                    printf( "0) No\n" );
                    printf( "1) Si\n" );
                    printf( "Inserisci --> " );
                    scanf( "%d", &doSconto );

               } while( doSconto != 0 && doSconto != 1 );

                if( doSconto ) {
                   system( "clear" );
                   printf( "!!! Lo sconto è stato applicato !!!\n" );
                   sconto = ( costoTratta * 5 ) / 100;
                   costoTratta = costoTratta - sconto;
                   utente->punti -= 5;
                }
                else {
                  printf( "Lo sconto non verrà applicato\n" );
                  utente->punti = utente->punti + ( costoTratta * 0.1 );
                }
            }

            else if( utente->punti >= 10 && utente->punti < 15 ) {

            do {
                 puts( "" );
                 printf( "Hai diritto ad uno sconto del 10%, applicarlo ?\n" );
                 printf( "0) No\n" );
                 printf( "1) Si\n" );
                 printf( "Inserisci --> " );
                 scanf( "%d", &doSconto );

            } while( doSconto != 0 && doSconto != 1 );

              if( doSconto ) {
                system( "clear" );
                printf( "!!! Lo sconto è stato applicato !!!\n" );
                sconto = ( costoTratta * 10 ) / 100;
                costoTratta = costoTratta - sconto;
                utente->punti -= 10;
              }
              else {
                  printf( "Lo sconto non verrà applicato\n" );
                  utente->punti = utente->punti + ( costoTratta / 10 );
              }
            }

            else if( punti >= 15 ) {

             do {
                 puts( "" );
                 printf( "Hai diritto ad uno sconto del 15%, applicarlo ?\n" );
                 printf( "0) No\n" );
                 printf( "1) Si\n" );
                 printf( "Inserisci --> " );
                 scanf( "%d", &doSconto );

            } while( doSconto != 0 && doSconto != 1 );

              if( doSconto ) {
                system( "clear" );
                printf( "!!! Lo scon è stato applicato !!!\n" );
                sconto = ( costoTratta * 15 ) / 100;
                costoTratta = costoTratta - sconto;
                utente->punti -= 15;
              }
              else {
                  printf( "Lo sconto non verrà applicato\n" );
                  utente->punti = utente->punti + ( costoTratta / 10 );
              }
            } else {
              utente->punti = utente->punti + ( costoTratta / 10 );
            }
          } else {
              utente->punti = utente->punti + ( costoTratta / 10 );
          }
      }

      fprintf( cfPtr, "%d %s %s %d %d\n", id, partenza, destinazione, costoTratta, utente->punti );
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

int controlloId( int id, char* username ) {

    FILE* cfPtr;
    char DBUtente[ 20 ] = "dbutente";
    char start[ 20 ], end[ 20 ];
    int punti, ident, prezzo;
    strcat( DBUtente, username );
    strcat( DBUtente, ".txt" );

    cfPtr = fopen( DBUtente, "r" );
    if( cfPtr == NULL )
        return 0;

    fscanf( cfPtr, "%d %s %s %d %d", &ident, start, end, &prezzo, &punti );
    while( !feof( cfPtr ) ) {
           if( ident == id )
               return 1;
           fscanf( cfPtr, "%d %s %s %d %d", &ident, start, end, &prezzo, &punti );
    }
    return 0;
}

Prenotazioni* creaNodo( int identificativo, int costoTratta, char* partenza, char* destinazione, int punti ) {

  Prenotazioni* newPtr = ( Prenotazioni* )malloc( sizeof( Prenotazioni ) );

  newPtr->costoTratta = costoTratta;
  newPtr->idPrenotazione = identificativo;
  strcpy( newPtr->partenza, partenza );
  newPtr->punti = punti;
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

void copiaPrenotazioni( Prenotazioni** Testa, char* username, FILE* cfPtr ) {

  char partenza[ 20 ];
  char destinazione[ 20 ];
  int costoTratta, identificativo, punti;
  Prenotazioni* temp = NULL;
  char DButente[ 20 ] = "dbutente";

  strcat( DButente, username );
  strcat( DButente, ".txt" );

  cfPtr = fopen( DButente, "r" );

  if( *Testa == NULL ) {
      fscanf( cfPtr, "%d%s%s%d%d", &identificativo, partenza, destinazione, &costoTratta, &punti );
      *Testa = creaNodo( identificativo, costoTratta, partenza, destinazione, punti );
  }
  temp = *Testa;
  fscanf( cfPtr, "%d%s%s%d%d", &identificativo, partenza, destinazione, &costoTratta, &punti );

  while( !feof( cfPtr ) ) {
      temp->next = creaNodo( identificativo, costoTratta, partenza, destinazione, punti );

      fscanf( cfPtr, "%d%s%s%d%d", &identificativo, partenza, destinazione, &costoTratta, &punti );
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

void incollaPrenotazioni( Prenotazioni** Testa, char* username, int costoTratta, int id ) {

     Prenotazioni* tempTesta = *Testa;
     FILE* cfPtr;
     char DButente[ 20 ] = "dbutente";

     strcat( DButente, username );
     strcat( DButente, ".txt");

     cfPtr = fopen( DButente, "w" );
     while( tempTesta != NULL ) {
       if( costoTratta == 0 ) {
           fprintf( cfPtr, "%d %s %s %d %d\n", tempTesta->idPrenotazione, tempTesta->partenza, tempTesta->destinazione, tempTesta->costoTratta, tempTesta->punti );
       }
       if( tempTesta->idPrenotazione == id )
            fprintf( cfPtr, "%d %s %s %d %d\n", tempTesta->idPrenotazione, tempTesta->partenza, tempTesta->destinazione, costoTratta, tempTesta->punti );
       else
            fprintf( cfPtr, "%d %s %s %d %d\n", tempTesta->idPrenotazione, tempTesta->partenza, tempTesta->destinazione, tempTesta->costoTratta, tempTesta->punti );
       tempTesta = tempTesta->next;
     }
     system( "clear" );
     puts( " !!! Partenza modificata con successo !!!" );
     puts( "" );
     fclose( cfPtr );
}
