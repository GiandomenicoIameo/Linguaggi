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


Il file contiene alcune delle piu' importanti funzioni riguardo
alle **liste semplicemente concatenate**. Ogni funzione dichiarata e'
stata studiata nel minimo dettaglio per garantire, a chi le utilizza,
prestazioni efficienti in relazione al **tempo** e allo **spazio** utilizzato.

----------

Il file header ( stdlist.h ) introduce le **strutture dati dinamiche** che
possono crescere e ridursi al momento dell'esecuzione.

- Le **liste collegate** sono collezioni di dati "allineati in una riga".
  In una lista collegata le inserzioni e le cancellazioni vengono fatte
  ovunque.

- Lo **stack** e' un tipo di lista collegata molto importante nei sistemi
  operativi e compilatori. Le inserzioni e cancellazioni vengono fatte
 _solo a un estremo_, ovvero la sua **cima**.

- Le **code** rappresentano le linee di attesa; le inserzioni vengono fatte
  _solo alla fine_ ( indicata con **tail** ) di una coda e le rimozioni
  vengono fatte _solo all'inizio_ ( indicato con **head** ) di una coda.

Ricordate che una _struttura autoreferenziale_ contiene un membro puntatore
che punta a una struttura dello stesso tipo. Le definizioni sono le seguenti :

```
// Struttura del nodo
struct elem {
    int data;
    struct elem *next;
};

// Struttura della coda
struct equeue {
    struct elem *top;
    struct elem *end;
};
```

Lo stile di scrittura del codice, come potete notare, rispecchia lo 
stile adottato in **GNOME**. Sebbene lo stile sia una questione di gusti, in 
**GNOME** preferiscono uno stile che promuova coerenza, leggibilità e 
manutenibilità. 
