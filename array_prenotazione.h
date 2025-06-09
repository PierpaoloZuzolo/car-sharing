/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include <stdbool.h>
#define CELLE_GIORNALIERE 48  // 48 mezz'ore in un giorno

/*
 Tipo astratto di dato: prenotazioni
 ----------------------------------
 Struttura che rappresenta le prenotazioni di un veicolo
 suddivise in celle giornaliere (es. 48 slot per 24 ore a intervalli di 30 min)
 per un periodo di 6 giorni (lunedì-sabato).
*/
typedef struct prenotazioni *ptr_prenotazione;


/*
 Funzione: inizializza_prenotazioni
 ----------------------------------

 Crea e inizializza una nuova struttura per la gestione delle prenotazioni.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    restituisce un puntatore a una nuova struttura `prenotazioni` con celle inizializzate a 0,
    oppure NULL in caso di errore di allocazione

 Ritorna:
    un puntatore a una struttura `ptr_prenotazione`, o NULL se la creazione fallisce

 Side-effect:
    alloca memoria dinamicamente per la struttura delle prenotazioni
 */
ptr_prenotazione inizializza_prenotazioni();

/*
 Funzione: prenota_intervallo
 ----------------------------

 Tenta di prenotare un intervallo di tempo specificato all'interno della struttura delle prenotazioni.

 Parametri:
    p: puntatore alla struttura `prenotazioni`
    inizio_cella: indice iniziale dell'intervallo da prenotare (incluso)
    fine_cella: indice finale dell'intervallo da prenotare (escluso)

 Pre-condizioni:
    - `p` deve essere diverso da NULL
    - `inizio_cella` deve essere >= 0
    - `fine_cella` deve essere <= CELLE_GIORNALIERE
    - `inizio_cella` deve essere < `fine_cella`

 Post-condizioni:
    - se tutte le celle nell'intervallo sono libere, vengono marcate come occupate
    - se l'intervallo è già parzialmente occupato o non valido, non viene effettuata alcuna modifica

 Ritorna:
    1 se la prenotazione è stata effettuata con successo, 0 altrimenti

 Side-effect:
    modifica lo stato interno della struttura `prenotazioni` riservando le celle indicate
 */
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
 Funzione: libera_intervallo
 ---------------------------

 Libera un intervallo di celle precedentemente prenotate nella struttura delle prenotazioni.

 Parametri:
    p: puntatore alla struttura `prenotazioni`
    inizio_cella: indice iniziale dell'intervallo da liberare (incluso)
    fine_cella: indice finale dell'intervallo da liberare (escluso)

 Pre-condizioni:
    - `p` deve essere diverso da NULL
    - `inizio_cella` deve essere >= 0
    - `fine_cella` deve essere <= CELLE_GIORNALIERE
    - `inizio_cella` deve essere < `fine_cella`

 Post-condizioni:
    le celle dell'intervallo specificato sono marcate come libere (valore 0)

 Ritorna:
    1 se l’intervallo è stato liberato con successo, 0 se l’operazione non è stata eseguita (es. puntatore NULL o intervallo non valido)

 Side-effect:
    modifica lo stato interno della struttura `prenotazioni`, liberando le celle indicate
 */
int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
 Funzione: ottiene_cella
 -----------------------

 Restituisce lo stato di una specifica cella all'interno della struttura delle prenotazioni.

 Parametri:
    p: puntatore alla struttura `prenotazioni`
    indice: posizione della cella da leggere

 Pre-condizioni:
    - `p` deve essere diverso da NULL
    - `indice` deve essere compreso tra 0 (incluso) e CELLE_GIORNALIERE (escluso)

 Post-condizioni:
    Nessuna modifica alla struttura

 Ritorna:
    - 1 se la cella è prenotata
    - 0 se la cella è libera
    - -1 se il puntatore è NULL o l’indice è fuori dal range

 Side-effect:
    Nessuno
 */
int ottiene_cella (ptr_prenotazione p, int indice);

/*
 Funzione: imposta_cella
 -----------------------

 Imposta manualmente il valore di una specifica cella nella struttura delle prenotazioni.

 Parametri:
    p: puntatore alla struttura `prenotazioni`
    indice: posizione della cella da modificare
    valore: nuovo valore da assegnare alla cella (tipicamente 0 per libero, 1 per occupato)

 Pre-condizioni:
    - `p` deve essere diverso da NULL
    - `indice` deve essere compreso tra 0 (incluso) e CELLE_GIORNALIERE (escluso)

 Post-condizioni:
    la cella all’indice specificato assume il valore passato

 Ritorna:
    Nessuno

 Side-effect:
    modifica il contenuto della struttura `prenotazioni` alla cella specificata
 */
void imposta_cella(ptr_prenotazione p, int indice, int valore);

/*
 Funzione: azzera_celle
 ----------------------

 Inizializza tutte le celle della struttura delle prenotazioni a 0, marcandole come libere.

 Parametri:
    p: puntatore alla struttura `prenotazioni`

 Pre-condizioni:
    - `p` deve essere diverso da NULL

 Post-condizioni:
    tutte le celle della struttura sono impostate a 0 (libere)

 Ritorna:
    Nessuno

 Side-effect:
    modifica tutte le celle della struttura `prenotazioni` azzerandole
 */
void azzera_celle(ptr_prenotazione p);

/*
 Funzione: in_intervallo
 -----------------------

 Verifica se un indice è compreso all'interno di un intervallo semi-aperto [inizio, fine).

 Parametri:
    indice: valore da verificare
    inizio: limite inferiore (incluso) dell’intervallo
    fine: limite superiore (escluso) dell’intervallo

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    1 se `indice` ∈ [inizio, fine), 0 altrimenti

 Side-effect:
    Nessuno
 */
int in_intervallo(int indice, int inizio, int fine);

/*
 Funzione: prendi_grandezza_array_prenotazioni
 ---------------------------------------------

 Restituisce la dimensione dell'array utilizzato per memorizzare le prenotazioni giornaliere.

 Implementazione:
    Restituisce il valore della costante `CELLE_GIORNALIERE`.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    un intero che rappresenta il numero di celle giornaliere disponibili per le prenotazioni

 Side-effect:
    Nessuno
 */
int prendi_grandezza_array_prenotazioni();



#endif
