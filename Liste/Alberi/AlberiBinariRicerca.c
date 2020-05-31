#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct treeNode {
  struct treeNode* leftPtr;
  struct treeNode* rightPtr;
  int data;
};

typedef struct treeNode treeNode;

treeNode* creaNodo( int data );
void insertNode( treeNode** albero, int data );
int abrSearch( treeNode** albero, int key );
void PreOrder( treeNode* albero );

int main( void ) {

  treeNode* root = NULL;
  int choice, random;
  int found;

  srand( time( NULL ) );

  printf( "Inserisci numero nodi : " );
  scanf( "%d", &choice );

  for( int indice = 0; indice < choice; indice++ ) {
    random = rand() % 101;
    insertNode( &root, random );
  }
  PreOrder( root );
  puts( "" );

  printf( "Inserisci il nodo da ricercare : " );
  scanf( "%d", &choice );

  found = abrSearch( &root, choice );

  if( found ) {
    puts( "Il nodo è stato trovato" );
  }
  else {
    puts( "Il nodo non è trovato" );
  }



  return 0;
}

treeNode* creaNodo( int data ) {

  treeNode* newPtr = ( treeNode* )malloc( sizeof( treeNode ) );
  newPtr->data = data;
  newPtr->leftPtr = NULL;
  newPtr->rightPtr = NULL;

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
  }
}

int abrSearch( treeNode** albero, int key ) {

  if( *albero != NULL ) {
    if( key == ( *albero )->data )
       return 1;
    else if( *albero && key > ( *albero )->data  )
      return abrSearch( &( ( *albero )->rightPtr ), key );
    else
      return abrSearch( &( ( *albero )->leftPtr ), key );
  }
  else {
    return 0;
  }
}

void PreOrder( treeNode* albero ) {

  if( albero != NULL ) {
    printf( "%d ", albero->data );
    PreOrder( albero->leftPtr );
    PreOrder( albero->rightPtr );
  }
}
