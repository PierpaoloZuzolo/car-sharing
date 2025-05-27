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
 Salva i dati di un utente su due file:
  - Un file generico (append) che elenca nome ed email di tutti gli utenti
  - Un file dedicato all'utente, con nome "nome_utente.txt",
    contenente i dettagli specifici (nome, email, sconto, ecc.)

 Parametri:
   nome_file: percorso del file generico dove aggiungere utente
   ut: puntatore alla struttura utente da salvare

 Pre-condizione:
   ut deve essere un puntatore valido

 Post-condizione:
   I file vengono creati/aggiornati con i dati dell'utente

 Valore di ritorno:
   Nessuno (void)
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

    // Creazione file dedicato "nome_utente.txt"
    char nome_file_utente[256];
    snprintf(nome_file_utente, sizeof(nome_file_utente), "%s.txt", prendi_nome(ut));

    FILE *file_utente = fopen(nome_file_utente, "w");  // scrittura, sovrascrive se esiste
    if (file_utente) {
        // Qui puoi salvare i dati specifici dell'utente (es. sconto, prenotazioni, ecc.)
        fprintf(file_utente, "Nome: %s\n", prendi_nome(ut));
        fprintf(file_utente, "Email: %s\n", prendi_email(ut));
        // Per esempio, sconto di default
        fprintf(file_utente, "%d\n", 0);

        fclose(file_utente);
    } else {
        printf("\nErrore nella creazione del file utente dedicato.\n");
    }
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