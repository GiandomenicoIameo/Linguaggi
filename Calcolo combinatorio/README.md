Prolog
===================



Installazione e configurazione :
----------

Windows e Mac :
E' possibile scaricare e installare SWI-Prolog direttamente dal sito ufficiale <link>,
è sufficiente seguire la procedura di installazione.

Linux:

 1. Aggiungi il ppa ppa:swi-prolog/stable alle sorgenti software del tuo sistema :
       Apri il terminale e digita:
       ```$ sudo add-apt-repository ppa:swi-prolog/stable ```

       Successivamente, aggiorna le informazioni sul pacchetto:
       ```$ sudo apt-get update```

       Ora installa SWI-Prolog tramite il gestore pacchetti principale:
       Apri il terminale e digita:
       ```$ sudo apt-get install swi-prolog```

binomial/2 :
----------

Il predicato binomial/2 consente di ricercare il numero dei sottoinsiemi di una certa cardinalità. In
particolare, il suddetto predicato è bidirezionale. Vediamo alcuni esempi :

```?- binomial( [ a,b,c ], X ).
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




