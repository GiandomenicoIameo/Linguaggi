#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Nodo_Coda {
  int dato;
  struct Nodo_Coda* next;
};

typedef struct Nodo_Coda Nodo_Coda;

Nodo_Coda* creaNodo( int dato );
void insert( Nodo_Coda** Testa, int dato );
void removeTail( Nodo_Coda** Testa );
void creaMatrice( int*** grafo, int numVertice );
void inizializza( int** grafo, int numVertice );
void inizializzaArray( int* array, const int size, int value );
void stampaMatrice( int** grafo, int numVertice );
void riempiMatrice( int** grafo, int numLato, int numVertice );
void inserimentoAdiacenze( Nodo_Coda** Testa, int** grafo, int numVertice, int verticeSrc, int* arrayVisite, int* predecessori );
int verificaVertici( int** grafo, int numVertice, int verticeSrc );
void visitaInAmpiezza( int** grafo, int numVertice, int verticeSrc, Nodo_Coda** Testa, int* predecessori );
void stampaPercorso( int verticeSrc, int verticeDst, int* predecessori  );

int main( void ) {

  int** grafo;
  int* arrayVisite;
  int numVertice, numLato, totLati;
  Nodo_Coda* Testa = NULL;
  int* predecessori;

  do {

    printf( "Inserisci numero vertici : " );
    scanf( "%d", &numVertice );

    predecessori = ( int* )calloc( numVertice, sizeof( int ) );
    arrayVisite = ( int* )calloc( numVertice, sizeof( int ) );

    inizializzaArray( predecessori, numVertice, -1 );
    inizializzaArray( arrayVisite, numVertice, 0 );

    totLati = (( numVertice * numVertice ) - numVertice ) / 2;

    printf( "Inserisci numero lati : " );
    scanf( "%d", &numLato );

    if( numLato > totLati ) {
      printf( "Capienza superata ripeti !!\n\n" );
    }

  } while( numLato > totLati );

  creaMatrice( &grafo, numVertice );
  inizializza( grafo, numVertice );
  riempiMatrice( grafo, numLato, numVertice );
  stampaMatrice( grafo, numVertice );
  puts( "" );

  visitaInAmpiezza( grafo, numVertice, 0, &Testa, predecessori );
  
  return 0;
}

Nodo_Coda* creaNodo( int dato ) {

  Nodo_Coda* newPtr = ( Nodo_Coda* )malloc( sizeof( Nodo_Coda ) );
  newPtr->dato = dato;
  newPtr->next = NULL;

  return newPtr;
}

void insert( Nodo_Coda** Testa, int dato ) {

  Nodo_Coda* tempPtr = NULL;

  if( *Testa == NULL ) {
      *Testa = creaNodo( dato );
  }
  else {

    tempPtr = *Testa;
    while( tempPtr->next != NULL ) {
      tempPtr = tempPtr->next;
    }
    tempPtr->next = creaNodo( dato );
  }
}

void removeTail( Nodo_Coda** Testa ) {

  Nodo_Coda* deletePtr = NULL;
  int value;

  if( *Testa == NULL ) {
    return;
  }
  else {
    deletePtr = *Testa;
    *Testa = ( *Testa )->next;
    free( deletePtr );
  }
}

void creaMatrice( int*** grafo, int numVertice ) {

  *grafo = ( int** )calloc( numVertice, sizeof( int* ) );
  for( int indice = 0; indice < numVertice; indice++ ) {
      ( *grafo )[ indice ] = ( int* )calloc( numVertice, sizeof( int ) );
  }
}

void inizializza( int** grafo, int numVertice ) {

  for( int indiceRow = 0; indiceRow < numVertice; indiceRow++ ) {
    for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ )
      grafo[ indiceRow ][ indiceCol ] = 0;
  }
}

void inizializzaArray( int* array, const int size, int value ) {

  for( int indice = 0; indice < size; indice++ )
       array[ indice ] = value;
}

void stampaMatrice( int** grafo, int numVertice ) {

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

void riempiMatrice( int** grafo, int numLato, int numVertice ) {

  int indice = 0;
  int randomCol, randomRow;

  while( indice < numLato ) {

      randomRow = rand() % numVertice;
      randomCol = rand() % numVertice;

      if( grafo[ randomRow ][ randomCol ] ) {
          indice--;
      } else {
          grafo[ randomRow ][ randomCol ] = 1;
          grafo[ randomCol ][ randomRow ] = 1;
      }
      indice = indice + 1;
  }
}

void inserimentoAdiacenze( Nodo_Coda** Testa, int** grafo, int numVertice, int verticeSrc, int* arrayVisite, int* predecessori ) {

  if( arrayVisite[ verticeSrc ] == 0 ) {
      insert( Testa, verticeSrc );
      arrayVisite[ verticeSrc ] = 2; // nodo colorato di nero perché verranno inseriti in Coda
      // i vertici adiacenti
  }

  for( int indice = 0; indice < numVertice; indice++ ) {
    if( grafo[ verticeSrc ][ indice ] && !arrayVisite[ indice ] ) {
      insert( Testa, indice );
      arrayVisite[ indice ] = 1; // nodi colorati di grigio
      predecessori[ indice ] = verticeSrc;
    }
  }
}

void visitaInAmpiezza( int** grafo, int numVertice, int verticeSrc, Nodo_Coda** Testa, int* predecessori ) {

  Nodo_Coda* tempPtr = *Testa;
  int* arrayVisite = ( int* )calloc( numVertice, sizeof( int ) );
  int esistenzaElementi;

  if( verificaVertici( grafo, numVertice, verticeSrc ) )
      inserimentoAdiacenze( Testa, grafo, numVertice, verticeSrc, arrayVisite, predecessori );
  else {
    for( int indice = 0; indice < numVertice; indice++ ) {
         if( verificaVertici( grafo, numVertice, indice ) ) {
             inserimentoAdiacenze( Testa, grafo, numVertice, indice, arrayVisite, predecessori );
             break;
      }
    }
  }

  while( *Testa != NULL ) {
    if( arrayVisite[ ( *Testa )->dato ] == 2 ) {
      removeTail( Testa );
    }
    else if( arrayVisite[ ( *Testa )->dato ] == 1 ) {
      arrayVisite[ ( *Testa )->dato ] = 2;
      inserimentoAdiacenze( Testa, grafo, numVertice, ( *Testa )->dato, arrayVisite, predecessori );
    }
  }
  free( arrayVisite );
}

int verificaVertici( int** grafo, int numVertice, int verticeSrc ) {

  for( int indiceCol = 0; indiceCol < numVertice; indiceCol++ ) {
        if( grafo[ verticeSrc ][ indiceCol ] ) return 1;
  }
    return 0;
}

void stampaPercorso( int verticeSrc, int verticeDst, int* predecessori  ) {

     if( verticeSrc == verticeDst )
         printf( "%d\n", verticeSrc );
     else if( predecessori[ verticeDst ] == -1 ) {
         puts( "Non esiste alcun percorso" );
         exit( 0 );
     } else {
         stampaPercorso( verticeSrc, predecessori[ verticeDst ], predecessori );
         printf( "%d\n", verticeDst );
    }
}
