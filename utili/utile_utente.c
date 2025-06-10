/*
Autore: Roberto Saporoso
Data: 20/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utile_utente.h"
#include "Modello_utente/utente.h"
#include "ADT_hash/hash_utenti.h"


/*
 Funzione: stampa_utente
 -----------------------

 Stampa a video il nome dell'utente se il puntatore fornito è valido.

 Implementazione:
    Verifica che il puntatore all'utente non sia NULL.
    Se valido, stampa il nome ottenuto tramite la funzione `prendi_nome`.

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
void stampa_utente(ptr_utente ut)
{
    if(ut){
        printf("%s", prendi_nome(ut));
    }
}


/*
 Funzione: salva_utente_su_file
 ------------------------------

 Salva i dati dell'utente su due file:
 1) un file generale di elenco utenti (append),
 2) un file dedicato con nome "<nome_utente>.txt" contenente dati specifici.

 Implementazione:
    Controlla che il puntatore utente sia valido.
    Apre il file generale in append e scrive nome ed email.
    Costruisce il nome del file dedicato basato sul nome dell'utente.
    Apre il file dedicato in scrittura (sovrascrive se esiste).
    Scrive dati specifici (nome, email, sconto di default).
    Gestisce errori di apertura file con messaggi su stdout.

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
void salva_utente_su_file(char *nome_file, ptr_utente ut)
{
    if (!ut) {
        printf("\nErrore: utente nullo.\n");
        return;
    }

    // Salvataggio su file generale (append)
    FILE *file = fopen(nome_file, "a");
    if (file) {
        fprintf(file, "%s %s\n", prendi_nome(ut), prendi_email(ut));
        fclose(file);
    } else {
        printf("\nErrore salvataggio file utenti generico.\n");
    }

}


/*
 Funzione: carica_utente_da_file
 -------------------------------

 Carica gli utenti da un file e li inserisce nella tabella hash degli utenti.

 Implementazione:
    Apre il file in lettura.
    Se il file non esiste o non può essere aperto, esce senza modificare la tabella hash.
    Legge da file coppie di stringhe (nome e email) fino a fine file.
    Per ogni coppia, crea un nuovo utente con `inizia_utente` e lo inserisce nella hash con `inserisci_utente_in_hash`.

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
void carica_utente_da_file(const char *nome_file, ptr_hash_utenti h)
{
    FILE *file = fopen(nome_file, "r");
    // Controlla se non esiste o non si apre, termina senza modificare.
    if(!file){
        return;
    }

    char nome[50], 
        email[100];

    while(fscanf(file, "%50s %100s", nome, email) == 2){
        // Crea un nuovo utente e lo inserisce nella tabella hash.
        inserisci_utente_in_hash(h, inizia_utente(nome, email));
    }
}


/*
 Funzione: libera_utente
 -----------------------

 Libera la memoria allocata per una struttura utente.

 Implementazione:
    Se il puntatore utente non è NULL, libera la memoria dinamica associata.

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
void libera_utente(ptr_utente ut)
{
    if(ut){
        free(ut);
    }
}