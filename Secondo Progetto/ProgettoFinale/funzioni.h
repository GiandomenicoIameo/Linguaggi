#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 9999999
#define vertici 24

struct ListAdiacenza {
  int vertice;
  char citta[ vertici ];
  int costo;
  int prezzo;
  struct ListAdiacenza* next;
};

struct Grafo {
  int numeroVertici;
  struct ListAdiacenza** summit;
};

struct Coda {
  char citta[ vertici ];
  int vertice;
  int distanza;
  struct Coda* next;
};

struct prenotazioni {
  char username[ 20 ];
  int idPrenotazione;
  int punti;
  int costoTratta;
  char partenza[ 20 ];
  char destinazione[ 20 ];

  struct prenotazioni* next;
};

enum _bool { false = 0, true = 1 };
typedef enum _bool boolean;

struct utente{
	boolean isLogged;
	char username[ 20 ];
	char password[ 25 ];
	int punti;
};

typedef struct prenotazioni Prenotazioni;
typedef struct Coda Coda;
typedef struct Grafo Grafo;
typedef struct ListAdiacenza ListAdiacenza;
typedef struct utente Utente;

// ************ ACCOUNT UTENTE ***********

void Login( void );
Utente LoginUtente();
void RegistraUtente();
void VisualizzaPrenotazioni( Utente* utente );
int Search_in_File(char *fname, char *str );


// ******** GESTIONE PRENOTAZIONI ************

void Menu( void );
void prenotazioneEffettutata( Utente* utente, int* metaGettonata );
Prenotazioni* creaNodo( int identificativo, int costoTratta, char* partenza, char* destinazione, int punti );
void copiaPrenotazioni( Prenotazioni** Testa, char* username, FILE* cfPtr );
void eliminaNodo( Prenotazioni** Testa, int identificativo );
void incollaPrenotazioni( Prenotazioni** Testa, char* username, int costoTratta, int id );
void ModificaPrenotazioni( Prenotazioni** Testa, char* partenza, int id );
void stampaLista( Prenotazioni* Testa );
int controlloId( int id, char* username );
int controlloStringa( Prenotazioni* Testa, int id, char* string, int partDest );
void inserisciPrenotazione( char* partenza, char* destinazione, int id, int costoTratta, char* username, Utente* utente );
int controlloUtente( char* username );
int EmptyFile( char* username );
int ricercaMinimo( int* array, int size );
void prendiDaFile( Grafo** graph, char** citta );
int contaPunti( char* username );


//************ CREAZIONE GRAFO ***********************

void removeAllCoda( Coda** Testa );
int ricercaCosto( Grafo* graph, int verticeSrc, int verticeDst );
Coda* creaCoda( int vertice, int distanza );
void insertCoda( Coda** Testa, int vertice, int distanza );
int removeCoda( Coda** Testa );
void removeNodo( Coda** Testa, int vertice );
Grafo* creaLista( int vertice );
void insert( Grafo** graph , int vertice, int verticeDst, int costo, char* cittaDestinazione, int prezzo );
void rimuoviLato( Grafo** graph, int verticeSrc, int verticeDst );
ListAdiacenza* creaNodoGrafo( int vertice, int costo, char* citta, int prezzo );
void insertTesta( ListAdiacenza* nodePtr, ListAdiacenza** vertice );
int isDuplicate( ListAdiacenza* nodePtr, int costo );
void inizializzaArray( int* array, int size, int value );

// ********* CALCOLO PERCOSI MINIMI *****************

void calcoloDistanza( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void algoritmoDijkstra( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void inserimentoAdiacenze( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void AggiornaNodo( Coda** Testa, int vertice, int distanze );
int stampaArray( int* array, int size, int verticeDst );
void stampaPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze );
int ricercaMeta( char** citta, char* meta );
void buffer( void );
void stampaListaGrafo( Grafo* graph );

///********* CALCOLO COSTI MINIMI *********

void calcoloDistanzaCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void algoritmoDijkstraCosto( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void inserimentoAdiacenzeCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void AggiornaNodoCosti( Coda** Testa, int vertice, int distanze );
void stampaCostoPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze );
