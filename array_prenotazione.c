/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "array_prenotazione.h"
#include "utile.h"


struct prenotazioni {
    int cella[CELLE_GIORNALIERE];  // ogni cella vale 30 minuti
};


/*
 Funzione: inizializza_prenotazioni
 ----------------------------------

 Crea e inizializza una nuova struttura per la gestione delle prenotazioni.

 Implementazione:
    Alloca dinamicamente una struttura `prenotazioni` e imposta a 0 tutte le celle.

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
ptr_prenotazione inizializza_prenotazioni() 
{
    ptr_prenotazione p = malloc(sizeof(struct prenotazioni));

    if (p) memset(p->cella, 0, sizeof(p->cella));
    return p;
}

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
int prendi_grandezza_array_prenotazioni()
{
    return CELLE_GIORNALIERE;
}

/*
 Funzione: prenota_intervallo
 ----------------------------

 Tenta di prenotare un intervallo di tempo specificato all'interno della struttura delle prenotazioni.

 Implementazione:
    Verifica che l'intervallo sia valido e che tutte le celle siano libere.
    Se l'intervallo è disponibile, imposta a 1 tutte le celle comprese tra `inizio_cella` e `fine_cella`.

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
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella) 
{
    if (!p) return 0;

    if (inizio_cella < 0 || fine_cella > CELLE_GIORNALIERE  || inizio_cella >= fine_cella) {
        //printf(" Intervallo non valido: inizio=%d, fine=%d\n", inizio_cella, fine_cella);
        return 0;
    }

    // Verifica disponibilità in quell'orario
    for (int i = inizio_cella; i < fine_cella; i++) {
        if (p->cella[i]) {
            //printf(" Intervallo occupato (slot %d gia prenotato).\n", i);
            return 0;
        }
    }

    // Prenota se è libero quell'orario
    for (int i = inizio_cella; i < fine_cella; i++) {
        p->cella[i] = 1;
    }

    return 1;
}

/*
 Funzione: libera_intervallo
 ---------------------------

 Libera un intervallo di celle precedentemente prenotate nella struttura delle prenotazioni.

 Implementazione:
    Verifica che l'intervallo sia valido e imposta a 0 tutte le celle comprese tra `inizio_cella` e `fine_cella`.

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
int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella) 
{
    if (!p) return 0;

    if (inizio_cella < 0 || fine_cella > CELLE_GIORNALIERE || inizio_cella >= fine_cella) {
        //printf(" Intervallo non valido: inizio=%d, fine=%d\n", inizio_cella, fine_cella);
        return 0;
    }

    // Libera le celle
    for (int i = inizio_cella; i < fine_cella; i++) {
        p->cella[i] = 0;
    }

    return 1;
}

/*
 Funzione: ottiene_cella
 -----------------------

 Restituisce lo stato di una specifica cella all'interno della struttura delle prenotazioni.

 Implementazione:
    Verifica che il puntatore e l'indice siano validi, quindi restituisce il valore della cella indicata.

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
int ottiene_cella (ptr_prenotazione p, int indice) {
    if (p && indice >= 0 && indice < CELLE_GIORNALIERE)
        return p->cella[indice];
    return -1;
}

/*
 Funzione: imposta_cella
 -----------------------

 Imposta manualmente il valore di una specifica cella nella struttura delle prenotazioni.

 Implementazione:
    Verifica che il puntatore e l'indice siano validi, quindi assegna il valore indicato alla cella corrispondente.

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
void imposta_cella(ptr_prenotazione p, int indice, int valore) {
    if (p && indice >= 0 && indice < CELLE_GIORNALIERE)
        p->cella[indice] = valore;
}

/*
 Funzione: azzera_celle
 ----------------------

 Inizializza tutte le celle della struttura delle prenotazioni a 0, marcandole come libere.

 Implementazione:
    Utilizza `memset` per azzerare l'intero array `cella`.

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
void azzera_celle(ptr_prenotazione p) {
    memset(p->cella, 0, sizeof(p->cella));
}

/*
 Funzione: in_intervallo
 -----------------------

 Verifica se un indice è compreso all'interno di un intervallo semi-aperto [inizio, fine).

 Implementazione:
    Restituisce vero (1) se l'indice è maggiore o uguale a `inizio` e strettamente minore di `fine`.

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
int in_intervallo(int indice, int inizio, int fine)  // DA METTERE FUORI
{
    return indice >= inizio && indice < fine;
}