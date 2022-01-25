#include <iostream> // Passaggio di parametri : in per copia
using namespace std;

void swap( int a, int b ) {
  int tmp;

  tmp = a;
  a = b;
  b = tmp;
}

int main( void ) {

  int a = 5;
  int b = 6;

  cout << "a : " << a << endl;
  cout << "b : " << b << endl;

  swap( a, b );

  putchar( '\n' );
  cout << "a : " << a << endl;
  cout << "b : " << b << endl;

  return 0;
}
