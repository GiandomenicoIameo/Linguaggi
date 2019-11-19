#include <stdio.h>

int main( void )
{
  int vettore[ 5 ];
  size_t i;
  int numero, contatore = 0, trovato = 0;

  // caricamento nel vettore

  for( i = 0; i < 5; i++ )
  {
    printf( "vettore[%ld] = ",i );
    scanf( "%d", &vettore[i] );
  }

  printf("\n");

  printf( "Inserisci elemento da ricercare : " );
  scanf( "%d", &numero );

  for( i = 0; i < 5; i++ )
  {
    if( numero == vettore[ i ] )
    {
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
