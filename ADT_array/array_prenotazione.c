#include <stdio.h>

#include "array_prenotazione.h"
#include "array.h"

/*
 Funzione: inizializza_prenotazioni
 ----------------------------------

 Crea e inizializza una nuova struttura per la gestione delle prenotazioni.

 Implementazione:
    Alloca e inizializza un array tramite l'ADT array.

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
ptr_prenotazione inizializza_prenotazioni() 
{
    ptr_prenotazione p = crea_array();
    if (p) azzera_array(p);
    return p;
}

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
int prendi_grandezza_array_prenotazioni()
{
    return dimensione_array();
}

/*
 Funzione: prenota_intervallo
 ----------------------------

 Prenota un intervallo di celle nell'array prenotazioni.

 Implementazione:
    Verifica validità intervallo e disponibilità,
    quindi inserisce il valore prenotato (void*)1 in ogni cella.

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

int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella) 
{
    if (!p) return 0;

    // Verifica validità intervallo usando la funzione dell'ADT
    if (!in_intervallo(inizio_cella, 0, dimensione_array()) || 
        !in_intervallo(fine_cella-1, 0, dimensione_array()) || 
        inizio_cella >= fine_cella) {
        return 0;
    }

    // Verifica disponibilità
    for (int i = inizio_cella; i < fine_cella; i++) {
        if (cerca_in_array(p, i) != NULL) {
            return 0;
        }
    }

    // Prenota l'intervallo
    for (int i = inizio_cella; i < fine_cella; i++) {
        // Usiamo (void*)1 per rappresentare "prenotato"
        inserisci_in_array(p, i, (void*)1);                    //DEVI CHIAMARE FUNZONE IMPOSTA CELLA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }

    return 1;
}
*/

/*
 Funzione: libera_intervallo
 ---------------------------

 Libera un intervallo di celle nell'array prenotazioni.

 Implementazione:
    Imposta NULL in tutte le celle nell'intervallo indicato.

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

int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella) 
{
    if (!p) return 0;

    // Verifica validità intervallo
    if (!in_intervallo(inizio_cella, 0, dimensione_array()) || 
        !in_intervallo(fine_cella-1, 0, dimensione_array()) || 
        inizio_cella >= fine_cella) {
        return 0;
    }

    // Libera l'intervallo
    for (int i = inizio_cella; i < fine_cella; i++) {
        inserisci_in_array(p, i, NULL);                       //DEVI CHIAMARE FUNZIONE IMPOSTA CELLA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }

    return 1;
}
*/

/*
 Funzione: ottiene_cella
 -----------------------

 Restituisce lo stato di una cella specifica nell'array prenotazioni.

 Implementazione:
    Controlla se la cella è prenotata (1) o libera (0).

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
int ottiene_cella(ptr_prenotazione p, int indice) 
{
    if (!p || !in_intervallo(indice, 0, dimensione_array()))
        return -1;
    
    // Restituisce 1 se prenotato, 0 altrimenti
    return (cerca_in_array(p, indice) != NULL) ? 1 : 0;
}

/*
 Funzione: imposta_cella
 -----------------------

 Imposta manualmente lo stato di una cella nell'array prenotazioni.

 Implementazione:
    Se valore è diverso da 0, imposta la cella come prenotata (void*)1,
    altrimenti libera la cella (NULL).

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
void imposta_cella(ptr_prenotazione p, int indice, int valore) 
{
    if (p && in_intervallo(indice, 0, dimensione_array())) {
        inserisci_in_array(p, indice, valore ? (void*)1 : NULL);
    }
}

/*
 Funzione: azzera_celle
 ----------------------

 Azzerra tutte le celle della struttura prenotazioni.

 Implementazione:
    Usa la funzione dell'ADT per azzerare tutte le celle.

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
void azzera_celle(ptr_prenotazione p) 
{
    if (p) azzera_array(p);
}

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
int in_intervallo(int indice, int inizio, int fine)
{
    return indice >= inizio && indice < fine;
}

/*
 Funzione: distruggi_array_prenotazioni
 --------------------------------------

 Dealloca la memoria della struttura prenotazioni.

 Implementazione:
    Chiama la funzione dell'ADT per liberare la struttura.

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
void distruggi_array_prenotazioni(ptr_prenotazione p)
{
    distruggi_array(p, NULL);
}
