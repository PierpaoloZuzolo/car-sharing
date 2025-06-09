#ifndef LISTA_STORICO_PRENOTAZIONI_H
#define LISTA_STORICO_PRENOTAZIONI_H

#include "lista.h"

typedef struct ListaNoleggi *ptr_lista_noleggi;

ptr_lista prendi_testa(ptr_lista_noleggi l);

ptr_lista prendi_coda(ptr_lista_noleggi l);

void imposta_testa(ptr_lista_noleggi lista, ptr_lista nodo);

void imposta_coda(ptr_lista_noleggi lista, ptr_lista nodo);

ptr_lista_noleggi crea_lista_storico();

bool lista_storico_vuota(ptr_lista_noleggi l);

void metti_nodo_in_testa(ptr_lista_noleggi l, ptr_storico valore);

void sposta_puntatore_coda(ptr_lista_noleggi l);

ptr_storico prendi_prenotazione_da_lista(ptr_lista nodo);

void metti_dopo_coda(ptr_lista_noleggi l, ptr_storico valore);

void distruggi_lista_storico_noleggio(ptr_lista_noleggi l);




#endif






