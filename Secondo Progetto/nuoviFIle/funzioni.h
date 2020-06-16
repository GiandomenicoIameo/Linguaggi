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
  int idUtente;
  int idPrenotazione;

  int costoTratta;

  char partenza[ 20 ];
  char destinazione[ 20 ];

  struct prenotazioni* next;
};

typedef struct prenotazioni Prenotazioni;
typedef struct Coda Coda;
typedef struct Grafo Grafo;
typedef struct ListAdiacenza ListAdiacenza;


// ******** GESTIONE PRENOTAZIONI ************

void Menu( void );
Prenotazioni* creaNodo( int identificativo, int costoTratta, char* partenza, char* destinazione );
void copiaPrenotazioni( Prenotazioni** Testa, int idUtente, FILE* cfPtr );
void eliminaNodo( Prenotazioni** Testa, int identificativo );
void incollaPrenotazioni( Prenotazioni** Testa, int idUtente );
void ModificaPrenotazioni( Prenotazioni** Testa, char* partenza, int id );
void stampaLista( Prenotazioni* Testa );
int controlloId( Prenotazioni* Testa, int id );
int controlloStringa( Prenotazioni* Testa, int id, char* string, int partDest );
void inserisciPrenotazione( char* partenza, char* destinazione, int id, int costoTratta, int idUtente );
int controlloUtente( int idUtente );
int EmptyFile( int idUtente, FILE** cfPtr );
int ricercaMinimo( int* array, int size );


//************ CREAZIONE GRAFO ***********************

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
void algoritmoDijkstraCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void inserimentoAdiacenzeCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori );
void AggiornaNodoCosti( Coda** Testa, int vertice, int distanze );
int stampaArray( int* array, int size, int verticeDst );
void stampaCostoPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze );
int ricercaMeta( char** citta, char* meta );
void buffer( void );
void stampaListaGrafo( Grafo* graph );
