#include <stdio.h>

struct Nodo_SL{
  char dato;
  struct Nodo_SL* next;
};

typedef struct Nodo_SL Nodo;

void NewLista( Nodo** TopPtr, char value );
void InsertTesta( Nodo** TestaPtr, char value );
void Print( Nodo* TestaPtr );
void InsertCoda( Nodo** TestaPtr, char value );
Nodo* Ordinamento( Nodo* TestaPtr, char value );
int lenList( Nodo* TestaPtr );
Nodo* deleteNodo( Nodo* TestaPtr, char value );
void instruction( void );
