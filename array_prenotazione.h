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
 Alloca e inizializza una struttura prenotazioni con tutte le celle libere.

 Parametri:
   Nessuno.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   La struttura prenotazioni è allocata e tutte le celle sono azzerate (libere).

 Ritorna:
   Puntatore alla nuova struttura prenotazioni,
   oppure NULL se l’allocazione fallisce.
*/
ptr_prenotazione inizializza_prenotazioni();


/*
 Funzione: prenota_intervallo
 ----------------------------
 Tenta di prenotare un intervallo di celle consecutive.

 Parametri:
   p: puntatore alla struttura prenotazioni.
   inizio_cella: indice dello celle di inizio (incluso).
   fine_cella: indice dello slot di fine (escluso).

 Pre-condizione:
   p deve essere un puntatore valido.
   inizio_cella e fine_cella devono essere indici validi e inizio_cella < fine_cella.

 Post-condizione:
   Se possibile, le celle nell’intervallo sono marcate come prenotate.

 Ritorna:
   1 se la prenotazione ha successo,
   0 se uno o più celle nell’intervallo sono già occupate o intervallo non valido.
*/
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);


int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);



/*
 Funzione: ottiene_cella
 -----------------------
 Restituisce lo stato di una specifica cella.

 Parametri:
   p: puntatore alla struttura prenotazioni.
   indice: indice della cella da leggere.

 Pre-condizione:
   p deve essere un puntatore valido.
   indice deve essere un indice valido.

 Post-condizione:
   Nessuna modifica alla struttura prenotazioni.

 Ritorna:
   1 se la cella è prenotata,
   0 se la cella è libera,
   -1 se p è NULL o indice non valido.
*/
int ottiene_cella (ptr_prenotazione p, int indice);


/*
 Funzione: imposta_cella
 -----------------------
 Imposta lo stato di una specifica cella.

 Parametri:
   p: puntatore alla struttura prenotazioni.
   indice: indice della cella da modificare.
   valore: valore da assegnare (0 o 1).

 Pre-condizione:
   p deve essere un puntatore valido.
   indice deve essere un indice valido.

 Post-condizione:
   La cella specificata viene modificata con il valore dato.

 Ritorna:
   Nessun valore di ritorno.
*/
void imposta_cella(ptr_prenotazione p, int indice, int valore);


/*
 Funzione: azzera_celle
 ----------------------
 Azzera tutte le celle della struttura prenotazioni.

 Parametri:
   p: puntatore alla struttura prenotazioni.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Tutte le celle sono impostate a 0 (libere).

 Ritorna:
   Nessun valore di ritorno.
*/
void azzera_celle(ptr_prenotazione p);


/*
 Funzione: blocca_celle_passate
 -----------------------------
 Blocca le celle di prenotazione che sono già passate
 in base all’orario corrente.

 Parametri:
   p: puntatore alla struttura prenotazioni da aggiornare.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Tutti le celle antecedenti all’orario corrente sono marcate come occupate.
   
 Ritorna:
   Nessun valore.
*/
void blocca_celle_passate(ptr_prenotazione p);


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
int in_intervallo(int indice, int inizio, int fine);



int prendi_grandezza_array_prenotazioni();



#endif
