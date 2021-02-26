#include <stdio.h>
#include <ctype.h>

char isvowel( char c ) {

  switch( c ) {
    case 'a' :
    case 'A' :

    case 'e' :
    case 'E' :

    case 'i' :
    case 'I' :

    case 'o' :
    case 'O' :

    case 'u' :
    case 'U' :
      return 1;
    default :
      return 0;
  }
}

unsigned int countdigit( char* str ) {

  unsigned int count = 0;

  for( ; *str != '\0'; str++ ) {
    if( isdigit( *str ) ) count++;
  }
  return count;
}

unsigned int countcharacter( char* str ) {

  unsigned int count = 0;

  for( ; *str != '\0'; str++ ) {
    count++;
  }
  return count;
}

unsigned int countspace( char* str ) {

  unsigned int count = 0;

  for( ; *str != '\0'; str++ ) {
      if( *str == ' ' ) count++;
  }
  return count;
}
