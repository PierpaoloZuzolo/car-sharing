#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

struct nodo{
    void *oggetto;
    struct nodo *prossimo;
};


ptr_lista crea_lista()
{
    return NULL;
}

bool lista_vuota(ptr_lista l)
{
    return l == NULL;
}

ptr_lista metti_nodo(void *valore, ptr_lista prossimo_nodo)
{
    if(valore){
        ptr_lista nuovo_nodo = malloc(sizeof(struct nodo));
        nuovo_nodo->oggetto = valore;
        nuovo_nodo->prossimo = prossimo_nodo;
        return nuovo_nodo;
    }

    return NULL;
}

ptr_lista prendi_prossimo(ptr_lista nodo)
{
    if(nodo){
        return nodo->prossimo;
    }

    return NULL;
}

void cambia_prossimo_nodo(ptr_lista nodo_corrente, ptr_lista nodo_prossimo)
{
    if(nodo_corrente){
        nodo_corrente->prossimo = nodo_prossimo;
    }
}


void *prendi_oggetto(ptr_lista nodo)
{
    if(nodo){
        return nodo->oggetto;
    }

    return NULL;
}


void distruggi_nodo(ptr_lista nodo, void (*distruggi_oggetto)(void *)) 
{
    if (nodo) {
        if (nodo->oggetto && distruggi_oggetto) {
            distruggi_oggetto(nodo->oggetto);  // chiama il distruttore specifico per l'oggetto
        }
        free(nodo);  // libera il nodo
    }
}



void distruggi_lista(ptr_lista l, void (*distruggi_oggetto)(void *)) 
{
    while (l != NULL) {
        ptr_lista temp = l;
        l = l->prossimo;
        if (distruggi_oggetto && temp->oggetto) {
            distruggi_oggetto(temp->oggetto);  // chiama il distruttore
        }
        free(temp);
    }
}


