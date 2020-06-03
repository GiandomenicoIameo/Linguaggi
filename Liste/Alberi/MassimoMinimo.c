#include <stdio.h>
#include <stdlib.h>

struct treeNode {
  struct treeNode* leftPtr;
  int data;
  struct treeNode* rightPtr;
};

typedef struct treeNode treeNode;

treeNode* creaNodo( int data );
void insert( treeNode** albero, int data );
void InOrder( treeNode* albero );
treeNode* searchMin( treeNode* albero );
treeNode* searchMax( treeNode* albero );

int main( void ) {

  treeNode* root = NULL;
  treeNode* max, *min;
  int choice, value;

  printf( "Inserisci il numero di nodi da inserire : " );
  scanf( "%d", &choice );

  for( int indice = 0; indice < choice; indice++ ) {
    printf( "Inserisci elemento ---> " );
    scanf( "%d", &value );
    insert( &root, value );
  }
  InOrder( root );
  puts( "" );

  printf( "Inserisci elemento " );
  scanf( "%d", &value );
 
  max = searchMax( root );
  min = searchMin( root );

  printf( "%d\n", max->data );
  printf( "%d\n", min->data );
 
  return 0;
 }
 
 
treeNode* creaNodo( int data ) {

  treeNode* newPtr;
  newPtr = ( treeNode* )malloc( sizeof( treeNode ) );

  newPtr->leftPtr = NULL;
  newPtr->data = data;
  newPtr->rightPtr = NULL;

  return newPtr;
}

void insert( treeNode** albero, int data ) {

  if( *albero == NULL ) {
      *albero = creaNodo( data );
  } else {

    if( data > ( *albero )->data )
      insert( &( ( *albero )->rightPtr ), data );
    else if( data < ( *albero )->data )
      insert( &( ( *albero )->leftPtr ), data );
  }
}

void InOrder( treeNode* albero ) {

  if( albero != NULL ) {
    InOrder( albero->rightPtr );
    printf( "%d ", albero->data );
    InOrder( albero->leftPtr );
  }
}

treeNode* searchMin( treeNode* albero ) {

  static treeNode* min = NULL;

  if( albero != NULL ) {
    min = albero;
    searchMin( albero->leftPtr );
  }
  return min;
}

treeNode* searchMax( treeNode* albero ) {

  static treeNode* max = NULL;

  if( albero != NULL ) {
    max = albero;
    searchMax( albero->rightPtr );
  }
  return max;
}
