/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "ADT_array/array_prenotazione.h"
#include "utili/utile_array_prenotazione.h"


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

 Crea e inizializza una nuova struttura veicolo con i dati forniti:
    - marca
    - modello
    - targa
    - posizione
 Inizializza inoltre la struttura interna delle prenotazioni associata al veicolo.

 Implementazione:
    - Alloca dinamicamente una nuova struttura `veicolo`.
    - Copia le stringhe ricevute nei campi corrispondenti della struttura.
    - Inizializza il campo prenotazione con `inizializza_prenotazioni()`.
    - Imposta lo stato iniziale a "sconosciuto".

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
        //carica_prenotazioni_da_file(nuovo_veicolo->prenotazione_veicolo, nuovo_veicolo->targa);

       /*
        if(veicolo_disponibile_oggi(nuovo_veicolo->prenotazione_veicolo))

            strcpy(nuovo_veicolo->stato, "disponibile");
        else
            strcpy(nuovo_veicolo->stato, "non disponibile");
         */
        strcpy(nuovo_veicolo->stato, "sconosciuto");
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
