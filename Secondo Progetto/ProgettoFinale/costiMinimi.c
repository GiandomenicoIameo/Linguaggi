#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"
#include <time.h>

void calcoloDistanzaCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

     ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

     while( tempTesta != NULL ) {
        if( distanze[ verticeSrc ] + tempTesta->prezzo < distanze[ tempTesta->vertice ] ) {
            distanze[ tempTesta->vertice ] = distanze[ verticeSrc ] + tempTesta->prezzo;
            predecessori[ tempTesta->vertice ] = verticeSrc;
            removeNodo( Testa, tempTesta->vertice );
            insertCoda( Testa, tempTesta->vertice, distanze[ tempTesta->vertice ] );
        }
        tempTesta = tempTesta->next;
     }
}

void AggiornaNodoCosti( Coda** Testa, int vertice, int distanze ) {

     Coda* tempTesta = *Testa;

     while( tempTesta != NULL ) {
        if( tempTesta->vertice == vertice ) {
            tempTesta->distanza = distanze;
            return;
        }
        tempTesta = tempTesta->next;
    }
}

void inserimentoAdiacenzeCosti( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

    ListAdiacenza* tempTesta = graph->summit[ verticeSrc ];

    while( tempTesta != NULL ) {
        distanze[ tempTesta->vertice ] = tempTesta->prezzo;
        predecessori[ tempTesta->vertice ] = verticeSrc;
        AggiornaNodoCosti( Testa, tempTesta->vertice, distanze[ tempTesta->vertice ] );
        tempTesta = tempTesta->next;
    }
}

void algoritmoDijkstraCosto( Coda** Testa, Grafo* graph, int verticeSrc, int* distanze, int* predecessori ) {

    int vertice;

    for( int indice = verticeSrc + 1; indice < graph->numeroVertici; indice++ )
          insertCoda( Testa, indice, INF );

  distanze[ verticeSrc ] = 0;
  inserimentoAdiacenzeCosti( Testa, graph, verticeSrc, distanze, predecessori );

  while( *Testa != NULL ) {
       vertice = removeCoda( Testa );
       calcoloDistanzaCosti( Testa, graph, vertice, distanze, predecessori );
  }
}

void stampaCostoPercorsoMinimo( int verticeDst, int verticeSrc, int* predecessori, char** citta, int* distanze ) {

     if( distanze[ verticeDst ] == INF ) {
         puts( "Prezzo al momento non disponibile" );
         return;
     }

     if( predecessori[ verticeDst ] == verticeSrc ) {
         printf( "%s < ", citta[ verticeDst ] );
         printf( "%s\n", citta[ verticeSrc ] );
         return;
     }
     else {
        printf( "%s < ", citta[ verticeDst ] );
        stampaCostoPercorsoMinimo( predecessori[ verticeDst ], verticeSrc, predecessori, citta, distanze );
    }
}
