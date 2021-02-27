#include <stdio.h>
#include <stdlib.h>
#include "List.h"

struct Node* createList( void ) {
  return NULL;
}

struct Node* createNode( int data ) {

  struct Node* node;

  node = ( struct Node* )malloc( sizeof( struct Node ) );
  if( node == NULL ) return NULL;

  node->data = data;
  node->next = NULL;

  return node;
}

struct Node* push( struct Node* top, int data ) {

  struct Node* node = createNode( data );

  if( top == NULL )
      top = node;
  else {
      node->next = top;
      top = node;
  }
  return top;
}

struct Node* enqueue( struct Node* top, int data ) {

  struct Node* node = createNode( data );
  struct Node* temp;

  if( top == NULL ) return node;

  temp = top;
  while( temp->next != NULL ) {
    temp = temp->next;
  }
  temp->next = node;

  return top;
}
