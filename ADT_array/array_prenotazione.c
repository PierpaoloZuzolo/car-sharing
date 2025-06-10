#include <stdio.h>

#include "array_prenotazione.h"
#include "array.h"


ptr_prenotazione inizializza_prenotazioni() 
{
    ptr_prenotazione p = crea_array();
    if (p) azzera_array(p);
    return p;
}

int prendi_grandezza_array_prenotazioni()
{
    return dimensione_array();
}

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
        inserisci_in_array(p, i, (void*)1);
    }

    return 1;
}

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
        inserisci_in_array(p, i, NULL);
    }

    return 1;
}

int ottiene_cella(ptr_prenotazione p, int indice) 
{
    if (!p || !in_intervallo(indice, 0, dimensione_array()))
        return -1;
    
    // Restituisce 1 se prenotato, 0 altrimenti
    return (cerca_in_array(p, indice) != NULL) ? 1 : 0;
}

void imposta_cella(ptr_prenotazione p, int indice, int valore) 
{
    if (p && in_intervallo(indice, 0, dimensione_array())) {
        inserisci_in_array(p, indice, valore ? (void*)1 : NULL);
    }
}

void azzera_celle(ptr_prenotazione p) 
{
    if (p) azzera_array(p);
}

int in_intervallo(int indice, int inizio, int fine)
{
    return indice >= inizio && indice < fine;
}


void distruggi_array_prenotazioni(ptr_prenotazione p)
{
    distruggi_array(p, NULL);
}
