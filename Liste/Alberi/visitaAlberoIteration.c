#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct treeNode {
  struct treeNode* leftPtr;
  struct treeNode* rightPtr;
  int data;
};

struct CodaNode {
  struct CodaNode* next;
  struct treeNode* tree;
};

typedef struct treeNode treeNode;
typedef struct CodaNode CodaNode;

treeNode* creaNodo( int data );
CodaNode* creaCoda( treeNode* albero );
void insertNode( treeNode** albero, int data );
CodaNode* Queue( CodaNode* Testa, treeNode* sottoAlbero );
CodaNode* Enqueue( CodaNode* Testa );
void visitaAlbero( treeNode* albero, CodaNode* Testa );
void alberiInseriti( CodaNode* Testa, treeNode* sottoAlberoS, treeNode* sottoAlberoD );

int main( void ) {

  // dichiarazione variabili
  int random;
  int choice;
  treeNode* root;
  CodaNode* coda;

  // inizializzazione variabili
  root = NULL;
  coda = NULL;
  srand( time( NULL ) );

  printf( "Inserisci numero nodi : " );
  scanf( "%d", &choice );

  for( int indice = 0; indice < choice; indice++ ) {
    random = rand() % 101;
    insertNode( &root, random );
  }

  puts( "" );
  visitaAlbero( root, coda );

  return 0;
}

treeNode* creaNodo( int data ) {

  treeNode* newPtr = ( treeNode* )malloc( sizeof( treeNode ) );

  newPtr->data = data;
  newPtr->leftPtr = NULL;
  newPtr->rightPtr = NULL;

  return newPtr;
}

CodaNode* creaCoda( treeNode* albero ) {

  CodaNode* newPtr = NULL;
  newPtr = ( CodaNode* )malloc( sizeof( CodaNode ) );

  newPtr->next = NULL;
  newPtr->tree = albero;

  return newPtr;
}

void insertNode( treeNode** albero, int data ) {

  if( *albero == NULL ) {
      *albero = creaNodo( data );
  }
  else {
    if( data < ( ( *albero )->data ) ) {
      insertNode( &( ( *albero )->leftPtr ), data );
    }
    else if( data > ( ( *albero )->data ) ) {
      insertNode( &( ( *albero )->rightPtr ), data );
    }
    // Nell' albero binario non vengono memorizzati i duplicati
  }
}

CodaNode* Queue( CodaNode* Testa, treeNode* sottoAlbero ) {

  CodaNode* tempTesta = NULL;

  if( Testa == NULL ) {
    Testa = creaCoda( sottoAlbero );
    alberiInseriti( Testa, sottoAlbero->leftPtr, sottoAlbero->rightPtr );

    return Testa;
  }
  else {
    tempTesta = Testa;
    while( tempTesta->next != NULL ) {
      tempTesta = tempTesta->next;
    }
    alberiInseriti( tempTesta, sottoAlbero->leftPtr, sottoAlbero->rightPtr );

    return Testa;
  }
}

CodaNode* Enqueue( CodaNode* Testa ) {

  CodaNode* delete = NULL;

  free( delete );
  delete = Testa;
  Testa = Testa->next;

  return Testa;
}

void visitaAlbero( treeNode* albero, CodaNode* Testa ) {

  Testa = Queue( Testa, albero );
  printf( "%d\n", Testa->tree->data );
  Testa = Enqueue( Testa );

  while( Testa != NULL ) {

    printf( "%d\n", Testa->tree->data );
    Testa = Queue( Testa, Testa->tree );
    Testa = Enqueue( Testa );
  }
}

void alberiInseriti( CodaNode* Testa, treeNode* sottoAlberoS, treeNode* sottoAlberoD ) {

  int True = sottoAlberoD && sottoAlberoS;

  switch( True ) {
    case 1 :
      Testa->next = creaCoda( sottoAlberoS );
      Testa->next->next = creaCoda( sottoAlberoD );
    break;

    case 0 :
      if( sottoAlberoS )
        Testa->next = creaCoda( sottoAlberoS );
      else if( sottoAlberoD )
        Testa->next = creaCoda( sottoAlberoD );
    break;
  }
}
