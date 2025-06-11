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

 Carica i veicoli da un file di testo e li inserisce nella tabella hash dei veicoli.
 Per ogni veicolo letto dal file, viene creata una struttura `veicolo` e caricata la relativa disponibilità prenotazioni.

 Parametri:
    nome_file - stringa contenente il percorso/nome del file da cui caricare i veicoli.
    h         - puntatore alla tabella hash di veicoli (ptr_hash_veicoli) in cui inserire i veicoli caricati.

 Pre-condizioni:
    - Il puntatore `nome_file` deve essere valido e puntare a un file esistente e accessibile in lettura.
    - La tabella hash `h` deve essere già inizializzata.

 Post-condizioni:
    - Inserisce in `h` tutti i veicoli validi letti dal file.
    - Se il file non esiste o si verifica un errore di apertura, la funzione restituisce 0.
    - Se il caricamento ha successo, restituisce 1.

 Ritorna:
    - 1 se il caricamento è avvenuto con successo.
    - 0 in caso di errore di apertura file.

 Side-effect:
    - Alloca dinamicamente memoria per ciascun veicolo caricato.
    - Inserisce i veicoli nella tabella hash.
    - Stampa messaggi di errore su stderr in caso di problemi.
*/
int carica_veicoli_da_file(const char *nome_file, ptr_hash_veicoli h); // CAMBIARE SPECIFICA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11



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

 Aggiorna lo stato di disponibilità del veicolo in base alle prenotazioni del giorno corrente.

 Parametri:
    ve: puntatore alla struttura `veicolo` da aggiornare

 Pre-condizioni:
    `ve` deve essere un puntatore valido a una struttura `veicolo`.

 Post-condizioni:
    Lo stato del veicolo (`ve->stato`) viene aggiornato coerentemente con la sua disponibilità.

 Ritorna:
    `true` se il veicolo è *non disponibile* oggi, `false` se disponibile o se `ve` è NULL.

 Side-effect:
    Modifica il campo `stato` all'interno della struttura `veicolo`.
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
 Funzione: aggiorna_prenotazione_veicolo
 ---------------------------------------

 Aggiorna lo stato delle prenotazioni di un veicolo, blocca le celle non più prenotabili 
 in base all'orario corrente, salva le prenotazioni aggiornate su file e aggiorna lo stato 
 del veicolo (disponibile o non disponibile).

 Parametri:
    ve: puntatore al veicolo di cui aggiornare le prenotazioni e lo stato.

 Pre-condizioni:
    ve deve essere un puntatore valido a un veicolo con prenotazioni valide.

 Post-condizioni:
    Le prenotazioni del veicolo sono aggiornate, salvate su file e lo stato del veicolo è aggiornato.

 Ritorna:
    Nessun valore di ritorno (void).

 Side-effect:
    Modifica le prenotazioni associate al veicolo.
    Scrive su file i dati aggiornati delle prenotazioni.
    Modifica lo stato interno del veicolo.
*/

void aggiorna_prenotazione_veicolo(ptr_veicolo ve); // DA TOGLIERE

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

 Aggiorna lo stato delle prenotazioni per tutti i veicoli presenti nella tabella hash.

 Parametri:
    h - puntatore alla tabella hash dei veicoli (ptr_hash_veicoli).

 Pre-condizioni:
    - La tabella hash `h` deve essere valida e inizializzata.
    - Le funzioni `blocca_celle_passate` e `aggiorna_stato_veicolo` devono essere definite e funzionanti.

 Post-condizioni:
    - Le prenotazioni passate vengono bloccate.
    - Lo stato di ogni veicolo viene aggiornato in base alle nuove prenotazioni.

 Ritorna:
    - 1 se l'operazione è andata a buon fine.
    - 0 in caso di errore (es. tabella hash vuota o non valida).

 Side-effect:
    - Modifica le strutture di prenotazione e lo stato dei veicoli nella tabella hash.
    - Libera la memoria temporaneamente allocata da `ottieni_valori_hash`.
*/
int aggiorna_prenotazioni_veicoli(ptr_hash_veicoli h);

/*
 Funzione: aggiorna_file_prenotazione_veicoli
 --------------------------------------------

 Salva su file le prenotazioni aggiornate di tutti i veicoli presenti nella tabella hash.

 Parametri:
    h - puntatore alla tabella hash dei veicoli (ptr_hash_veicoli).

 Pre-condizioni:
    - La tabella hash `h` deve essere valida e inizializzata.
    - La funzione `salva_prenotazioni_su_file` deve essere definita e funzionante.

 Post-condizioni:
    - I file di prenotazione associati a ciascun veicolo sono aggiornati.

 Ritorna:
    - 1 se l'operazione è andata a buon fine.
    - 0 in caso di errore (es. tabella hash vuota o non valida).

 Side-effect:
    - Sovrascrive i file di prenotazione per ciascun veicolo.
    - Libera la memoria temporaneamente allocata da `ottieni_valori_hash`.
*/
int aggiorna_file_prenotazione_veicoli(ptr_hash_veicoli h);


#endif