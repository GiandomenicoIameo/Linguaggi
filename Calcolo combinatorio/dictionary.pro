:- include( 'combinatorics.pro' ).

generate_binomial( List, Comb ) :- sort( List, Set ),
binomial( Set, Comb ).

generate_permutation( List, Comb ) :- sort( List, Set ),
permutation( Set, Comb ).

generate_combination( List, Comb ) :- sort( List, Set ),
combination( Set, Comb ).
