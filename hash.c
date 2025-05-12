#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utente.h"
#include "hash.h"



typedef struct nodo{
    PtrUtente utente;
    struct nodo *prossimo;
}nodo;

struct tabellaHash{
    int dimensione;
    nodo **tabella;
};



// funzione hash
unsigned int hash(char nome[], char email[], int dimensione)
{
    unsigned int lunghezza_nome = strnlen(nome, 50);
    unsigned int lunghezza_cognome = strnlen(email, 100);

    unsigned int valore_hash = 0;

    for (int i = 0; i < lunghezza_nome; i++){
        valore_hash += nome[i];
    }

    for (int i = 0; i < lunghezza_cognome; i++){
        valore_hash += email[i];
        valore_hash = (valore_hash * email[i]) % dimensione;
    }

    return valore_hash;
}



// funzione che crea la tabella hash
PtrHash NuovaTabellaHash(int dimensione)
{

    PtrHash h = (struct tabellaHash *) malloc(sizeof(struct tabellaHash));
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



// funzione che inserisce un utente nella tabella 
bool InserisciHash(PtrHash h, PtrUtente ut)
{
    if(!ut) return false;

    int indice = hash(PrendiNome(ut), PrendiEmail(ut), h->dimensione); // passare il valore dimensione

    nodo *attuale = h->tabella[indice];
     // prende il primo nodo della lista collegata presente in quella celletta
    while(attuale){
        if(strcmp(PrendiEmail(attuale->utente), PrendiEmail(ut)) == 0){
            free(ut);
             return false;
        }
      attuale = attuale->prossimo;
    }
    nodo *nuovo = malloc(sizeof(nodo));
    nuovo->utente = ut;
    nuovo->prossimo = h->tabella[indice];
    h->tabella[indice] = nuovo;

    return true;
    
}




PtrUtente CercaUtente(PtrHash h, PtrUtente ut)
{
    int indice = hash(PrendiNome(ut), PrendiEmail(ut), h->dimensione); 
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(PrendiEmail(attuale->utente), PrendiEmail(ut)) == 0){
            return attuale->utente;
        }
        attuale = attuale->prossimo;
    }
    return NULL;
}




void DistruggiHash(PtrHash h)
{
    for(int i = 0; i < h->dimensione; i++){
        nodo *attuale = h->tabella[i];
        while(attuale){
            nodo *temp = attuale;
            attuale = attuale->prossimo;
            LiberaUtente(temp->utente);
            free(temp);
        }
    }
    free(h->tabella);
    free(h);
}