/* Cripta

Si scriva un programma C che accetti
un intero di quattro cifre. Sostituisca
ogni cifra con il risultato della somma
modulo dieci tra la cifra stessa e sette.
Infine scambi la prima cifra con la terza
e la seconda con la quarta.

Esempio di output:

Inserisci un numero di quattro cifre: 1278

Numero da crittografare: 1278
Numero crittografato: 4589

*/


#include <stdio.h>

int main( void ){

  int value;
  int cifra1, cifra2, cifra3, cifra4;

  do{

    printf( "Inserisci valore di 4 cifre : " );
    scanf( "%d", &value );

  }while( value < 1000 || value > 9999 );

  cifra4 = (( value % 10 ) + 7 ) % 10;
  value = value / 10;
  cifra3 = (( value % 10 ) + 7 ) % 10;
  value = value / 10;
  cifra2 = (( value % 10 ) + 7 ) % 10;
  value = value / 10;
  cifra1 = (( value % 10 ) + 7 ) % 10;

  printf( "%d%d%d%d\n", cifra3, cifra4, cifra1, cifra2 );

  return 0;
}
