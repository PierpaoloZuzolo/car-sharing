/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#ifndef VEICOLO_H
#define VEICOLO_H

#define DIM_STATO 20

#include "ADT_array/array_prenotazione.h"

/*
 Tipo astratto di dato: prenotazione
 ------------------------------------
 Struttura che rappresenta una prenotazione associata a un veicolo.
*/
typedef struct veicolo *ptr_veicolo;


/*
 Funzione: inizia_veicolo
 ------------------------

 Crea e inizializza una nuova struttura veicolo con i dati forniti:
    - marca
    - modello
    - targa
    - posizione
 Inizializza inoltre la struttura interna delle prenotazioni associata al veicolo.

 Parametri:
    marca_veicolo    - puntatore a stringa contenente la marca del veicolo
    modello_veicolo  - puntatore a stringa contenente il modello del veicolo
    targa_veicolo    - puntatore a stringa contenente la targa del veicolo
    posizione_veicolo- puntatore a stringa contenente la posizione del veicolo

 Pre-condizioni:
    - Tutti i puntatori a stringa devono essere validi e non NULL.
    - Le stringhe devono rispettare le dimensioni massime previste nei rispettivi campi della struttura.

 Post-condizioni:
    - Restituisce un nuovo puntatore `ptr_veicolo` completamente inizializzato, oppure NULL in caso di errore di allocazione.

 Ritorna:
    - Puntatore alla nuova struttura veicolo (`ptr_veicolo`), oppure NULL se l’allocazione fallisce.

 Side-effect:
    - Alloca memoria dinamica per il veicolo e per la struttura di prenotazione associata.
*/
ptr_veicolo inizia_veicolo(const char *marca_veicolo, const char *modello_veicolo, const char *targa_veicolo, const char *posizione_veicolo);


/*
 Funzione: prendi_marca
 ----------------------

 Restituisce la marca del veicolo.

 Parametri:
    ve: puntatore alla struttura veicolo

 Pre-condizioni:
    Il puntatore `ve` può essere NULL.

 Post-condizioni:
    Nessuna modifica allo stato delle strutture.

 Ritorna:
    Puntatore alla stringa della marca del veicolo,
    oppure NULL se il veicolo è NULL.

 Side-effect:
    Nessuno.
*/
char *prendi_marca(ptr_veicolo ve);


/*
 Funzione: prendi_modello
 ------------------------

 Restituisce il modello del veicolo.

 Parametri:
    ve: puntatore alla struttura veicolo

 Pre-condizioni:
    Il puntatore `ve` può essere NULL.

 Post-condizioni:
    Nessuna modifica allo stato delle strutture.

 Ritorna:
    Puntatore alla stringa del modello del veicolo,
    oppure NULL se il veicolo è NULL.

 Side-effect:
    Nessuno.
*/
char *prendi_modello(ptr_veicolo ve);


/*
 Funzione: prendi_targa
 ----------------------

 Restituisce la targa del veicolo.

 Parametri:
    ve: puntatore alla struttura veicolo

 Pre-condizioni:
    Il puntatore `ve` può essere NULL.

 Post-condizioni:
    Nessuna modifica allo stato delle strutture.

 Ritorna:
    Puntatore alla stringa della targa del veicolo,
    oppure NULL se il veicolo è NULL.

 Side-effect:
    Nessuno.
*/
char *prendi_targa(ptr_veicolo ve);


/*
 Funzione: prendi_posizione
 --------------------------

 Restituisce la posizione attuale del veicolo.

 Parametri:
    ve: puntatore alla struttura veicolo

 Pre-condizioni:
    Il puntatore `ve` può essere NULL.

 Post-condizioni:
    Nessuna modifica allo stato delle strutture.

 Ritorna:
    Puntatore alla stringa della posizione del veicolo,
    oppure NULL se il veicolo è NULL.

 Side-effect:
    Nessuno.
*/
char *prendi_posizione(ptr_veicolo ve);


/*
 Funzione: prendi_stato
 ----------------------

 Restituisce lo stato corrente del veicolo.

 Parametri:
    ve: puntatore alla struttura veicolo

 Pre-condizioni:
    Il puntatore `ve` può essere NULL.

 Post-condizioni:
    Nessuna modifica allo stato delle strutture.

 Ritorna:
    Puntatore alla stringa dello stato del veicolo,
    oppure NULL se il veicolo è NULL.

 Side-effect:
    Nessuno.
*/
char *prendi_stato(ptr_veicolo ve);


/*
 Funzione: prendi_prenotazioni
 -----------------------------

 Restituisce il puntatore alla lista delle prenotazioni associate a un veicolo.

 Parametri:
    ve: puntatore alla struttura veicolo

 Pre-condizioni:
    Il puntatore `ve` può essere NULL.

 Post-condizioni:
    Nessuna modifica allo stato delle strutture.

 Ritorna:
    Puntatore alla lista delle prenotazioni associata al veicolo,
    oppure NULL se il veicolo è NULL.

 Side-effect:
    Nessuno.
*/
ptr_prenotazione prendi_prenotazioni(ptr_veicolo ve);


/*
 Funzione: imposta_stato_veicolo
 -------------------------------

 Imposta lo stato del veicolo con la stringa fornita.

 Parametri:
    ve: puntatore alla struttura veicolo da modificare
    stato: stringa contenente il nuovo stato da assegnare

 Pre-condizioni:
    Il puntatore `ve` e la stringa `stato` devono essere non NULL.

 Post-condizioni:
    Il campo stato della struttura veicolo è aggiornato con la nuova stringa.

 Ritorna:
    Nessun valore di ritorno.

 Side-effect:
    Modifica il campo `stato` della struttura veicolo.
*/
void imposta_stato_veicolo(ptr_veicolo ve, const char *stato);


#endif