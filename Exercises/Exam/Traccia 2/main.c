#include <stdio.h>
#include "funzioni.h"

int main( void ) {

  struct elem *top = nuovaLista();
  FILE *fptr = NULL;

  top = inputDaFile( top, fptr );
  stampaLista( top );
  top = inserisciNuovi( NULL, top );
  stampaLista( top );
  outputFile( top, fptr );

  return 0;
}
