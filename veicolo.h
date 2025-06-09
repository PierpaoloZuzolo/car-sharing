/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#ifndef VEICOLO_H
#define VEICOLO_H

#define DIM_STATO 20

#include "array_prenotazione.h"

/*
 Tipo astratto di dato: prenotazione
 ------------------------------------
 Struttura che rappresenta una prenotazione associata a un veicolo.
*/
typedef struct veicolo *ptr_veicolo;


/*
 Funzione: inizia_veicolo
 ------------------------

 Crea e inizializza una nuova struttura veicolo con i dati forniti,
 carica le prenotazioni associate e imposta lo stato di disponibilità.

 Parametri:
    marca_veicolo: stringa contenente la marca del veicolo
    modello_veicolo: stringa contenente il modello del veicolo
    targa_veicolo: stringa contenente la targa del veicolo
    posizione_veicolo: stringa contenente la posizione del veicolo

 Pre-condizioni:
    Tutti i parametri devono essere stringhe valide e non NULL.

 Post-condizioni:
    Restituisce un puntatore a una nuova struttura veicolo inizializzata,
    oppure NULL se l'allocazione fallisce.

 Ritorna:
    Puntatore a una struttura `veicolo` allocata dinamicamente, o NULL in caso di errore

 Side-effect:
    Alloca memoria dinamica e può caricare dati da file per le prenotazioni.
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