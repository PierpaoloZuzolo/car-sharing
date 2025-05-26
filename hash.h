#ifndef HASH_H
#define HASH_H

#include "utente.h"
#include <stdbool.h>

/*
 Tipo astratto di dato: tabella_hash
 -----------------------------------
 Struttura dati per la gestione di una tabella hash contenente utenti.
*/
typedef struct tabella_hash *ptr_hash;

/*
 Funzione: hash
 --------------
 Calcola l'hash per una stringa (chiave) usando una funzione di hashing.

 Parametri:
   chiave: puntatore a una stringa (es. codice fiscale).
   dimensione: dimensione della tabella hash.

 Pre-condizione:
   chiave deve essere un puntatore valido.
   dimensione > 0.

 Post-condizione:
   Nessuna modifica ai parametri.

 Ritorna:
   Un intero non negativo rappresentante l'indice hash calcolato.
*/
unsigned int hash(char *chiave, int dimensione);


/*
 Funzione: nuova_tabella_hash
 ----------------------------
 Crea e inizializza una nuova tabella hash vuota con dimensione specificata.

 Parametri:
   dimensione: numero di bucket nella tabella.

 Pre-condizione:
   dimensione > 0.

 Post-condizione:
   Alloca e restituisce un puntatore a una nuova tabella hash vuota.

 Ritorna:
   Puntatore alla tabella hash appena creata,
   oppure NULL in caso di errore.
*/
ptr_hash nuova_tabella_hash(int dimensione);


/*
 Funzione: inserisci_hash
 ------------------------
 Inserisce un utente nella tabella hash.

 Parametri:
   h: puntatore alla tabella hash.
   utente: puntatore all'utente da inserire.

 Pre-condizione:
   h e utente devono essere puntatori validi.

 Post-condizione:
   L'utente è inserito nella tabella se non già presente.

 Ritorna:
   true se l'inserimento ha avuto successo,
   false se l'utente era già presente o in caso di errore.
*/
bool inserisci_hash(ptr_hash h, ptr_utente utente);


/*
 Funzione: cerca_utente
 ----------------------
 Cerca un utente nella tabella hash.

 Parametri:
   h: puntatore alla tabella hash.
   utente: puntatore a un utente con il campo chiave da confrontare.

 Pre-condizione:
   h e ut devono essere puntatori validi.

 Post-condizione:
   Nessuna modifica alla tabella.

 Ritorna:
   Puntatore all'utente trovato, oppure NULL se non esiste.
*/
ptr_utente cerca_utente(ptr_hash h, ptr_utente utente);


/*
 Funzione: distruggi_hash
 ------------------------
 Libera tutta la memoria associata alla tabella hash.

 Parametri:
   h: puntatore alla tabella da liberare.

 Pre-condizione:
   h deve essere un puntatore valido.

 Post-condizione:
   Tutta la memoria occupata dalla tabella e dagli utenti viene liberata.

 Ritorna:
   Nessun valore.
*/
void distruggi_hash(ptr_hash h);


/*
 Funzione: dimensione_hash
 -------------------------
 Restituisce il numero di utenti attualmente presenti nella tabella hash.

 Parametri:
   h: puntatore alla tabella hash.

 Pre-condizione:
   h deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica alla tabella.

 Ritorna:
   Numero di elementi nella tabella.
*/
int dimensione_hash(ptr_hash h);

#endif
