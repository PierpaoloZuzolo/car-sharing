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
 Crea e inizializza un nuovo veicolo con i dati specificati.

 Parametri:
   marca_veicolo: stringa contenente la marca del veicolo
   modello_veicolo: stringa contenente il modello del veicolo
   targa_veicolo: stringa contenente la targa del veicolo
   posizione_veicolo: stringa che rappresenta la posizione attuale del veicolo

 Pre-condizione:
   Tutti i parametri devono essere stringhe valide terminate da '\0'.

 Post-condizione:
   Alloca dinamicamente una struttura veicolo e copia i dati ricevuti nei rispettivi campi.

 Ritorna:
   Un puntatore alla nuova struttura veicolo allocata,
   oppure NULL in caso di errore di allocazione.
*/
ptr_veicolo inizia_veicolo(const char *marca_veicolo, const char *modello_veicolo, const char *targa_veicolo, const char *posizione_veicolo);


/*
 Funzione: prendi_marca
 ----------------------
 Restituisce la marca di un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare la marca

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente la marca del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_marca(ptr_veicolo ve);


/*
 Funzione: prendi_modello
 ------------------------
 Restituisce il modello di un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare il modello

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente il modello del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_modello(ptr_veicolo ve);


/*
 Funzione: prendi_targa
 ----------------------
 Restituisce la targa di un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare la targa

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente la targa del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_targa(ptr_veicolo ve);


/*
 Funzione: prendi_posizione
 --------------------------
 Restituisce la posizione attuale del veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare la posizione

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente la posizione attuale del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_posizione(ptr_veicolo ve);


/*
 Funzione: prendi_stato
 ----------------------
 Restituisce lo stato corrente del veicolo (es. "disponibile", "occupato").

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare lo stato

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente lo stato del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_stato(ptr_veicolo ve);


/*
 Funzione: prendi_prenotazioni
 -----------------------------
 Restituisce il puntatore alla struttura delle prenotazioni associate a un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare le prenotazioni

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica ai dati del veicolo o delle prenotazioni

 Ritorna:
   Un puntatore alla lista delle prenotazioni associate al veicolo,
   oppure NULL se il puntatore ve è NULL
*/
ptr_prenotazione prendi_prenotazioni(ptr_veicolo ve);


/*
 Funzione: imposta_stato_veicolo
 -----------------------
 Imposta lo stato di un veicolo.

 Parametri:
   ve: puntatore al veicolo da modificare.
   stato: stringa che rappresenta il nuovo stato.

 Pre-condizione:
   ve deve essere un puntatore valido.
   stato deve essere una stringa valida.

 Post-condizione:
   Lo stato interno del veicolo è aggiornato con la nuova stringa.
   La stringa è sempre terminata correttamente.

 Effetti:
   Modifica il campo stato all’interno della struttura veicolo.
*/
void imposta_stato_veicolo(ptr_veicolo ve, const char *stato);


#endif