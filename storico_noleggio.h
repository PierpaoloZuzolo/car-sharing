#ifndef STORICO_PRENOTAZIONE_H
#define STORICO_PRENOTAZIONE_H

#include <stdbool.h>

typedef struct storico_noleggio *ptr_storico;

ptr_storico inizia_storico_noleggio( int gg, int mm, int aa, int ora, int minuto ,char *tipo_v, char *targa_v, char *nome_ut, float costo, int inizio_ora, int inizio_minuto, int fine_ora, int fine_minuto);

int prendi_giorno_noleggiato(ptr_storico pr);

int prendi_mese_noleggiato(ptr_storico pr);

int prendi_anno_noleggiato(ptr_storico pr);

int prendi_ora_noleggiato(ptr_storico pr);

int prendi_minuto_noleggiato(ptr_storico pr);

int prendi_ora_inizio_noleggiato(ptr_storico pr);

int prendi_minuto_inizio_noleggiato(ptr_storico pr);


int prendi_ora_fine_noleggiato(ptr_storico pr);

int prendi_minuto_fine_noleggiato(ptr_storico pr);


float prendi_costo_noleggiato(ptr_storico pr);

char *prendi_targa_veicolo_noleggiato(ptr_storico pr);

char *prendi_tipo_veicolo_noleggiato(ptr_storico pr);

char *prendi_utente_veicolo_noleggiato(ptr_storico pr);

void stampa_storico_noleggio(ptr_storico s);

bool vedi_se_noleggio_eliminabile(ptr_storico s);

void distruggi_storico_noleggio(ptr_storico s);


#endif