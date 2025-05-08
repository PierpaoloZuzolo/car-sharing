#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utente.h>
#include <time.h>
#include "priorita_prenotazione.h"


// Definizione della struttura per la coda di priorità.
struct c_CP {
    PRENOTAZIONE vet[MASSIMO];  // Array per memorizzare le prenotazione dell'heap.
    int grandezza;       // Numero attuale di elementi nell'heap.
};


// Dichiarazione delle funzioni statiche per la manipolazione dell'heap.
static void scendi (CODAPRIORITA coda);
static void sali (CODAPRIORITA coda);

// Funzione per creare una nuova coda di priorità.
CODAPRIORITA CPnuova(void)
{
    CODAPRIORITA coda;
     coda = malloc(sizeof(struct c_CP));  
     if (coda == NULL) return NULL;       
     coda->grandezza = 0;                     
     return coda;                        
}

// Funzione per controllare se la coda è vuota.
int CPvuota(CODAPRIORITA coda)
{
     if (!coda) return 1;            // Controlla se il puntatore è NULL.
     return coda->grandezza == 0;        // Ritorna vero se la coda è vuota.
}

// Funzione per ottenere il massimo elemento dalla coda di priorità.
PRENOTAZIONE ottieniMassimo(CODAPRIORITA coda)
{
     return coda->vet[1];  
}

// Funzione per eliminare l'elemento massimo dalla coda di priorità.
int eliminaMassimo(CODAPRIORITA coda)
{
     if (!coda || coda->grandezza == 0) return 0;

     coda->vet[1] = coda->vet[coda->grandezza];  
     coda->grandezza--;                   

     scendi(coda);  // Riaggiusta l'heap scendendo l'elemento sostituito.
     return 1;
}

// Funzione per riaggiustare l'heap verso il basso.
static void scendi(CODAPRIORITA coda)
{
    PRENOTAZIONE temp;
    int n = coda->grandezza, i = 1, pos;

    while (1)
    {
       // Determina la posizione del figlio con il valore più grande.
       // Se il nodo corrente ha due figli.
       if (2*i + 1 <= n)
                  pos = (coda->vet[2*i]->inizio > coda->vet[2*i + 1]->inizio) ? 2*i : 2*i + 1;
                  // Se il nodo corrente ha solo un figlio.
       else if (2*i <= n)  
                  pos = 2*i;
       else 
         break;  // Se non ha figli, interrompe il ciclo.

       // Scambia i valori se il figlio ha un valore più grande.
       if (coda->vet[pos]->inizio > coda->vet[i]->inizio)
       {
             temp = coda->vet[i];
             coda->vet[i] = coda->vet[pos];
             coda->vet[pos] = temp;
             // Continua a scendere nell'heap.
             i = pos;  
       }
       else
           break;  // Termina se non sono necessari altri scambi.
     }
}

// Funzione per inserire una nuova prenotazione nell'heap.
int inserisci(CODAPRIORITA coda, PRENOTAZIONE prenotazione)
{
    // Verifica se la coda è piena o il puntatore è NULL.
    if (!coda || coda->grandezza == MASSIMO) return 0;  

    coda->grandezza++;  
    coda->vet[coda->grandezza] = prenotazione; 

    // Riaggiusta l'heap risalendo l'elemento inserito.
    sali(coda);  
    return 1;
}

// Funzione per riaggiustare l'heap verso l'alto.
static void sali(CODAPRIORITA coda)
{
    PRENOTAZIONE temp;
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
            i = pos / 2;  // Continua a salire nell'heap.
       }
       else
             break;  // Termina se non sono necessari altri scambi.
     }
}
