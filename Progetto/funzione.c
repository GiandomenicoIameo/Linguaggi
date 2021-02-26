int ricercaMeta( char** citta, char* meta );
int ricercaMinimo( int* array, int vertice, int verticeSrc );

verticePartenza = ricercaMeta( nomeCitta, partenza );
verticeDestinazione = ricercaMeta( nomeCitta, destinazione );

tratta = ricercaMinimo( distanze, vertici, verticePartenza );

if( tratta == -1 ) {
     puts( "Non esistono tratte" );
 }
  else {
      printf( "La meta più economica è : %s\n", nomeCitta[ tratta ] );
 }
 
 int ricercaMinimo( int* array, int size, int verticeSrc ) {

    int min = array[ 0 ];
    int count = -1;
    for( int indice = 0; indice < size; indice++ ) {
         if( verticeSrc == indice )
             continue;
         if( array[ indice ] < min ) {
             min = array[ indice ];
             count = indice;
         }
    }
    return count;
}

int ricercaMeta( char** citta, char* meta ) {

    int value;

    for( int indice = 0; indice < vertici; indice++ ) {
         value = strcmp( citta[ indice ], meta );

         if( !value )
             return indice;
    }
    return -1;
}
