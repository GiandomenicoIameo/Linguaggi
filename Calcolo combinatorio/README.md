# Calcolo combinatorio

## ```binomial/2```:

Il predicato ```binomial/2``` consente di ricercare il numero dei sottoinsiemi, di un particolare insieme, aventi cardinalità non superiore all’insieme di partenza. In
particolare, come accade spesso nel linguaggio Prolog, tale predicato è anche bidirezionale. Vediamo alcuni esempi :

```prolog
?- binomial( [ a,b,c ], X ).
X = [] ;
X = [a] ;
X = [a, b] ;
X = [a, b, c] ;
X = [a, c] ;
X = [b] ;
X = [b, c] ;
X = [c] ;
false. 
```
In questo caso, il predicato ha ricercato lungo l'albero di derivazione ogni sottoinsieme di ```[a, b, c]``` di cardinalità 1,2 e 3. Come è possibile notare, il numero dei sottoinsiemi generati è uguale al numero di sottoinsiemi dell’insieme delle parti di ```[a, b, c]```. Tuttavia, è possibile imporre al programma di ricercare solo sottoinsiemi di cardinalità 2 :

```prolog
?- binomial( [ a,b,c ], [ X,Y ] ).
X = a,
Y = b ;
X = a,
Y = c ;
X = b,
Y = c ;
false.
```
Ritornando al concetto di bidirezionalità, il predicato può essere usato per ricercare tutti i soprainsiemi di un certo insieme :

```prolog
?- binomial( X, [ a,b ] ).
X = [a, b|_3196] ;
X = [a, _3194, b|_3202] ;
X = [a, _3194, _3200, b|_3208] ;
X = [a, _3194, _3200, _3206, b|_3214] ;
...
```
In questo caso, sono stati ricercati tutti i soprainsiemi dell'insieme 
```[a, b]``` e cioè tutti gli insieme ```X``` tali che,```X``` contiene ```[a, b]``` come parte. Ovviamente i risultati non avranno fine.

----------
__*N.B.*__ Il predicato ```binomial/2``` suppone per ipotesi che l'insieme ricevuto come argomento sia effettivamente un insieme. Tuttavia, se il predicato riceverà in input una ennupla ordinata in cui compaiono elementi ripetuti, i risultati che produrrà potrebbero essere non quelli desiderati : verranno generati insiemi con elementi ripetuti. Per ovviare a ciò, è possibile utilizzare il predicato ```generate_binomial/2``` :

```prolog
?- generate_binomial( [ a,b,c,a,c ], X ).
X = [] ;
X = [a] ;
X = [a, b] ;
X = [a, b, c] ;
X = [a, c] ;
X = [b] ;
X = [b, c] ;
X = [c] ;
false.
```

Il predicato ha considerato l'insieme ```[a, b, c, a, c]``` prefettamente equivalente all'insieme ```[a, b, c]```. Nonostante questo vantaggio, lo stesso predicato non è bidirezionale.
