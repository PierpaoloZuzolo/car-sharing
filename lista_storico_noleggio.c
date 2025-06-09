#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "storico_noleggio.h"
#include "lista_storico_noleggio.h"
#include "lista.h"


struct  ListaNoleggi{
    ptr_lista testa;
    ptr_lista coda;
};


ptr_lista prendi_testa(ptr_lista_noleggi l)
{
    return l ? l->testa : NULL;
}

ptr_lista prendi_coda(ptr_lista_noleggi l)
{
    return l ? l->coda : NULL;
}

void imposta_testa(ptr_lista_noleggi lista, ptr_lista nodo) 
{
    if (!lista) return;
    lista->testa = nodo;
}

void imposta_coda(ptr_lista_noleggi lista, ptr_lista nodo) 
{
    if (!lista) return;
    lista->coda = nodo;
} 


ptr_lista_noleggi crea_lista_storico()
{
    ptr_lista_noleggi lista = malloc(sizeof(struct ListaNoleggi));
    if (!lista) {
        return NULL; 
    }
    lista->testa = crea_lista(); // cioè NULL
    lista->coda = NULL;
    return lista;
}


bool lista_storico_vuota(ptr_lista_noleggi l)
{
    return lista_vuota(l->testa);
}

void metti_nodo_in_testa(ptr_lista_noleggi l, ptr_storico valore)
{
    if(lista_vuota(l->testa)){
        l->testa = metti_nodo(valore, NULL);
    }else {
            l->testa = metti_nodo(valore, l->testa); //da vedere
    }
}


void sposta_puntatore_coda(ptr_lista_noleggi l)
{
    if(l){
        if(l->coda){
            l->coda = prendi_prossimo(l->coda);
        }
    }
}

ptr_storico prendi_prenotazione_da_lista(ptr_lista nodo)
{
    if(nodo){
        return (ptr_storico) prendi_oggetto(nodo);
    }
    return NULL;
}


void metti_dopo_coda(ptr_lista_noleggi l, ptr_storico valore)
{
    if (l && l->coda) {
        ptr_lista nuovo = metti_nodo(valore, prendi_prossimo(l->coda)); // crea il nodo con "valore" e come prossimo il vecchio prossimo della coda
        cambia_prossimo_nodo(l->coda, nuovo); // collega la coda al nuovo nodo
    }
}

static void distruggi_storico_in_lista(void *s)
{
    ptr_storico ptr = (ptr_storico)s;
    distruggi_storico_noleggio(ptr);
}

void distruggi_lista_storico_noleggio(ptr_lista_noleggi l) {
    if (l) {
        distruggi_lista(l->testa, distruggi_storico_in_lista);  
        free(l);
    }
}









