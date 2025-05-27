#ifndef LISTA_VEICOLI_H
#define LISTA_VEICOLI_H

#include "veicolo.h"

/*
 Tipo astratto di dato: lista_veicoli
 ------------------------------------
 Struttura che rappresenta una lista dinamica di veicoli.
*/
typedef struct lista_veicoli *ptr_lista;

/*
 Funzione: nuova_lista
 ---------------------
 Crea e inizializza una nuova lista di veicoli vuota.

 Parametri:
   Nessuno.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   Alloca e restituisce un puntatore a una nuova lista vuota.

 Ritorna:
   Puntatore alla lista appena creata,
   oppure NULL in caso di errore.
*/
ptr_lista nuova_lista();


/*
 Funzione: inserisci_veicolo_lista
 ---------------------------------
 Inserisce un veicolo alla fine della lista.

 Parametri:
   li: puntatore alla lista di veicoli.
   ve: puntatore al veicolo da inserire.

 Pre-condizione:
   li e ve devono essere puntatori validi (non NULL).

 Post-condizione:
   Il veicolo viene inserito nella lista.

 Ritorna:
   Nessun valore.
*/
void inserisci_veicolo_lista(ptr_lista li, ptr_veicolo ve);


/*
 Funzione: rimuovi_veicolo_non_disponibile
 -----------------------------------------
 Rimuove dalla lista tutti i veicoli il cui stato non è "disponibile".

 Parametri:
   li: puntatore alla lista di veicoli.

 Pre-condizione:
   li deve essere un puntatore valido.

 Post-condizione:
   I veicoli non disponibili vengono rimossi e la loro memoria liberata.

 Ritorna:
   Nessun valore.
*/
void rimuovi_veicolo_non_disponibile(ptr_lista li);


/*
 Funzione: stampa_lista_veicoli
 ------------------------------
 Stampa tutte le informazioni dei veicoli presenti nella lista.

 Parametri:
   li: puntatore alla lista da stampare.

 Pre-condizione:
   li deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica alla lista.

 Ritorna:
   Nessun valore. Produce output a video.
*/
void stampa_lista_veicoli(ptr_lista li);


/*
 Funzione: libera_lista_veicoli
 ------------------------------
 Libera tutta la memoria associata alla lista e ai veicoli in essa contenuti.

 Parametri:
   li: puntatore alla lista da liberare.

 Pre-condizione:
   li deve essere un puntatore valido.

 Post-condizione:
   Tutta la memoria occupata dalla lista e dai veicoli è liberata.

 Ritorna:
   Nessun valore.
*/
void libera_lista_veicoli(ptr_lista li);


/*
 Funzione: trova_veicolo_lista
 -----------------------------
 Restituisce il veicolo alla posizione specificata nella lista.

 Parametri:
   posizione: indice del veicolo da restituire (0-based).
   li: puntatore alla lista da cui cercare.

 Pre-condizione:
   li deve essere un puntatore valido.
   posizione deve essere compresa tra 0 e (dimensione della lista - 1).

 Post-condizione:
   Nessuna modifica alla lista.

 Ritorna:
   Puntatore al veicolo alla posizione specificata,
   oppure NULL se la posizione è invalida.
*/
ptr_veicolo trova_veicolo_lista(int posizione, ptr_lista li);


#endif
