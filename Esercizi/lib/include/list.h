#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>

struct elem {
  int data;
  struct elem* next;
};

struct elem* createList( void );
struct elem* creatNode( int data );
struct elem* push( struct elem* top, struct elem* node );
struct elem* enqueue( struct elem* top, struct elem* node );

#endif
