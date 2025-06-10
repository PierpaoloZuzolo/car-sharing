#ifndef ARRAY_PRENOTAZIONE_H
#define ARRAY_PRENOTAZIONE_H

#include "array.h"


typedef struct array *ptr_prenotazione;

/*
  Funzione: inizializza_prenotazioni
  ----------------------------------

  Crea e inizializza un nuovo array di prenotazioni.

  Parametri:
     Nessuno

  Pre-condizioni:
     Nessuna

  Post-condizioni:
     Se l’allocazione ha successo, restituisce un array con tutte le celle a NULL.

  Ritorna:
     Un puntatore a un nuovo array di prenotazioni, oppure NULL in caso di errore.

  Side-effect:
     Alloca memoria dinamicamente per l’array.
*/
ptr_prenotazione inizializza_prenotazioni();

/*
  Funzione: prendi_grandezza_array_prenotazioni
  ---------------------------------------------

  Restituisce la dimensione dell’array delle prenotazioni.

  Parametri:
     Nessuno

  Pre-condizioni:
     Nessuna

  Post-condizioni:
     Nessuna

  Ritorna:
     Un intero pari al numero di celle disponibili nell’array.

  Side-effect:
     Nessuno
*/
int prendi_grandezza_array_prenotazioni();

/*
  Funzione: prenota_intervallo
  ----------------------------

  Segna come prenotate le celle comprese in un intervallo specificato.

  Parametri:
     p            - puntatore all’array delle prenotazioni
     inizio_cella - indice iniziale (inclusivo)
     fine_cella   - indice finale (esclusivo)

  Pre-condizioni:
     p != NULL
     inizio_cella e fine_cella - 1 devono essere in range valido
     inizio_cella < fine_cella

  Post-condizioni:
     Se tutte le celle sono libere, l’intervallo è prenotato.

  Ritorna:
     1 se la prenotazione ha successo, 0 altrimenti.

  Side-effect:
     Modifica lo stato dell’array prenotazioni.
*/
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
  Funzione: libera_intervallo
  ---------------------------

  Libera tutte le celle dell’intervallo specificato.

  Parametri:
     p            - puntatore all’array delle prenotazioni
     inizio_cella - indice iniziale (inclusivo)
     fine_cella   - indice finale (esclusivo)

  Pre-condizioni:
     p != NULL
     inizio_cella e fine_cella - 1 devono essere in range valido
     inizio_cella < fine_cella

  Post-condizioni:
     Le celle nell’intervallo risultano libere.

  Ritorna:
     1 se l’operazione ha successo, 0 altrimenti.

  Side-effect:
     Modifica lo stato dell’array prenotazioni.
*/
int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
  Funzione: ottiene_cella
  -----------------------

  Verifica se una determinata cella è prenotata.

  Parametri:
     p      - puntatore all’array delle prenotazioni
     indice - indice della cella da controllare

  Pre-condizioni:
     p != NULL
     indice in range valido

  Post-condizioni:
     Nessuna

  Ritorna:
     1 se la cella è prenotata, 0 se libera, -1 se indice non valido.

  Side-effect:
     Nessuno
*/
int ottiene_cella(ptr_prenotazione p, int indice);

/*
  Funzione: imposta_cella
  -----------------------

  Imposta manualmente lo stato di una singola cella.

  Parametri:
     p      - puntatore all’array delle prenotazioni
     indice - indice della cella da modificare
     valore - 0 per liberare, diverso da 0 per prenotare

  Pre-condizioni:
     p != NULL
     indice in range valido

  Post-condizioni:
     La cella indicata assume il valore corrispondente.

  Ritorna:
     Nulla

  Side-effect:
     Modifica la cella specificata.
*/
void imposta_cella(ptr_prenotazione p, int indice, int valore);

/*
  Funzione: azzera_celle
  ----------------------

  Libera tutte le celle dell’array, azzerandole.

  Parametri:
     p - puntatore all’array delle prenotazioni

  Pre-condizioni:
     p != NULL

  Post-condizioni:
     Tutte le celle risultano libere (NULL).

  Ritorna:
     Nulla

  Side-effect:
     Modifica tutte le celle dell’array.
*/

void azzera_celle(ptr_prenotazione p);

/*
  Funzione: in_intervallo
  -----------------------

  Controlla se un indice si trova nell'intervallo [inizio, fine).

  Parametri:
     indice - valore da verificare
     inizio - limite inferiore (inclusivo)
     fine   - limite superiore (esclusivo)

  Pre-condizioni:
     Nessuna

  Post-condizioni:
     Nessuna

  Ritorna:
     1 se indice ∈ [inizio, fine), 0 altrimenti.

  Side-effect:
     Nessuno
*/

int in_intervallo(int indice, int inizio, int fine);


/*
  Funzione: distruggi_array_prenotazioni
  --------------------------------------

  Distrugge l’array delle prenotazioni e libera la memoria.

  Parametri:
     p - puntatore all’array delle prenotazioni

  Pre-condizioni:
     Nessuna

  Post-condizioni:
     L’array viene deallocato.

  Ritorna:
     Nulla

  Side-effect:
     Libera memoria dinamica.
*/
void distruggi_array_prenotazioni(ptr_prenotazione p);

#endif