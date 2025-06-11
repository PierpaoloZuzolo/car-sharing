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

  Salva le informazioni di un utente su un file di testo, in modalità append.

  Implementazione:
     Costruisce il nome completo del file a partire dal nome base e, se fornito, dal percorso.
     Apre il file in modalità "append" ("a") per aggiungere l'utente alla fine del file.
     Scrive su una nuova riga il nome e l'email dell’utente separati da uno spazio.

  Parametri:
     nome_file: nome base del file (senza estensione)
     ut: puntatore alla struttura utente da salvare
     percorso_file: percorso opzionale della cartella in cui salvare il file

  Pre-condizioni:
     ut != NULL
     nome_file != NULL e non vuoto

  Post-condizioni:
     se il file viene aperto correttamente, i dati dell'utente sono scritti in append;
     altrimenti, non viene scritto nulla.

  Ritorna:
     1 se il salvataggio ha avuto successo;
     0 in caso di errore (es. parametri non validi o apertura file fallita)

  Side-effect:
     apre (o crea) e scrive su un file di testo;
     aggiunge una nuova riga contenente i dati dell'utente.
 */

int salva_utente_su_file(char *nome_file, ptr_utente ut, const char *percorso_file)
{
   if (!ut || !nome_file || strlen(nome_file) == 0) {
       //  printf("Lista o nome utente non validi.\n");
        return 0;
    }

    char nome_file_completo[200];
    if (percorso_file && strlen(percorso_file) > 0) {
        snprintf(nome_file_completo, sizeof(nome_file_completo), "%s/%s", percorso_file, nome_file);
    } else {
        snprintf(nome_file_completo, sizeof(nome_file_completo), "%s", nome_file);
    }

    // Salvataggio su file generale (append)
    FILE *file = fopen(nome_file_completo, "a");
    if (file) {
        fprintf(file, "%s %s\n", prendi_nome(ut), prendi_email(ut));
        fclose(file);
        return 1;
    } else {
        //printf("\nErrore salvataggio file utenti generico.\n");
        return 0;
    }

}


/*
  Funzione: carica_utenti_da_file
  -------------------------------

  Carica da un file di testo gli utenti registrati e li inserisce in una tabella hash.

  Implementazione:
     Costruisce il nome completo del file a partire dal nome base e, se fornito, dal percorso.
     Apre il file in modalità lettura ("r").
     Per ogni riga, legge nome ed email dell'utente, crea una nuova struttura utente
     e la inserisce nella tabella hash tramite la funzione `inserisci_utente_in_hash`.

  Parametri:
     nome_file: nome del file contenente gli utenti (con o senza estensione)
     h: puntatore alla tabella hash degli utenti
     percorso_file: percorso opzionale della cartella in cui si trova il file

  Pre-condizioni:
     nome_file != NULL
     h != NULL

  Post-condizioni:
     se il file è valido e contiene righe ben formattate (nome email),
     gli utenti vengono inseriti nella tabella hash;
     le righe mal formattate vengono ignorate.

  Ritorna:
     1 se il file è stato aperto correttamente e almeno un'operazione di lettura è stata tentata;
     0 se il file non può essere aperto o i parametri sono invalidi.

  Side-effect:
     apre e legge da un file su disco;
     può allocare memoria dinamicamente per ogni utente letto e inserirlo nella tabella hash.
 */

int carica_utenti_da_file(const char *nome_file, ptr_hash_utenti h, const char *percorso_file)
{
    if (!nome_file || !h) return 0;

    char nome_file_completo[200];
    if (percorso_file && strlen(percorso_file) > 0) {
        snprintf(nome_file_completo, sizeof(nome_file_completo), "%s/%s", percorso_file, nome_file);
    } else {
        snprintf(nome_file_completo, sizeof(nome_file_completo), "%s", nome_file);
    }

    FILE *file = fopen(nome_file_completo, "r");
    if (!file) {
        return 0;
    }

    char nome[51], email[101];
    while (fscanf(file, "%50s %100s", nome, email) == 2) {
        ptr_utente nuovo = inizia_utente(nome, email);
        if (nuovo) {
            inserisci_utente_in_hash(h, nuovo);
        }
    }

    fclose(file);
    return 1;
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