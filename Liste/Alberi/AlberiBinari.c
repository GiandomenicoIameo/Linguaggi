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
void PreOrder( treeNode* albero );
void InOrder( treeNode* albero );
void PostOrder( treeNode* albero );

int main( void ) {

  treeNode* root = NULL;
  int choice, random;

  srand( time( NULL ) );

  printf( "Inserisci numero nodi : " );
  scanf( "%d", &choice );

  for( int indice = 0; indice < choice; indice++ ) {
    random = rand() % 101;
    insertNode( &root, random );
  }

  PreOrder( root );
  puts( "" );
  InOrder( root );
  puts( "" );
  PostOrder( root );
  puts( "" );

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

void PreOrder( treeNode* albero ) {

  if( albero != NULL ) {
    printf( "%d ", albero->data );
    PreOrder( albero->leftPtr );
    PreOrder( albero->rightPtr );
  }
}

void InOrder( treeNode* albero ) {

  if( albero != NULL ) {
    PreOrder( albero->leftPtr );
    printf( "%d ", albero->data );
    PreOrder( albero->rightPtr );
  }
}

void PostOrder( treeNode* albero ) {

  if( albero != NULL ) {
    PreOrder( albero->leftPtr );
    PreOrder( albero->rightPtr );
    printf( "%d ", albero->data );
  }
}
