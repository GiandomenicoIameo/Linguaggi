#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Biblioteca_SL {
  char titoloLibro[ 50 ];
  struct Biblioteca_SL* next;
};

struct Studente_SL {
  int matricola;
  char *libroPrelevato[ 30 ];
  int numeroLibriPrelevati;
  struct Studente_SL* next;
};

typedef struct Biblioteca_SL Biblioteca_SL;
typedef struct Studente_SL Studente_SL;

void prelevazioneLibri( Biblioteca_SL** Testa, Studente_SL** TestaStudente );
void restituzioneLibri( Biblioteca_SL** Testa, Studente_SL** TestaStudente );
void inserimentoLibriDaFile( Biblioteca_SL** Testa, FILE* ptrLibri );
void instructions( void );
void stampaLibri( Biblioteca_SL** Testa );
static void rimuoviLibroStudente( int matricola, char* libro, Studente_SL* TestaStudente, int indice );
static void aggiungiMatricola( int matricola, Studente_SL** TestaStudente );
static void inputUtente( char** libro, int* matricola );
static Biblioteca_SL* creaNodo( char* titolo );
static Studente_SL* creaNodoStudente( int matricola );
static int prelevaLibro( Biblioteca_SL** Testa, char* libro );
static int restituireLibri( Biblioteca_SL** Testa, int matricola, Studente_SL** TestaStudente, char* libro );
static void AggiungiLibroStudente( int matricola, char* libro, Studente_SL** TestaStudente );
static void buffer( void );
static void gestioneDeadlock( Biblioteca_SL** Testa, Studente_SL** TestaStudente, char* libro, int matricola );
static int verificaMatricola( Studente_SL** TestaStudente, int matricola );
static int ricercaLibroElenco( char* libro, int matricola, Studente_SL** TestaStudente );
static int ricercaLibroBiblioteca( char* libro );
static void inserisciInBiblioteca( Biblioteca_SL** Testa, Biblioteca_SL** nodoSL );
static void eliminaNodoStudente( Studente_SL** Testa, Studente_SL* deleteNode );
static Studente_SL* ricercaNodoMatricola( Studente_SL** TestaStudente, int matricola );
