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
  Coda* coda = NULL;
  int idUtente, puntiUtente;
  Grafo* graph;
  int verticePartenza;
  int verticeDestinazione;
  int* predecessori;
  int* distanze;
  int log;
  int metaGettonata[ 24 ] = { 0 };

  Menu();

  return 0;
}
