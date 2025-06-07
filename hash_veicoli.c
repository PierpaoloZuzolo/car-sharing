#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "hash_veicoli.h"
#include "utile_veicolo.h"

typedef struct nodo{
    ptr_veicolo veicolo;
    struct nodo *prossimo;
}nodo;

struct tab_hash{
    int dimensione;
    nodo **tabella;
};



unsigned int hash(char *chiave, int dimensione)
{
    int valore_hash = 0;
    while (*chiave) {
        valore_hash = (valore_hash * 31 + *chiave) % dimensione;
        chiave++;
    }

    return valore_hash;
}



ptr_hash_veicolo nuova_tabella_hash(int dimensione)
{

    ptr_hash_veicolo h = (struct tab_hash *) malloc(sizeof(struct tab_hash));
    if(!h){
        return NULL;
    }

    h->dimensione = dimensione;

    h->tabella = calloc(dimensione, sizeof(nodo*));
    if(h->tabella == NULL){
        free(h);
        return NULL;
    }

    return h;
}



bool inserisci_hash(ptr_hash_veicolo h, ptr_veicolo ve)
{
    // Controlla che l’utente non sia NULL.
    if(!ve) return false;

    // Calcola l’indice della tabella hash in cui inserire il veicolo.
    char *targa = prendi_targa(ve);
    if (!targa) return false;

    int indice = hash(targa, h->dimensione); 

    // Scorre la lista collegate per verificare duplicati in base al nome e libera l'utente duplicato
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(prendi_targa(attuale->veicolo), targa) == 0){
          printf("\nErrore: targa gia' inserita.\n");
            free(ve);
             return false;
        }
      attuale = attuale->prossimo;
    }

    nodo *nuovo = malloc(sizeof(nodo));
    nuovo->veicolo = ve;

    nuovo->prossimo = h->tabella[indice];
    h->tabella[indice] = nuovo;

    return true;
    
}



ptr_veicolo cerca_veicolo(ptr_hash_veicolo h, ptr_veicolo ve)
{
    char *targa = prendi_targa(ve);
    if (!targa) return NULL;

    int indice = hash(targa, h->dimensione); 

    //Scorre la lista per trovare un utente con la stesso nome
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(prendi_targa(attuale->veicolo), targa) == 0){
            return attuale->veicolo;
        }
        attuale = attuale->prossimo;
    }

    return NULL;
}


void distruggi_hash(ptr_hash_veicolo h)
{
    for(int i = 0; i < h->dimensione; i++){
        nodo *attuale = h->tabella[i];

        while(attuale){
            nodo *temp = attuale;
            attuale = attuale->prossimo;

            libera_utente(temp->veicolo);
            free(temp);
        }
    }

    free(h->tabella);
    free(h);
}



int dimensione_hash(ptr_hash_veicolo h)
{
  // Restituisce 0 se h punta a NULL.
    return h ? h->dimensione : 0;
}