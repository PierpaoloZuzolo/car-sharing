/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "array_prenotazione.h"
#include "utile_array_prenotazione.h"


struct veicolo{
    char marca[30];
    char modello[40];
    char targa[8];
    char posizione[60];
    char stato[20];

  
   ptr_prenotazione prenotazione_veicolo;
};


/*
 Funzione: inizia_veicolo
 ------------------------

 Crea e inizializza una nuova struttura veicolo con i dati forniti,
 carica le prenotazioni associate e imposta lo stato di disponibilità.

 Implementazione:
    Alloca memoria per un nuovo veicolo, copia i dati delle stringhe passate
    nei rispettivi campi della struttura.
    Inizializza la struttura delle prenotazioni e le carica da file in base alla targa.
    Verifica la disponibilità del veicolo per oggi e aggiorna lo stato di conseguenza.

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
ptr_veicolo inizia_veicolo(const char *marca_veicolo, const char *modello_veicolo, const char *targa_veicolo, const char *posizione_veicolo)
{
    ptr_veicolo nuovo_veicolo = malloc(sizeof(struct veicolo));
    if(nuovo_veicolo){
        strncpy(nuovo_veicolo->marca, marca_veicolo, sizeof(nuovo_veicolo->marca) - 1);
        nuovo_veicolo->marca[sizeof(nuovo_veicolo->marca) - 1] = '\0';

        strncpy(nuovo_veicolo->modello, modello_veicolo, sizeof(nuovo_veicolo->modello) - 1);
        nuovo_veicolo->modello[sizeof(nuovo_veicolo->modello) - 1] = '\0';

        strncpy(nuovo_veicolo->targa, targa_veicolo, sizeof(nuovo_veicolo->targa) - 1);
        nuovo_veicolo->targa[sizeof(nuovo_veicolo->targa) - 1] = '\0';

        strncpy(nuovo_veicolo->posizione, posizione_veicolo, sizeof(nuovo_veicolo->posizione) - 1);
        nuovo_veicolo->posizione[sizeof(nuovo_veicolo->posizione) - 1] = '\0';

       
       nuovo_veicolo->prenotazione_veicolo = inizializza_prenotazioni();
        carica_prenotazioni_da_file(nuovo_veicolo->prenotazione_veicolo, nuovo_veicolo->targa);

       
        if(veicolo_disponibile_oggi(nuovo_veicolo->prenotazione_veicolo))

            strcpy(nuovo_veicolo->stato, "disponibile");
        else
            strcpy(nuovo_veicolo->stato, "non disponibile");
    } 
    return nuovo_veicolo;
}


/*
 Funzione: prendi_marca
 ----------------------

 Restituisce la marca del veicolo.

 Implementazione:
    Controlla se il puntatore al veicolo è valido.
    Se sì, restituisce la stringa contenente la marca,
    altrimenti restituisce NULL.

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
char *prendi_marca(ptr_veicolo ve)
{
    // Restituisce la marca se il veicolo è valido, altrimenti NULL
    return ve ? ve->marca : NULL;
}


/*
 Funzione: prendi_modello
 ------------------------

 Restituisce il modello del veicolo.

 Implementazione:
    Verifica se il puntatore al veicolo è valido.
    Se sì, restituisce la stringa contenente il modello,
    altrimenti restituisce NULL.

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
char *prendi_modello(ptr_veicolo ve)
{
    // Restituisce il modello se il veicolo è valido, altrimenti NULL
    return ve ? ve->modello : NULL;
}


/*
 Funzione: prendi_targa
 ----------------------

 Restituisce la targa del veicolo.

 Implementazione:
    Verifica se il puntatore al veicolo è valido.
    Se sì, restituisce la stringa contenente la targa,
    altrimenti restituisce NULL.

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
char *prendi_targa(ptr_veicolo ve)
{
    // Restituisce la targa se il veicolo è valido, altrimenti NULL
    return ve ? ve->targa : NULL;
}


/*
 Funzione: prendi_posizione
 --------------------------

 Restituisce la posizione attuale del veicolo.

 Implementazione:
    Controlla se il puntatore al veicolo è valido,
    quindi restituisce la stringa contenente la posizione.
    Se il veicolo è NULL, restituisce NULL.

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
char *prendi_posizione(ptr_veicolo ve)
{
    // Restituisce la posizione se il veicolo è valido, altrimenti NULL
    return ve ? ve->posizione : NULL;
}


/*
 Funzione: prendi_stato
 ----------------------

 Restituisce lo stato corrente del veicolo.

 Implementazione:
    Verifica se il puntatore al veicolo è valido,
    quindi restituisce la stringa contenente lo stato.
    Se il veicolo è NULL, restituisce NULL.

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
char *prendi_stato(ptr_veicolo ve)
{
    // Restituisce lo stato se il veicolo è valido, altrimenti NULL
    return ve ? ve->stato : NULL;
}


/*
 Funzione: prendi_prenotazioni
 -----------------------------

 Restituisce il puntatore alla lista delle prenotazioni associate a un veicolo.

 Implementazione:
    Controlla se il puntatore al veicolo è valido,
    quindi ritorna il puntatore alla struttura delle prenotazioni.
    Se il veicolo è NULL, restituisce NULL.

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
ptr_prenotazione prendi_prenotazioni(ptr_veicolo ve)
{
    return ve ? ve->prenotazione_veicolo : NULL;
}


/*
 Funzione: imposta_stato_veicolo
 -------------------------------

 Imposta lo stato del veicolo con la stringa fornita.

 Implementazione:
    Se il puntatore al veicolo e la stringa stato sono validi,
    copia la stringa nel campo stato del veicolo, garantendo
    la corretta terminazione della stringa.

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
void imposta_stato_veicolo(ptr_veicolo ve, const char *stato)
{
    if (ve && stato) {
        strncpy(ve->stato, stato, DIM_STATO - 1);
        ve->stato[DIM_STATO - 1] = '\0'; // garantisce terminazione stringa
    }
}
