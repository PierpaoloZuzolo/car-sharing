#ifndef ARRAY_PRENOTAZIONE_H
#define ARRAY_PRENOTAZIONE_H

#include "array.h"


typedef struct array *ptr_prenotazione;

/*
 Funzione: inizializza_prenotazioni
 ----------------------------------

 Crea e inizializza una nuova struttura per la gestione delle prenotazioni.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Restituisce un puntatore a una struttura di prenotazioni inizializzata,
    oppure NULL in caso di errore.

 Ritorna:
    ptr_prenotazione - puntatore alla struttura prenotazioni o NULL

 Side-effect:
    Alloca memoria dinamicamente
*/
ptr_prenotazione inizializza_prenotazioni();

/*
 Funzione: prendi_grandezza_array_prenotazioni
 ---------------------------------------------

 Restituisce la dimensione dell'array prenotazioni.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    int - dimensione massima dell'array prenotazioni

 Side-effect:
    Nessuno
*/
int prendi_grandezza_array_prenotazioni();

/*
 Funzione: prenota_intervallo
 ----------------------------

 Prenota un intervallo di celle nell'array prenotazioni.

 Parametri:
    p           - puntatore alla struttura prenotazioni
    inizio_cella- indice di inizio intervallo (inclusivo)
    fine_cella  - indice di fine intervallo (esclusivo)

 Pre-condizioni:
    p valido
    inizio_cella e fine_cella validi e inizio_cella < fine_cella

 Post-condizioni:
    Celle nell'intervallo prenotate

 Ritorna:
    1 se prenotazione riuscita, 0 altrimenti

 Side-effect:
    Modifica celle nell'array prenotazioni
*/
//int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
 Funzione: libera_intervallo
 ---------------------------

 Libera un intervallo di celle nell'array prenotazioni.

 Parametri:
    p           - puntatore alla struttura prenotazioni
    inizio_cella- indice di inizio intervallo (inclusivo)
    fine_cella  - indice di fine intervallo (esclusivo)

 Pre-condizioni:
    p valido
    inizio_cella e fine_cella validi e inizio_cella < fine_cella

 Post-condizioni:
    Celle nell'intervallo liberate (impostate a NULL)

 Ritorna:
    1 se liberazione riuscita, 0 altrimenti

 Side-effect:
    Modifica celle nell'array prenotazioni
*/
//int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
 Funzione: ottiene_cella
 -----------------------

 Restituisce lo stato di una cella specifica nell'array prenotazioni.

 Parametri:
    p       - puntatore alla struttura prenotazioni
    indice  - indice della cella da interrogare

 Pre-condizioni:
    p valido
    indice valido

 Post-condizioni:
    Nessuna modifica allo stato della struttura

 Ritorna:
    1 se prenotata, 0 se libera, -1 se indice non valido o p nullo

 Side-effect:
    Nessuno
*/
int ottiene_cella(ptr_prenotazione p, int indice);

/*
 Funzione: imposta_cella
 -----------------------

 Imposta manualmente lo stato di una cella nell'array prenotazioni.

 Parametri:
    p       - puntatore alla struttura prenotazioni
    indice  - indice della cella da modificare
    valore  - stato da impostare (0 = libera, !=0 = prenotata)

 Pre-condizioni:
    p valido
    indice valido

 Post-condizioni:
    Stato della cella modificato

 Ritorna:
    void

 Side-effect:
    Modifica celle nell'array prenotazioni
*/
void imposta_cella(ptr_prenotazione p, int indice, int valore);

/*
 Funzione: azzera_celle
 ----------------------

 Azzerra tutte le celle della struttura prenotazioni.

 Parametri:
    p - puntatore alla struttura prenotazioni

 Pre-condizioni:
    p valido

 Post-condizioni:
    Tutte le celle impostate a NULL (libere)

 Ritorna:
    void

 Side-effect:
    Modifica celle nell'array prenotazioni
*/
void azzera_celle(ptr_prenotazione p);

/*
 Funzione: in_intervallo
 -----------------------

 Controlla se un indice è compreso in un intervallo [inizio, fine).

 Parametri:
    indice - valore da controllare
    inizio - limite inferiore incluso
    fine   - limite superiore escluso

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    1 se indice in [inizio, fine), 0 altrimenti

 Side-effect:
    Nessuno
*/
int in_intervallo(int indice, int inizio, int fine);

/*
 Funzione: distruggi_array_prenotazioni
 --------------------------------------

 Dealloca la memoria della struttura prenotazioni.

 Parametri:
    p - puntatore alla struttura prenotazioni da distruggere

 Pre-condizioni:
    p valido

 Post-condizioni:
    Memoria liberata

 Ritorna:
    void

 Side-effect:
    Dealloca memoria
*/
void distruggi_array_prenotazioni(ptr_prenotazione p);

#endif