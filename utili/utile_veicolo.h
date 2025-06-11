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

 Legge da file le informazioni relative ai veicoli e li inserisce nella tabella hash.

 Parametri:
    nome_file: stringa contenente il nome del file da cui leggere i dati dei veicoli
    h: puntatore alla tabella hash in cui inserire i veicoli

 Pre-condizioni:
    `nome_file` deve essere una stringa valida e non NULL.
    `h` deve essere un puntatore valido a una tabella hash inizializzata.

 Post-condizioni:
    Tutti i veicoli letti dal file vengono inseriti nella tabella hash.

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Apre un file in lettura.
    Alloca memoria dinamica per ogni veicolo letto.
    In caso di errore nell'apertura del file, termina il programma con `exit(1)`.
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

int stampa_veicoli_disponibili(ptr_hash_veicoli h);

int aggiorna_prenotazioni_veicoli(ptr_hash_veicoli h);

int aggiorna_file_prenotazione_veicoli(ptr_hash_veicoli h);


#endif