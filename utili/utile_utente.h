/*
Autore: Roberto Saporoso
Data: 20/05/2025
*/

#ifndef UTILE_UTENTE_H
#define UTILE_UTENTE_H

#include "Modello_utente/utente.h"

#define NULLITEM NULL


/*
 Funzione: stampa_utente
 -----------------------

 Stampa a video il nome dell'utente se il puntatore fornito è valido.

 Parametri:
    ut: puntatore a una struttura `utente` da stampare.

 Pre-condizioni:
    Il parametro `ut` deve essere un puntatore valido o NULL.

 Post-condizioni:
    Nessuna modifica agli oggetti passati.

 Ritorna:
    Nessun valore.

 Side-effect:
    Scrive sullo standard output il nome dell'utente, se presente.
 */
void stampa_utente(ptr_utente ut);

/*
 Funzione: salva_utente_su_file
 ------------------------------

 Salva i dati dell'utente su due file:
 1) un file generale di elenco utenti (append),
 2) un file dedicato con nome "<nome_utente>.txt" contenente dati specifici.

 Parametri:
    nome_file: stringa contenente il nome del file per l'elenco generale utenti
    ut: puntatore alla struttura utente da salvare

 Pre-condizioni:
    `nome_file` deve essere una stringa valida.
    `ut` deve essere un puntatore valido non NULL.

 Post-condizioni:
    I dati dell'utente sono salvati su disco su due file (append + dedicato).

 Ritorna:
    void

 Side-effect:
    Scrive su file su disco.
    Può stampare messaggi di errore su stdout in caso di problemi.
 */
void salva_utente_su_file(char *nome_file, ptr_utente ut);

/*
 Funzione: carica_utente_da_file
 -------------------------------

 Carica gli utenti da un file e li inserisce nella tabella hash degli utenti.

 Parametri:
    nome_file: stringa contenente il nome del file da cui caricare gli utenti
    h: puntatore alla tabella hash utenti in cui inserire gli utenti caricati

 Pre-condizioni:
    `nome_file` deve essere una stringa valida e puntatore non NULL.
    `h` deve essere un puntatore valido alla tabella hash.

 Post-condizioni:
    La tabella hash `h` conterrà i nuovi utenti caricati dal file.

 Ritorna:
    void

 Side-effect:
    Può allocare memoria per nuovi utenti e modificarne la tabella hash.
 */
void carica_utente_da_file(const char *nome_file, ptr_hash_utenti h);


/*
 Funzione: libera_utente
 -----------------------

 Libera la memoria allocata per una struttura utente.

 Parametri:
    ut: puntatore alla struttura utente da liberare

 Pre-condizioni:
    `ut` deve essere un puntatore valido o NULL.

 Post-condizioni:
    La memoria occupata dalla struttura utente viene liberata.

 Ritorna:
    void

 Side-effect:
    Libera memoria dinamica.
 */
void libera_utente(ptr_utente ut);


#endif