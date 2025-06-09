#ifndef UTILE_LISTA_STORICO_PRENOTAZIONI_H
#define UTILE_LISTA_STORICO_PRENOTAZIONI_H

#include <stdbool.h>

#include "storico_noleggio.h"
#include "lista_storico_noleggio.h"
#include "lista.h"

void inserisci_nodo_storico_noleggio(ptr_lista_noleggi lista, ptr_storico prenotazione);

int elimina_nodo_storico_noleggio(ptr_lista_noleggi lista, char *targa_veicolo_eliminato, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine);

void salva_lista_storico_noleggio_su_file(ptr_lista_noleggi lista, char *nome_utente);

void carica_lista_storico_noleggio_da_file(ptr_lista_noleggi lista, char *nome_utente);

void aggiungi_prenotazione_storico_su_file(const char *targa, const char *tipo_veicolo, const char *nome_utente, int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, float costo);

int stampa_lista_noleggi(ptr_lista_noleggi l);

int stampa_dopo_coda(ptr_lista_noleggi l);

#endif