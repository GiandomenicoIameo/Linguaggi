elem( X, [ X|_ ] ).
elem( X, [ _|L ] ) :- elem( X, L ).

delete( T, [ T|List ], List ).
delete( X, [ T|List ], [ T|Rest ] ) :- delete( X, List, Rest ).

queue( X, [ X|List ], List ).                                       /* Il predicato queue/3 restituisce il resto della lista        */
queue( X, [ _|List ], Queue ) :- queue( X, List, Queue ).           /* a partire da ogni elemento : ?- queue( 2, [ 1,2,3,4 ], X ).  */
                                                                    /* X = [ 3,4 ]                                                  */
permutation( _, [] ).
permutation( List, [ X|Rest ] ) :- cancella( X, List, Comb ),       /* Per creare le permutazioni senza ripertizioni è sufficiente                   */
permutation( Comb, Rest ).                                          /* scrivere il predicato in questo modo : permutation( List, [ X1,X2,..Xn ] ),   */
                                                                    /* dove n indica la lunghezza della lista List.                                  */
combination( _, [] ).
combination( List, [ X|Rest ] ) :- elem( X, List ),
combination( List, Rest ).

binomial( _, [] ).
binomial( List, [ X|Rest ] ) :- queue( X, List, Tail ),
binomial( Tail, Rest ).
