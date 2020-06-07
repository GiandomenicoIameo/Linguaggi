#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creaMatrice( int numVertice, int*** grafo );
void inizializza( int numVertice, int** grafo );
void riempiMatrice( int numLato, int** grafo, int numVertice );
int visualizzaGradoEntrante( int** grafo, int numVertice, int vertice );
int visualizzaGradoUscente( int** grafo, int numVertice, int vertice );
void stampaMatrice( int numVertice, int** grafo );
void rimuoviLato( int** grafo, int verticeTesta, int verticeCoda );
void rimuoviVertice( int*** grafo, int numVertice );
void aggiungiLato( int** grafo, int verticeTesta, int verticeCoda );
void aggiungiVertice( int*** grafo, int numVertice );
int verificaAdiacenzaVertici( int** grafo, int verticeSrc, int verticeDst );
int grafoCompleto( int** grafo, int numVertice );

int main( void ) {

  int** grafo;
  int numVertice, numLato, grado, vertice;

  srand( time( NULL ) );

  printf( "Inserisci numero vertici : " );
  scanf( "%d", &numVertice );
  printf( "Inserisci numero lati : " );
  scanf( "%d", &numLato );

  creaMatrice( numVertice, &grafo );
  inizializza( numVertice, grafo );
  riempiMatrice( numLato, grafo, numVertice );
  stampaMatrice( numVertice, grafo );

  puts( "" );
  printf( "Inserisci vertice da esaminare : " );
  scanf( "%d", &vertice );

  rimuoviVertice( &grafo, numVertice );
  stampaMatrice( numVertice - 1, grafo );

  return 0;
}

void creaMatrice( int numVertice, int*** grafo ) {

  *grafo = ( int** )calloc( numVertice, sizeof( int* ) );
  for( int indice = 0; indice < numVertice; indice++ ) {
      ( *grafo )[ indice ] = ( int* )calloc( numVertice, sizeof( int ) );
  }
}

void inizializza( int numVertice, int** grafo ) {

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ )
      grafo[ indiceRow ][ indiceCol ] = 0;
  }
}

int visualizzaGradoEntrante( int** grafo, int numVertice, int vertice ) {

  int count = 0;

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ ) {
          if( indiceRow == vertice ) continue;
          if( grafo[ indiceRow ][ indiceCol ] == 1 && indiceCol == vertice ) count = count + 1;
    }
  }
  return count;
}

int visualizzaGradoUscente( int** grafo, int numVertice, int vertice ) {

  int count = 0;

  for( int indice = 0; indice < numVertice; indice++ ) {
      if( grafo[ vertice ][ indice ] == 1 ) count = count + 1;
    }
  return count;
}

void riempiMatrice( int numLato, int** grafo, int numVertice ) {

  int indice = 0;
  int randomCol, randomRow;

  while( indice < numLato ) {

      randomRow = rand() % numVertice;
      randomCol = rand() % numVertice;

      if( grafo[ randomRow ][ randomCol ] ) {
          indice--;
      } else {
          grafo[ randomRow ][ randomCol ] = 1;
      }
      indice = indice + 1;
  }
}

void stampaMatrice( int numVertice, int** grafo ) {

  for( int indice = 0; indice < numVertice; indice++ ) {
    printf(  "     [ %d ]", indice );
  }
  puts( "" );

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    printf( "[ %d ]  ", indiceRow );
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ ) {
      printf( "%d         ", grafo[ indiceRow ][ indiceCol ] );
    }
    puts( "" );
  }
}

void rimuoviLato( int** grafo, int verticeTesta, int verticeCoda ) {

    grafo[ verticeTesta ][ verticeCoda ] = 0;
}

void aggiungiLato( int** grafo, int verticeTesta, int verticeCoda ) {

    grafo[ verticeTesta ][ verticeCoda ] = 1;
}

int verificaAdiacenzaVertici( int** grafo, int verticeSrc, int verticeDst ) {

    return grafo[ verticeSrc ][ verticeDst ];
}

void aggiungiVertice( int*** grafo, int numVertice ) {

  *grafo = ( int** )realloc( *grafo, ( numVertice + 1 ) * sizeof( int* ) );
  for( int indice = 0; indice < numVertice + 1; indice++ ) {
      ( *grafo )[ indice ] = ( int* )realloc( ( *grafo )[ indice ], ( numVertice + 1 ) * sizeof( int ) );
  }
}

void rimuoviVertice( int*** grafo, int numVertice ) {

  int tempMatrix[ numVertice ][ numVertice ];

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ ) {
          tempMatrix[ indiceRow ][ indiceCol ] = ( *grafo )[ indiceRow ][ indiceCol ];
    }
  }

  *grafo = ( int** )realloc( *grafo, ( numVertice - 1 ) * sizeof( int* ) );
  for( int indice = 0; indice < ( numVertice - 1 ); indice++ ) {
      ( *grafo )[ indice ] = ( int* )realloc( ( *grafo )[ indice ], ( numVertice - 1 ) * sizeof( int ) );
  }

  for( int indiceRow = 0; indiceRow < ( numVertice - 1 ); indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < ( numVertice - 1 ); indiceCol++ ) {
          ( *grafo )[ indiceRow ][ indiceCol ] = tempMatrix[ indiceRow ][ indiceCol ];
    }
  }
}

int grafoCompleto( int** grafo, int numVertice ) {

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ ) {
      if( grafo[ indiceRow ][ indiceCol ] == 0 ) return 0;
    }
  }
  return 1;
}
