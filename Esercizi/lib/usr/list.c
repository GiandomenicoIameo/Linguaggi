#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

struct elem* createList( void ) {
  return NULL;
}

struct elem* createNode( int data ) {

  struct elem *node;

  node = ( struct elem* )malloc( sizeof( struct elem ) );
  if( node == NULL ) return node;

  node->data = data;
  node->next = NULL;

  return node;
}

struct elem* push( struct elem *top, struct elem *node ) {

  if( top == NULL )
      top = node;
  else {
      node->next = top;
      top = node;
  }
  return top;
}

struct elem* enqueue( struct elem *top, struct elem *node ) {

  struct elem *res;

  if( top == NULL )
      res = node;
  else {
      top->next = enqueue( top->next, node );
      res = top;
  }
  return res;
}
