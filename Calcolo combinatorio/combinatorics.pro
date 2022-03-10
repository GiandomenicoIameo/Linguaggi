elem( X, [ X|_ ] ).
elem( X, [ _|L ] ) :- elem( X, L ).

delete( T, [ T|List ], List ).
delete( X, [ T|List ], [ T|Rest ] ) :- delete( X, List, Rest ).

queue( X, [ X|List ], List ).                                       
queue( X, [ _|List ], Queue ) :- queue( X, List, Queue ).           
                                                                    
permutation( _, [] ).
permutation( List, [ X|Rest ] ) :- delete( X, List, Comb ),       
permutation( Comb, Rest ).                                          
                                                                    
combination( _, [] ).
combination( List, [ X|Rest ] ) :- elem( X, List ),
combination( List, Rest ).

binomial( _, [] ).
binomial( List, [ X|Rest ] ) :- queue( X, List, Tail ),
binomial( Tail, Rest ).
