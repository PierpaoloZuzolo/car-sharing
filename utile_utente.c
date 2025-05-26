#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utile_utente.h"
#include "utente.h"
#include "hash.h"


/*
 Funzione: stampa_utente
 -----------------------
 Stampa il nome dell'utente su standard output.

 Parametri:
   ut: puntatore all'utente da stampare.

  Pre-condizione:
   ut deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica all'utente.

 Effetti:
   Se ut è valido, stampa il nome dell'utente con printf,
   passato dalla funzione prendi_nome, dichiarata in utente.h.
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
 Salva le informazioni di un utente su file in modalità append.

 Parametri:
   nome_file: nome del file dove salvare i dati.
   ut: puntatore all'utente da salvare.

  Pre-condizione:
   nome_file e ut devono essere puntatori validi.

 Post-condizione:
   Le informazioni dell'utente vengono scritte nel file.

 Effetti:
   Se il file si apre correttamente e ut non è NULL,
   scrive nome ed email su una nuova riga nel file.
   Altrimenti stampa un messaggio di errore.
*/
void salva_utente_su_file(char *nome_file, ptr_utente ut)
{
    FILE *file = fopen(nome_file, "a");
    // Controlla se file e utente sono diversi da NULL.
    if (file && ut){ 
        fprintf(file, "%s %s\n", prendi_nome(ut), prendi_email(ut));
        fclose(file);
    } else printf("\nErrore salvataggio...");
        
    
}


/*
 Funzione: carica_utente_da_file
 -------------------------------
 Carica gli utenti da un file e li inserisce nella tabella hash.

 Parametri:
   nome_file: nome del file da cui leggere gli utenti.
   h: puntatore alla tabella hash dove inserire gli utenti caricati.

  Pre-condizione:
   nome_file e h devono essere puntatori validi.

 Post-condizione:
   Un utente viene caricato dal file e inserito nella tabella hash.

 Effetti:
   Per ogni coppia nome-email letta dal file, crea un nuovo utente
   e lo inserisce nella tabella hash.
   Se il file non si apre, la funzione termina senza fare nulla.
*/
void carica_utente_da_file(const char *nome_file, ptr_hash h)
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
        inserisci_hash(h, inizia_utente(nome, email));
    }
}


/*
 Funzione: libera_utente
 -----------------------
 Libera la memoria allocata per un utente.

 Parametri:
   ut: puntatore all'utente da liberare.

  Pre-condizione:
   ut deve essere un puntatore valido.

 Post-condizione:
   La memoria occupata dall'utente è liberata.

 Effetti:
   Se ut è diverso da NULL, ne libera la memoria.
*/
void libera_utente(ptr_utente ut)
{
    if(ut){
        free(ut);
    }
}