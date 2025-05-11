#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorita_prenotazione.h"
#include "prenotazione.h"


// Definizione della struttura per la coda di priorità.
struct c_CP {
    prenotazione* vet[MASSIMO];  // Array per memorizzare le prenotazione dell'heap.
    int grandezza;       // Numero attuale di elementi nell'heap.
};

// Dichiarazione delle funzioni statiche per la manipolazione dell'heap.
static void scendi (codapriorita coda);
static void sali (codapriorita coda);

// Funzione alloca dinamicamente una nuova coda di priorità.
codapriorita CPnuova(void)
{
    codapriorita coda;
     coda = malloc(sizeof(struct c_CP));  
     if (coda == NULL) return NULL;       
     coda->grandezza = 0;                     
     return coda;                        
}

// Funzione per controllare se la coda è vuota.
int CPvuota(codapriorita coda)
{
     if (!coda) return 1;            
     return coda->grandezza == 0;        
}

// Funzione per ottenere il massimo elemento dalla coda di priorità.
prenotazione* ottieniMassimo(codapriorita coda)
{
     return coda->vet[1];  
}

// Funzione per riaggiustare l'heap verso il basso.
static void scendi(codapriorita coda)
{
    prenotazione* temp;
    int n = coda->grandezza, i = 1, pos;

    while (1){
     // Se il nodo corrente ha entrambi i figli (sinistro e destro)
     if (2*i + 1 <= n) 
          // Confronta il valore di 'inizio' tra il figlio sinistro (2*i) e il figlio destro (2*i + 1) e prende il maggiore
          pos = (coda->vet[2*i]->inizio > coda->vet[2*i + 1]->inizio) ? 2*i : 2*i + 1;
     // Se il nodo corrente ha solo il figlio sinistro
     else if (2*i <= n)  
          pos = 2*i; 
     else 
          break;  

     // Scambia i valori se il figlio ha un valore più grande.
     if (coda->vet[pos]->inizio > coda->vet[i]->inizio){
          temp = coda->vet[i];
          coda->vet[i] = coda->vet[pos];
          coda->vet[pos] = temp;
          // Continua a scendere nell'heap.
          i = pos;  
     }
       else
          break;  
    }
}

// Funzione per eliminare l'elemento massimo dalla coda di priorità.
int eliminaMassimo(codapriorita coda)
{
     if (!coda || coda->grandezza == 0) return 0;

     coda->vet[1] = coda->vet[coda->grandezza];  
     coda->grandezza--;                   

     scendi(coda);  // Riaggiusta l'heap scendendo l'elemento sostituito.
     return 1;
}

// Funzione per riaggiustare l'heap verso l'alto.
static void sali(codapriorita coda)
{
    prenotazione* temp;
    int pos = coda->grandezza, i = pos / 2;

    while (pos > 1)
    {
       // Se l'elemento inserito è maggiore del suo genitore, scambia i loro valori.
       if (coda->vet[pos]->inizio > coda->vet[i]->inizio)
       {
            temp = coda->vet[i];
            coda->vet[i] = coda->vet[pos];
            coda->vet[pos] = temp;
            pos = i;
            // Continua a salire nell'heap.
            i = pos / 2;  
       }
       else
             break;
     }
}

// Funzione per inserire una nuova prenotazione nell'heap.
int inserisci(codapriorita coda, prenotazione* richiesta)
{
    // Verifica se la coda è piena o il puntatore è NULL.
    if (!coda || coda->grandezza == MASSIMO) return 0;  

    coda->grandezza++;  
    coda->vet[coda->grandezza] = richiesta; 

    // Riaggiusta l'heap risalendo l'elemento inserito.
    sali(coda);  
    return 1;
}
