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

  Salva le informazioni di un utente su un file di testo, in modalità append.

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

int salva_utente_su_file(char *nome_file, ptr_utente ut, const char *percorso_file);

/*
  Funzione: carica_utenti_da_file
  -------------------------------

  Carica da un file di testo gli utenti registrati e li inserisce in una tabella hash.

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

int carica_utenti_da_file(const char *nome_file, ptr_hash_utenti h, const char *percorso_file);



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