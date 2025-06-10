/*
Autore: Roberto Saporoso, Carmine Saporoso
Data: 07/06/2025
*/

#ifndef HASH_VEICOLI_H
#define HASH_VEICOLI_H

#include "Modello_veicolo/veicolo.h"
#include <stdbool.h>




typedef struct tabella_hash *ptr_hash_veicoli;

/*
 Funzione: crea_hash_veicoli
 ---------------------------

 Crea una nuova tabella hash specificamente per la gestione dei veicoli.


 Parametri:
    dimensione: numero di bucket da allocare nella tabella hash

 Pre-condizioni:
    dimensione deve essere maggiore di 0

 Post-condizioni:
    restituisce un puntatore a una nuova tabella hash per veicoli, oppure NULL in caso di errore

 Ritorna:
    un puntatore a una struttura `ptr_hash_veicoli`, o NULL se la creazione fallisce

 Side-effect:
    alloca memoria dinamicamente per la nuova tabella hash
 */
ptr_hash_veicoli crea_hash_veicoli(int dimensione);

/*
 Funzione: libera_veicolo_hash
 -----------------------------

 Funzione ausiliaria per liberare correttamente la memoria associata a un veicolo,
 da usare come callback nei processi di distruzione della tabella hash.


 Parametri:
    veicolo: puntatore generico a un veicolo da liberare

 Pre-condizioni:
    veicolo deve essere non NULL e puntare a una struttura `veicolo` valida

 Post-condizioni:
    la memoria associata al veicolo viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata al veicolo
 */
static void libera_veicolo_hash(void *veicolo);

/*
 Funzione: distruggi_hash_veicoli
 --------------------------------

 Distrugge una tabella hash contenente veicoli, liberando tutta la memoria associata.

 Parametri:
    h: puntatore alla tabella hash di veicoli

 Pre-condizioni:
    h può essere NULL; se non lo è, deve essere una tabella hash valida creata con `crea_hash_veicoli`

 Post-condizioni:
    la memoria associata alla tabella hash e ai veicoli viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata alla tabella hash e ai veicoli
 */
void distruggi_hash_veicoli(ptr_hash_veicoli h);

/*
 Funzione: inserisci_veicolo_in_hash
 -----------------------------------

 Inserisce un veicolo nella tabella hash usando la targa come chiave.

 Parametri:
    h: puntatore alla tabella hash dei veicoli
    ve: puntatore al veicolo da inserire

 Pre-condizioni:
    h deve essere una tabella hash valida
    ve deve essere un veicolo valido
    la targa restituita da `prendi_targa(ve)` deve essere non NULL

 Post-condizioni:
    se la funzione ha successo, il veicolo è inserito nella tabella hash
    altrimenti la tabella non viene modificata

 Ritorna:
    true se l'inserimento è andato a buon fine,
    false in caso di errore (puntatori NULL, targa NULL o duplicato)

 Side-effect:
    può allocare memoria internamente tramite `inserisci_in_hash`
 */
bool inserisci_veicolo_in_hash(ptr_hash_veicoli h, ptr_veicolo ve);


/*
 Funzione: cerca_veicolo_in_hash
 -------------------------------

 Cerca un veicolo nella tabella hash dato il numero di targa.

 Implementazione:
    Verifica che la tabella hash sia non NULL.
    Usa la funzione `cerca_in_hash` passando la targa come chiave.
    Se il veicolo viene trovato, ne restituisce il puntatore, altrimenti NULL.

 Parametri:
    h: puntatore alla tabella hash dei veicoli
    targa: stringa che rappresenta la targa del veicolo da cercare

 Pre-condizioni:
    h deve essere una tabella hash valida
    targa deve essere una stringa non NULL terminata da '\0'

 Post-condizioni:
    nessuna modifica alla tabella hash

 Ritorna:
    un puntatore al veicolo se trovato,
    NULL se la tabella è NULL o il veicolo non è presente

 Side-effect:
    nessuno
 */
ptr_veicolo cerca_veicolo_in_hash(ptr_hash_veicoli h, const char *targa);

/*
 Funzione: stampa_veicoli_disponibili
 ------------------------------------

 Stampa tutti i veicoli che risultano attualmente disponibili nella tabella hash.

 Parametri:
    h: puntatore alla tabella hash contenente i veicoli

 Pre-condizioni:
    h deve essere un puntatore valido a una ptr_tabella_hash.

 Post-condizioni:
    Nessuna modifica permanente alla tabella o ai veicoli (solo aggiornamento temporaneo dello stato prenotazioni).

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Stampa su standard output i veicoli disponibili.
    Libera la memoria temporanea allocata per l’elenco dei valori.
 */

void stampa_veicoli_disponibili(ptr_hash_veicoli h);



#endif