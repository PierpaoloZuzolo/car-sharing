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
 Inizializza una nuova struttura per la gestione delle prenotazioni.

  Pre-condizione:
   Nessuna.

 Post-condizione:
   La struttura prenotazioni è allocata e tutte le celle sono azzerate (libere).

 Ritorna:
   Un puntatore a una nuova struttura prenotazioni con tutte le celle impostate a NULL.
   Restituisce NULL in caso di fallimento nell'allocazione.
*/
ptr_prenotazione inizializza_prenotazioni() 
{
    ptr_prenotazione p = malloc(sizeof(struct prenotazioni));

    if (p) memset(p->cella, 0, sizeof(p->cella));
    return p;
}

int prendi_grandezza_array_prenotazioni()
{
    return CELLE_GIORNALIERE;
}


/*
 Funzione: prenota_intervallo
 ----------------------------
 Tenta di prenotare un intervallo di celle orarie consecutive.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.
   inizio_cella: indice della cella iniziale dell’intervallo.
   fine_cella: indice della cella finale (esclusiva) dell’intervallo.

  Pre-condizione:
   p deve essere un puntatore valido.
   inizio_cella e fine_cella devono essere indici validi e inizio_cella < fine_cella.

 Post-condizione:
   Se possibile, le celle nell’intervallo sono marcate come prenotate.

 Valore di ritorno:
   Restituisce 1 se l’intervallo è stato prenotato con successo, 0 altrimenti.
   Fallisce se l’intervallo è invalido o se una cella dell’intervallo è già occupata.
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


//todo specifica!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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
 Restituisce lo stato di una specifica cella di prenotazione.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.
   indice: indice della cella da leggere.

 Pre-condizione:
   p deve essere un puntatore valido.
   indice deve essere un valore valido tra 0 e CELLE_GIORNALIERE - 1.

 Post-condizione:
   Nessuna modifica alla struttura prenotazioni.

 Valore di ritorno:
   Restituisce 1 se la cella è prenotata, 0 se è libera.
   Restituisce -1 se p è NULL o indice non valido.
*/
int ottiene_cella (ptr_prenotazione p, int indice) {
    if (p && indice >= 0 && indice < CELLE_GIORNALIERE)
        return p->cella[indice];
    return -1;
}


/*
 Funzione: imposta_cella
 -----------------------
 Imposta lo stato di una specifica cella di prenotazione.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.
   indice: indice della cella da modificare.
   valore: valore da impostare (tipicamente 0 o 1).

 Pre-condizione:
   p deve essere un puntatore valido.
   indice deve essere un valore valido tra 0 e CELLE_GIORNALIERE - 1.

 Post-condizione:
   La cella specificata viene aggiornata con il valore fornito.

 Effetti:
   Modifica lo stato interno della struttura prenotazioni.
*/
void imposta_cella(ptr_prenotazione p, int indice, int valore) {
    if (p && indice >= 0 && indice < CELLE_GIORNALIERE)
        p->cella[indice] = valore;
}


/*
 Funzione: azzera_celle
 ----------------------
 Azzera tutte le celle della struttura prenotazioni, rendendole libere.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Tutte le celle sono impostate a 0 (libere).

 Effetti:
   Modifica lo stato interno della struttura prenotazioni.
*/
void azzera_celle(ptr_prenotazione p) {
    memset(p->cella, 0, sizeof(p->cella));
}



/*
 Funzione: in_intervallo
 -----------------------
 Verifica se un indice rientra in un intervallo [inizio, fine).

 Parametri:
   indice: indice della cella da verificare.
   inizio: inizio dell'intervallo (inclusivo).
   fine: fine dell'intervallo (esclusivo).

 Pre-condizione:
   Tutti i parametri devono essere validi (0 <= inizio <= fine <= CELLE_GIORNALIERE).

 Ritorna:
   1 se indice è nell'intervallo [inizio, fine),
   0 altrimenti.
*/
int in_intervallo(int indice, int inizio, int fine)  // DA METTERE FUORI
{
    return indice >= inizio && indice < fine;
}