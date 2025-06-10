#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct array *ptr_array;



/*
  Funzione: crea_array
  --------------------

  Crea e inizializza una nuova struttura array con tutte le celle impostate a NULL.

  Parametri:
     Nessuno

  Pre-condizioni:
     Nessuna

  Post-condizioni:
     Se l'allocazione ha successo, restituisce un puntatore a una struttura `ptr_array` inizializzata;
     altrimenti restituisce NULL.

  Ritorna:
     Un puntatore a una nuova struttura `ptr_array`, oppure NULL in caso di errore.

  Side-effect:
     Alloca memoria dinamicamente per una struttura `array`.
*/
ptr_array crea_array();

/*
  Funzione: dimensione_array
  --------------------------

  Restituisce la dimensione fissa dell’array (numero di celle giornaliere).

  Parametri:
     Nessuno

  Pre-condizioni:
     Nessuna

  Post-condizioni:
     Nessuna

  Ritorna:
     Un intero che rappresenta la dimensione dell'array.

  Side-effect:
     Nessuno
*/
int dimensione_array();

/*
  Funzione: inserisci_in_array
  ----------------------------

  Inserisce un valore generico (void*) in una specifica posizione dell'array.

  Parametri:
     a       - puntatore alla struttura `array`
     indice  - posizione dell'array dove inserire il valore
     valore  - puntatore al valore da inserire

  Pre-condizioni:
     a != NULL
     indice compreso tra 0 e CELLE_GIORNALIERE - 1

  Post-condizioni:
     Se le condizioni sono soddisfatte, il valore è assegnato alla cella indicata.

  Ritorna:
     true se l'inserimento ha avuto successo, false altrimenti.

  Side-effect:
     Modifica lo stato dell'array puntato da `a`.
*/
bool inserisci_in_array(ptr_array a, int indice, void *valore);

/*
  Funzione: cerca_in_array
  ------------------------

  Restituisce il valore contenuto in una specifica posizione dell'array.


  Parametri:
     a       - puntatore alla struttura `array`
     indice  - posizione dell'array da leggere

  Pre-condizioni:
     a != NULL
     indice compreso tra 0 e CELLE_GIORNALIERE - 1

  Post-condizioni:
     Nessuna

  Ritorna:
     Il valore contenuto nella cella indicata, oppure NULL se indice non valido o cella vuota.

  Side-effect:
     Nessuno
*/
void *cerca_in_array(ptr_array a, int indice);

/*
  Funzione: distruggi_array
  -------------------------

  Libera la memoria associata alla struttura `array`. 
  Se fornita, applica una funzione di distruzione ai valori non NULL contenuti nelle celle.

  Parametri:
     a                - puntatore alla struttura `array` da distruggere
     distruggi_valore - funzione da applicare a ciascun valore prima della liberazione (può essere NULL)

  Pre-condizioni:
     Nessuna (la funzione gestisce anche a == NULL)

  Post-condizioni:
     La memoria per la struttura viene rilasciata;
     ogni valore non NULL viene processato con la funzione di distruzione, se presente.

  Ritorna:
     Nulla

  Side-effect:
     Libera memoria dinamica; può chiamare funzioni di distruzione sui valori contenuti.
*/
void distruggi_array(ptr_array a, void (*distruggi_valore)(void *));

/*
  Funzione: azzera_array
  ----------------------

  Imposta tutte le celle dell’array a NULL (azzeramento logico).

  Parametri:
     a - puntatore alla struttura `array` da azzerare

  Pre-condizioni:
     a != NULL

  Post-condizioni:
     Tutte le celle dell’array sono impostate a NULL.

  Ritorna:
     Nulla

  Side-effect:
     Modifica lo stato interno dell’array.
*/
void azzera_array(ptr_array a);

#endif