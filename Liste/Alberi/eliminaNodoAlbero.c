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
int deleteNodo( treeNode** albero, int data );
treeNode* searchNodo( treeNode* albero, int data );
treeNode* searchMin( treeNode* albero );
treeNode* predecessore( treeNode* albero, int data, treeNode* predecessor );
void deleteRoot( treeNode** albero, int data );

int main( void ) {

  treeNode* root = NULL;
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

  choice = deleteNodo( &root, value );

  if( choice ) {
    InOrder( root );
    puts( "" );
  }
  else {
    puts( "Nodo non trovato" );
  }

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

treeNode* searchNodo( treeNode* albero, int data ) {

  if( albero == NULL )
    return NULL;
  else if( data > albero->data )
    searchNodo( albero->rightPtr, data );
  else if( data < albero->data )
    searchNodo( albero->leftPtr, data );
  else
    return albero;
}

treeNode* searchMin( treeNode* albero ) {

  static treeNode* min = NULL;

  if( albero != NULL ) {
    min = albero;
    searchMin( albero->leftPtr );
  }
  return min;
}

treeNode* predecessore( treeNode* albero, int data, treeNode* predecessor ) {

  if( albero != NULL ) {
      if( data > albero->data ) {
        predecessore( albero->rightPtr, data, albero );
      }
      else if( data < albero->data ) {
        predecessore( albero->leftPtr, data, albero );
      }
      else
        return predecessor;
  }
}


void deleteRoot( treeNode** albero, int data ) {

  treeNode* succRight = ( *albero )->rightPtr;
  treeNode* succLeft = ( *albero )->leftPtr;

  treeNode* delete = NULL;
  treeNode* treeMin = NULL;

  if( !succLeft && !succRight ) {
        // radice foglia
        *albero = NULL;
        puts( "Albero eliminato" );
        free( *albero );
  } else if ( !succLeft && succRight ) {
        // radice con un solo figlio ( destro )
        delete = *albero;
        *albero = succRight;
        free( delete );
  } else if( !succRight && succLeft ) {
        // radice con un solo figlio ( sinistro )
        delete = *albero;
        *albero = succLeft;
        free( delete );
  } else {
        // radice con tutti e due i figli
        delete = *albero;
        *albero = succRight;
        treeMin = searchMin( succRight );
        treeMin->leftPtr = succLeft;
        free( delete );
  }
}

int deleteNodo( treeNode** albero, int data ) {

  treeNode* predecessor = NULL;
  treeNode* treeMin = NULL;
  treeNode* treeFound = NULL;
  treeNode* delete = NULL;

  treeFound = searchNodo( *albero, data );
  if( treeFound == NULL ) {
    // se il nodo non esiste
    return 0;
  }
  else {
    predecessor = predecessore( *albero, data, NULL );
    if( !predecessor ) {
        // il nodo è la radice dell'albero
        deleteRoot( albero, data );
    } else {
        if( !treeFound->rightPtr && !treeFound->leftPtr ) {
            // il nodo è una foglia
            if( predecessor->leftPtr && predecessor->leftPtr->data == treeFound->data ) {
                predecessor->leftPtr = NULL;
                free( treeFound );
            } else if( predecessor->rightPtr && predecessor->rightPtr->data == treeFound->data ) {
                predecessor->rightPtr = NULL;
                free( treeFound );
            }
        } else if( treeFound->rightPtr ) {
            // il nodo ha un figlio destro oppure due figli
                treeMin = searchMin( treeFound->rightPtr );
                treeMin->leftPtr = treeFound->leftPtr;

                if( predecessor->leftPtr && predecessor->leftPtr->data == treeFound->data ) {
                      predecessor->leftPtr = treeFound->rightPtr;
                      free( treeFound );
                } else if( predecessor->rightPtr && predecessor->rightPtr->data == treeFound->data ) {
                      predecessor->rightPtr = treeFound->rightPtr;
                      free( treeFound );
                }
        } else if( treeFound->leftPtr ) {
              // il nodo ha solo un figlio ( sinistro )
                if( predecessor->leftPtr && predecessor->leftPtr->data == treeFound->data ) {
                      predecessor->leftPtr = treeFound->leftPtr;
                      free( treeFound );
                } else if( predecessor->rightPtr && predecessor->rightPtr->data == treeFound->data ) {
                      predecessor->rightPtr = treeFound->leftPtr;
                      free( treeFound );
                }
        }
      }
    }
    return 1;
}


