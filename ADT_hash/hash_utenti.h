/*
Autore: Roberto Saporoso
Data: 07/06/2025
*/

#ifndef HASH_UTENTI_H
#define HASH_UTENTI_H

#include "Modello_utente/utente.h"
#include <stdbool.h>

/*
 Tipo astratto di dato: tabella_hash
 -----------------------------------
 Struttura dati per la gestione di una tabella hash contenente utenti.
*/


typedef struct tabella_hash *ptr_hash_utenti;

/*
 Funzione: crea_hash_utenti
 --------------------------

 Crea una nuova tabella hash specificamente per la gestione degli utenti.

 Parametri:
    dimensione: numero di bucket da allocare nella tabella hash

 Pre-condizioni:
    dimensione deve essere maggiore di 0

 Post-condizioni:
    restituisce un puntatore a una nuova tabella hash per utenti, oppure NULL in caso di errore

 Ritorna:
    un puntatore a una struttura `ptr_hash_utenti`, o NULL se la creazione fallisce

 Side-effect:
    alloca memoria dinamicamente per la nuova tabella hash
 */
ptr_hash_utenti crea_hash_utenti(int dimensione);

/*
 Funzione: distruggi_hash_utenti
 -------------------------------

 Distrugge una tabella hash contenente utenti, liberando tutta la memoria associata.

 Parametri:
    h: puntatore alla tabella hash di utenti

 Pre-condizioni:
    h può essere NULL; se non lo è, deve essere una tabella hash valida creata con `crea_hash_utenti`

 Post-condizioni:
    la memoria associata alla tabella hash e agli utenti viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata alla tabella hash e agli utenti
 */
void distruggi_hash_utenti(ptr_hash_utenti h);

/*
 Funzione: inserisci_utente_in_hash
 ----------------------------------

 Inserisce un utente nella tabella hash usando il nome come chiave.

 Parametri:
    h: puntatore alla tabella hash degli utenti
    ut: puntatore all'utente da inserire

 Pre-condizioni:
    h deve essere una tabella hash valida
    ut deve essere un utente valido
    il nome restituito da `prendi_nome(ut)` deve essere non NULL

 Post-condizioni:
    se la funzione ha successo, l'utente è inserito nella tabella hash
    altrimenti la tabella non viene modificata

 Ritorna:
    true se l'inserimento è andato a buon fine,
    false in caso di errore (puntatori NULL, nome NULL o duplicato)

 Side-effect:
    può allocare memoria internamente tramite `inserisci_in_hash`
 */
bool inserisci_utente_in_hash(ptr_hash_utenti h, ptr_utente ut);

/*
 Funzione: cerca_utente_in_hash
 ------------------------------

 Cerca un utente nella tabella hash dato il nome.

 Parametri:
    h: puntatore alla tabella hash degli utenti
    nome: stringa che rappresenta il nome dell'utente da cercare

 Pre-condizioni:
    h deve essere una tabella hash valida
    nome deve essere una stringa non NULL terminata da '\0'

 Post-condizioni:
    nessuna modifica alla tabella hash

 Ritorna:
    un puntatore all'utente se trovato,
    NULL se la tabella è NULL o l'utente non è presente

 Side-effect:
    nessuno
 */
ptr_utente cerca_utente_in_hash(ptr_hash_utenti h, const char* nome);






#endif
