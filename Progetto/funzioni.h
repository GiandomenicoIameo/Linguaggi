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
void rimuoviLibroStudente( int matricola, char* libro, Studente_SL* TestaStudente, int indice );
void aggiungiMatricola( int matricola, Studente_SL** TestaStudente );
void inputUtente( char** libro, int* matricola );
Biblioteca_SL* creaNodo( char* titolo );
Studente_SL* creaNodoStudente( int matricola );
void inserimentoLibriDaFile( Biblioteca_SL** Testa, FILE* ptrLibri );
void stampaLibri( Biblioteca_SL** Testa );
int prelevaLibro( Biblioteca_SL** Testa, char* libro );
int restituireLibri( Biblioteca_SL** Testa, int matricola, Studente_SL** TestaStudente, char* libro );
void instructions( void );
void AggiungiLibroStudente( int matricola, char* libro, Studente_SL** TestaStudente );
void buffer( void );
void gestioneDeadlock( Biblioteca_SL** Testa, Studente_SL** TestaStudente, char* libro, int matricola );
int verificaMatricola( Studente_SL** TestaStudente, int matricola );
int ricercaLibroElenco( char* libro, int matricola, Studente_SL** TestaStudente );
int ricercaLibroBiblioteca( char* libro );
void inserisciInBiblioteca( Biblioteca_SL** Testa, Biblioteca_SL** nodoSL );
void eliminaNodoStudente( Studente_SL** Testa, Studente_SL* deleteNode );
Studente_SL* ricercaNodoMatricola( Studente_SL** TestaStudente, int matricola );
