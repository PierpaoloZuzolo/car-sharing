/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#ifndef UTILE_VEICOLO_H
#define UTILE_VEICOLO_H

#include "Modello_veicolo/veicolo.h"
#include "ADT_hash/hash_veicoli.h"


/*
 Funzione: stampa_veicolo
 ------------------------

 Visualizza le informazioni principali del veicolo e gli orari disponibili.


 Parametri:
    ve: puntatore alla struttura `veicolo` da stampare

 Pre-condizioni:
    Il puntatore `ve` deve essere valido (non NULL)

 Post-condizioni:
    Nessuna

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Scrive su standard output le informazioni relative al veicolo
    e gli orari disponibili letti dalla struttura delle prenotazioni
 */
void stampa_veicolo(ptr_veicolo ve);


/*
  Funzione: carica_veicoli_da_file
  --------------------------------

  Carica i dati dei veicoli da un file di testo e li inserisce in una tabella hash.

  Parametri:
     nome_file: nome del file contenente i dati dei veicoli
     h: puntatore alla tabella hash dei veicoli
     percorso_file: percorso opzionale della cartella in cui si trova il file

  Pre-condizioni:
     nome_file e h devono essere non NULL

  Post-condizioni:
     se il file è valido, i veicoli vengono letti e inseriti nella tabella hash;
     le righe mal formattate vengono ignorate, e viene stampato un messaggio d'errore.

  Ritorna:
     1 se il file è stato aperto correttamente (indipendentemente dal contenuto);
     0 se il file non può essere aperto.

  Side-effect:
     apre e legge da un file;
     può allocare memoria dinamicamente per ogni veicolo e inserirlo nella tabella hash;
     stampa su stderr eventuali messaggi d’errore se la creazione o l’inserimento fallisce.
 */

int carica_veicoli_da_file(const char *nome_file, ptr_hash_veicoli h, const char *percorso_file); // CAMBIARE SPECIFICA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11



/*
 Funzione: libera_veicolo
 ------------------------

 Libera la memoria allocata per una struttura veicolo, comprese le sue prenotazioni.

 Parametri:
    ve: puntatore alla struttura `veicolo` da liberare

 Pre-condizioni:
    `ve` può essere NULL o un puntatore valido a una struttura `veicolo`.

 Post-condizioni:
    Se `ve` è valido, tutta la memoria allocata per il veicolo e le sue prenotazioni viene liberata.

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Dealloca memoria dinamica per la struttura veicolo e le sue prenotazioni.
 */
void libera_veicolo(ptr_veicolo ve);


/*
  Funzione: aggiorna_stato_veicolo
  --------------------------------

  Aggiorna lo stato attuale di un veicolo in base alla sua disponibilità per il giorno corrente.

  Parametri:
     ve: puntatore alla struttura del veicolo da aggiornare

  Pre-condizioni:
     ve != NULL

  Post-condizioni:
     lo stato del veicolo è aggiornato in base alla disponibilità giornaliera

  Ritorna:
     true se l’aggiornamento è stato eseguito con successo;
     false se il puntatore al veicolo è NULL.

  Side-effect:
     modifica il campo "stato" del veicolo.
 */

bool aggiorna_stato_veicolo(ptr_veicolo ve);


/*
 Funzione: veicolo_disponibile
 -----------------------------

 Verifica se un veicolo è attualmente disponibile in base al suo stato.

 Parametri:
    ve: puntatore a una struttura `veicolo` di cui si vuole verificare la disponibilità.

 Pre-condizioni:
    Il parametro `ve` deve essere un puntatore valido o NULL.

 Post-condizioni:
    Nessuna modifica agli oggetti passati.

 Ritorna:
    `true` se il campo `stato` del veicolo è "disponibile", `false` altrimenti
    (incluso il caso in cui `ve` sia NULL).

 Side-effect:
    Nessuno.
 */
bool veicolo_disponibile(ptr_veicolo ve);



/*
 Funzione: stampa_veicoli_disponibili
 ------------------------------------

 Scansiona la tabella hash dei veicoli e stampa a video tutti i veicoli attualmente disponibili.

 Implementazione:
    - Ottiene tutti i veicoli presenti nella tabella hash tramite `ottieni_valori_hash`.
    - Per ogni veicolo controlla la disponibilità chiamando `veicolo_disponibile`.
    - Se disponibile, stampa i dati del veicolo tramite `stampa_veicolo`.
    - Restituisce il numero di veicoli disponibili stampati.

 Parametri:
    h - puntatore alla tabella hash dei veicoli (ptr_hash_veicoli).

 Pre-condizioni:
    - La tabella hash `h` deve essere inizializzata e valida.
    - Le funzioni `veicolo_disponibile` e `stampa_veicolo` devono essere definite e funzionanti.

 Post-condizioni:
    - Stampa a video i veicoli disponibili.
    - Restituisce il numero totale di veicoli disponibili stampati.
    - Libera la memoria allocata da `ottieni_valori_hash`.

 Ritorna:
    - Il numero di veicoli disponibili stampati.
    - 0 se la tabella hash è vuota o non valida.

 Side-effect:
    - Stampa su stdout le informazioni dei veicoli disponibili.
    - Libera la memoria allocata temporaneamente per la lista dei veicoli.
*/
int stampa_veicoli_disponibili(ptr_hash_veicoli h);

/*
  Funzione: aggiorna_prenotazioni_veicoli
  ---------------------------------------

  Aggiorna le prenotazioni di tutti i veicoli presenti nella tabella hash.

  Parametri:
     h: puntatore alla tabella hash contenente i veicoli

  Pre-condizioni:
     h != NULL

  Post-condizioni:
     le prenotazioni e lo stato di ogni veicolo sono aggiornati in base alla data e all'ora correnti

  Ritorna:
     1 se l’operazione è stata eseguita correttamente;
     0 in caso di errore (hash NULL o vuota)

  Side-effect:
     modifica le strutture interne di prenotazioni e stato di ogni veicolo;
     libera la memoria dell’array temporaneo ottenuto da `ottieni_valori_hash`.
*/
int aggiorna_prenotazioni_veicoli(ptr_hash_veicoli h);

/*
  Funzione: aggiorna_file_prenotazione_veicoli
  --------------------------------------------

  Salva su file le prenotazioni aggiornate di tutti i veicoli nella tabella hash.

  Parametri:
     h: puntatore alla tabella hash contenente i veicoli
     percorso_file: percorso della cartella in cui salvare i file delle prenotazioni

  Pre-condizioni:
     h != NULL

  Post-condizioni:
     i file delle prenotazioni dei veicoli sono aggiornati sul disco

  Ritorna:
     1 se l’operazione ha avuto successo;
     0 in caso di errore (hash NULL o vuota)

  Side-effect:
     scrive su file le prenotazioni di ogni veicolo;
     libera la memoria dell’array temporaneo ottenuto da `ottieni_valori_hash`.
*/
int aggiorna_file_prenotazione_veicoli(ptr_hash_veicoli h, const char *percorso_file);

/*
  Funzione: carica_prenotazioni_veicoli_da_file
  ---------------------------------------------

  Carica da file le prenotazioni associate a ciascun veicolo nella tabella hash.

  Parametri:
     h: puntatore alla tabella hash contenente i veicoli
     percorso_file: percorso della cartella in cui si trovano i file delle prenotazioni

  Pre-condizioni:
     h != NULL

  Post-condizioni:
     le strutture prenotazioni dei veicoli sono caricate con i dati contenuti nei file

  Ritorna:
     1 se l’operazione ha avuto successo almeno parzialmente;
     0 in caso di errore (hash NULL o vuota)

  Side-effect:
     legge da file le prenotazioni di ogni veicolo;
     stampa messaggi di avviso in caso di errori di caricamento;
     libera la memoria dell’array temporaneo ottenuto da `ottieni_valori_hash`.
*/
int carica_prenotazioni_veicoli_da_file(ptr_hash_veicoli h, const char *percorso_file);

#endif