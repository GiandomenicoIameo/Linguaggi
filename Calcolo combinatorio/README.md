Prolog
===================



Installazione e configurazione :
----------

Windows e Mac :
E' possibile scaricare e installare SWI-Prolog direttamente dal sito ufficiale <link>,
è sufficiente seguire la procedura di installazione.

Linux:

Aggiungi il ppa **ppa:swi-prolog/stable** alle sorgenti software del tuo sistema :
Apri il terminale e digita:
 ```$ sudo add-apt-repository ppa:swi-prolog/stable ```

Successivamente, aggiorna le informazioni sul pacchetto:
```$ sudo apt-get update```

Ora installa SWI-Prolog tramite il gestore pacchetti principale:
```$ sudo apt-get install swi-prolog```

**binomial/2** :
----------

Il predicato **binomial/2** consente di ricercare il numero dei sottoinsiemi di una certa cardinalità. In
particolare, il suddetto predicato è anche bidirezionale. Vediamo alcuni esempi :

```
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
In questo caso, il predicato ha ricercato lungo l'albero di derivazione ogni sottoinsieme di [ a,b,c ] di cardinalità 1,2,3. Tuttavia, è possibile 
imporre al programma di ricercare sottoinsiemi solo di cardinalità 2 :

```
?- binomial( [ a,b,c ], [ X,Y ] ).
X = a,
Y = b ;
X = a,
Y = c ;
X = b,
Y = c ;
false.
```
Inoltre, come dicevamo prima, il predicato è bidirezionale quindi risulterà possibile ricercare gli insiemi tali che un certo insieme [ a,b ] sia sottoinsieme degli insiemi di partenza :

```
?- binomial( X, [ a,b ] ).
X = [a, b|_3196] ;
X = [a, _3194, b|_3202] ;
X = [a, _3194, _3200, b|_3208] ;
X = [a, _3194, _3200, _3206, b|_3214] ;
...
```
Ovviamente, i risultati non avranno fine.

