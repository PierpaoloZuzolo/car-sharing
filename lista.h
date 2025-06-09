#ifndef LISTA_H
#define LISTA_H

typedef struct nodo *ptr_lista;

ptr_lista crea_lista();

bool lista_vuota(ptr_lista l);

ptr_lista metti_nodo(void *valore, ptr_lista prossimo_nodo);

ptr_lista prendi_prossimo(ptr_lista nodo);

void cambia_prossimo_nodo(ptr_lista nodo_corrente, ptr_lista nodo_prossimo);

void *prendi_oggetto(ptr_lista nodo);

void distruggi_nodo(ptr_lista nodo, void (*distruggi_oggetto)(void *));

void distruggi_lista(ptr_lista l, void (*distruggi_oggetto)(void *));


#endif