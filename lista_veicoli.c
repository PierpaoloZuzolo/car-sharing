#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "lista_veicoli.h"

typedef struct nodo{
    ptr_veicolo veicolo;
    struct nodo *prossimo;
}nodo;

struct lista_veicoli{
    nodo *testa;
};


/*
 Funzione: nuova_lista
 ---------------------
 Crea una nuova lista di veicoli vuota.

  Parametri:
   Nessuno.

 Pre-condizione:
   Nessuna.

 Ritorna:
   Un puntatore a una nuova lista inizializzata (testa NULL), 
   oppure NULL in caso di errore di allocazione.
*/
ptr_lista nuova_lista()
{
    ptr_lista li = malloc(sizeof(struct lista_veicoli));
    if(!li){
        return NULL;
    }
    
    li->testa = NULL;

    return li;
}


/*
 Funzione: inserisci_veicolo_lista
 ---------------------------------
 Inserisce un veicolo nella lista, se disponibile.

 Parametri:
   li: puntatore alla lista in cui inserire il veicolo.
   ve: puntatore al veicolo da inserire.

    Pre-condizione:
   li e ve devono essere puntatori validi (non NULL).

 Post-condizione:
   Il veicolo viene inserito nella lista.

 Effetti:
   Inserisce il veicolo in testa alla lista solo se il suo stato è "disponibile".
   In caso contrario, libera la memoria associata al veicolo.
   Se uno dei puntatori è NULL o si verifica un errore di allocazione, il programma termina.
*/
void inserisci_veicolo_lista(ptr_lista li, ptr_veicolo ve)
{
    if (!li || !ve) {
        printf("Errore: puntatori nulli in inserisci_veicolo_lista.\n");
        exit(1);
    }

    if (strcmp(prendi_stato(ve), "disponibile") != 0) {
        libera_veicolo(ve);
        return;
    }

    nodo *nuovo = malloc(sizeof(nodo));
    if (!nuovo) {
        printf("Errore allocazione nodo.\n");
        libera_veicolo(ve);
        return;
    }

    nuovo->veicolo = ve;
    nuovo->prossimo = li->testa;
    li->testa = nuovo;
}


/*
 Funzione: rimuovi_veicolo_non_disponibile
 -----------------------------------------
 Rimuove dalla lista tutti i veicoli non disponibili.

 Parametri:
   li: puntatore alla lista da modificare.

    Pre-condizione:
   li deve essere un puntatore valido.

 Post-condizione:
   I veicoli non disponibili vengono rimossi e la loro memoria liberata.

 Effetti:
   Scorre la lista e rimuove tutti i nodi il cui veicolo ha stato "non disponibile".
   Libera la memoria dei veicoli rimossi e dei nodi corrispondenti.
*/
void rimuovi_veicolo_non_disponibile(ptr_lista li)
{
    if (!li || !li->testa) return;

    nodo *curr = li->testa;
    nodo *prev = NULL;

    // Scorri tutta la lista per cercare veicoli non disponibili
    while (curr) {
        ptr_veicolo ve = curr->veicolo;

        if (strcmp(prendi_stato(ve), "non disponibile") == 0) {
            nodo *da_rimuovere = curr;

            if (prev == NULL) {
                li->testa = curr->prossimo;
            } else {
                prev->prossimo = curr->prossimo;
            }

            curr = curr->prossimo;

            libera_veicolo(da_rimuovere->veicolo);
            free(da_rimuovere);
        } else {
            prev = curr;
            curr = curr->prossimo;
        }
    }
}


/*
 Funzione: stampa_lista_veicoli
 ------------------------------
 Stampa a video l'intera lista dei veicoli.

 Parametri:
   li: puntatore alla lista da stampare.

    Pre-condizione:
   li deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica alla lista.

 Effetti:
   Per ogni veicolo nella lista, stampa le sue informazioni con indice progressivo.
*/
void stampa_lista_veicoli(ptr_lista li)
{
    int i = 1;
    nodo *corr = li->testa;

    while(corr){
        printf("%d) ", i);

        // Stampa le informazioni dettagliate del veicolo corrente
        stampa_veicolo(corr->veicolo);

        printf("\n");
        corr = corr->prossimo;
        i++;
    }
}


/*
 Funzione: libera_lista_veicoli
 ------------------------------
 Libera tutta la memoria associata alla lista di veicoli.

 Parametri:
   li: puntatore alla lista da deallocare.

    Pre-condizione:
   li deve essere un puntatore valido.

 Post-condizione:
   Tutta la memoria occupata dalla lista e dai veicoli è liberata.

 Effetti:
   Libera tutti i nodi e i veicoli contenuti, poi libera la lista stessa.
*/
void libera_lista_veicoli(ptr_lista li)
{
    nodo *corr = li->testa;

    while(corr){
        nodo *temp = corr;

        corr = corr->prossimo;

        libera_veicolo(temp->veicolo);

        free(temp);
    }

    free(li);
}


/*
 Funzione: trova_veicolo_lista
 -----------------------------
 Restituisce il veicolo nella posizione specificata della lista.

 Parametri:
   posizione: posizione (1-based) del veicolo da cercare.
   li: puntatore alla lista da cui estrarre il veicolo.

  Pre-condizione:
   li deve essere un puntatore valido.
   posizione deve essere compresa tra 0 e (dimensione della lista - 1).

 Post-condizione:
   Nessuna modifica alla lista.

 Ritorna:
   Il puntatore al veicolo nella posizione indicata, oppure NULL se non valido.
*/
ptr_veicolo trova_veicolo_lista(int posizione, ptr_lista li)
{
    // Verifica che la lista sia valida e la posizione sia almeno 1.
    if(!li || posizione < 1){
        return NULL;
    }

    nodo *corr = li->testa;

    for(int i = 1; i < posizione && corr != NULL; i++){
        corr = corr->prossimo;
    }

    if(corr){
        return corr->veicolo;
    }
    return NULL;
}
