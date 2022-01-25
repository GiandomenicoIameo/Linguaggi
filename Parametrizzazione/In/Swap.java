public class Swap { // Passaggio di parametri : in per copia

  public static void swap( int a, int b ) {
    int tmp = 0;

    tmp = a;
    a = b;
    b = tmp;
  }

  public static void main( String[] args ) {

    int a = 5;
    int b = 6;

    System.out.println( "a : " + a );
    System.out.println( "b : " + b );

    swap( a, b );

    System.out.println( "" );
    System.out.println( "a : " + a );
    System.out.println( "b : " + b );

  }
}
