#include <stdio.h>

int main( void ) {
  
  int vettore[ 5 ];
  size_t indice;
  int numero, contatore = 0, trovato = 0;

  // caricamento nel vettore

  for( indice = 0; indice < 5; indice++ ) {
    printf( "vettore[ %ld ] = ",indice );
    scanf( "%d", &vettore[ indice ] );
  }

  puts( "" );

  printf( "Inserisci elemento da ricercare : " );
  scanf( "%d", &numero );

  for( indice = 0; indice < 5; indice++ ) {
    if( numero == vettore[ indice ] ) {
      trovato = 1;
      contatore = contatore + 1;
    }
  }

  if( trovato )
      printf( "Il valore desiderato e' stato contato in numero pari a : %d\n", contatore );
  else
      printf( "Il numero non e' stato trovato\n" );

  return 0;
}
