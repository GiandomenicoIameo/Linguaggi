#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>

struct Node {
  int data;
  struct Node* next;
};

struct Node* createList( void );
struct Node* createNode( int data );
struct Node* push( struct Node* top, int data );
struct Node* enqueue( struct Node* top, int data );

#endif
