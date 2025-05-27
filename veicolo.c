#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "lista_veicoli.h"
#include "prenotazione.h"
#include "utile_prenotazione.h"


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
 Crea e inizializza un nuovo veicolo con i dati forniti.
 Utilizzata per costruire un oggetto veicolo e aggiungerlo alla lista.

 Parametri:
   marca_veicolo: stringa con la marca del veicolo
   modello_veicolo: stringa con il modello del veicolo
   targa_veicolo: stringa con la targa del veicolo
   posizione_veicolo: stringa con la posizione attuale del veicolo

  Pre-condizione:
   Tutti i parametri devono essere stringhe valide terminate da '\0'.

 Post-condizione:
   Alloca dinamicamente una struttura veicolo e copia i dati ricevuti nei rispettivi campi.

 Ritorna:
   Un puntatore al nuovo veicolo allocato, oppure NULL in caso di errore.
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

 Parametri:
   ve: puntatore al veicolo

  Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa con la marca, oppure NULL se il puntatore è invalido.
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

 Parametri:
   ve: puntatore al veicolo

  Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa con il modello, oppure NULL se il puntatore è invalido.
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

 Parametri:
   ve: puntatore al veicolo

  Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa con la targa, oppure NULL se il puntatore è invalido.
*/
char *prendi_targa(ptr_veicolo ve)
{
    // Restituisce la targa se il veicolo è valido, altrimenti NULL
    return ve ? ve->targa : NULL;
}


/*
 Funzione: prendi_posizione
 ----------------------
 Restituisce la posizione del veicolo.

 Parametri:
   ve: puntatore al veicolo

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo
   
 Ritorna:
   Una stringa con la posizione, oppure NULL se il puntatore è invalido.
*/
char *prendi_posizione(ptr_veicolo ve)
{
    // Restituisce la posizione se il veicolo è valido, altrimenti NULL
    return ve ? ve->posizione : NULL;
}


/*
 Funzione: prendi_stato
 ----------------------
 Restituisce lo stato del veicolo (es. disponibile, occupato).

 Parametri:
   ve: puntatore al veicolo

   Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa con lo stato, oppure NULL se il puntatore è invalido.
*/
char *prendi_stato(ptr_veicolo ve)
{
    // Restituisce lo stato se il veicolo è valido, altrimenti NULL
    return ve ? ve->stato : NULL;
}


/*
 Funzione: prendi_prenotazioni
 -----------------------------
 Restituisce il puntatore alla lista di prenotazioni del veicolo.

 Parametri:
   ve: puntatore al veicolo

  Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica ai dati del veicolo o delle prenotazioni

 Ritorna:
   Un puntatore alla lista delle prenotazioni associate, oppure NULL.
*/
ptr_prenotazione prendi_prenotazioni(ptr_veicolo ve)
{
    return ve ? ve->prenotazione_veicolo : NULL;
}


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
void imposta_stato_veicolo(ptr_veicolo ve, const char *stato)
{
    if (ve && stato) {
        strncpy(ve->stato, stato, DIM_STATO - 1);
        ve->stato[DIM_STATO - 1] = '\0'; // garantisce terminazione stringa
    }
}
