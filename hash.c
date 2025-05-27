#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utente.h"
#include "hash.h"
#include "utile_utente.h"



typedef struct nodo{
    ptr_utente utente;
    struct nodo *prossimo;
}nodo;

struct tabella_hash{
    int dimensione;
    nodo **tabella;
};



/*
 Funzione: hash
 --------------
 Calcola un valore hash a partire da nome.
 Utilizzato per indicizzare un utente all'interno di una tabella hash.

 Parametri:
   chiave: stringa contenente il nome dell'utente (massimo 50 caratteri considerati).
   
  Pre-condizione:
   chiave deve essere un puntatore valido.
   dimensione > 0.

 Post-condizione:
   Nessuna modifica ai parametri.

 Ritorna:
   Un valore hash (unsigned int) calcolato in base ai caratteri di chiave,
   compreso tra 0 e dimensione - 1.
*/
unsigned int hash(char *chiave, int dimensione)
{
    int valore_hash = 0;
    while (*chiave) {
        valore_hash = (valore_hash * 31 + *chiave) % dimensione;
        chiave++;
    }

    return valore_hash;
}


/*
 Funzione: nuova_tabella_hash
 ----------------------------
 Alloca e inizializza una nuova tabella hash con la dimensione specificata.

 Parametri:
   dimensione: numero di posizioni della tabella hash (numero di bucket).

  Pre-condizione:
   dimensione > 0.

 Post-condizione:
   Alloca e restituisce un puntatore a una nuova tabella hash vuota.

 Ritorna:
   Un puntatore alla nuova tabella hash (ptr_hash), oppure NULL in caso di errore di allocazione.
*/
ptr_hash nuova_tabella_hash(int dimensione)
{

    ptr_hash h = (struct tabella_hash *) malloc(sizeof(struct tabella_hash));
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


/*
 Funzione: inserisci_hash
 ------------------------
 Inserisce un nuovo utente nella tabella hash, evitando duplicati per email.

 Parametri:
   h: puntatore alla tabella hash in cui inserire l'utente.
   ut: puntatore alla struttura utente da inserire.

  Pre-condizione:
   h e utente devono essere puntatori validi.

 Post-condizione:
   L'utente è inserito nella tabella se non già presente.

 Ritorna:
   true se l'inserimento è andato a buon fine,
   false se l'utente è NULL, è già presente nella tabella (in base all'email),
   o se si verifica un errore di allocazione.
*/
bool inserisci_hash(ptr_hash h, ptr_utente ut)
{
    // Controlla che l’utente non sia NULL.
    if(!ut) return false;

    // Calcola l’indice della tabella hash in cui inserire l’utente.
    int indice = hash(prendi_nome(ut), h->dimensione); 

    // Scorre la lista collegate per verificare duplicati in base al nome e libera l'utente duplicato
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(prendi_nome(attuale->utente), prendi_nome(ut)) == 0){
          printf("\nNome inserito non valido!\n");
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


/*
 Funzione: cerca_utente
 ----------------------
 Cerca un utente nella tabella hash in base a nome.

 Parametri:
   h: puntatore alla tabella hash in cui cercare.
   ut: puntatore a una struttura utente con nome ed email da confrontare.

  Pre-condizione:
   h e ut devono essere puntatori validi.

 Post-condizione:
   Nessuna modifica alla tabella.

 Ritorna:
   Un puntatore all'utente trovato, oppure NULL se non è presente nella tabella.
*/
ptr_utente cerca_utente(ptr_hash h, ptr_utente ut)
{
    int indice = hash(prendi_nome(ut), h->dimensione); 

    //Scorre la lista per trovare un utente con la stesso nome
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(prendi_nome(attuale->utente), prendi_nome(ut)) == 0){
            return attuale->utente;
        }
        attuale = attuale->prossimo;
    }

    return NULL;
}


/*
 Funzione: distruggi_hash
 ------------------------
 Libera tutta la memoria allocata per la tabella hash, inclusi gli utenti e i nodi.

 Parametri:
   h: puntatore alla tabella hash da distruggere.

  Pre-condizione:
   h deve essere un puntatore valido.

 Post-condizione:
   Tutta la memoria occupata dalla tabella e dagli utenti viene liberata.

 Effetti:
   Dealloca tutti i nodi delle liste collegate, libera la memoria degli utenti tramite LiberaUtente,
   poi libera l'array della tabella e infine la struttura principale.
*/
void distruggi_hash(ptr_hash h)
{
    for(int i = 0; i < h->dimensione; i++){
        nodo *attuale = h->tabella[i];

        while(attuale){
            nodo *temp = attuale;
            attuale = attuale->prossimo;

            libera_utente(temp->utente);
            free(temp);
        }
    }

    free(h->tabella);
    free(h);
}


/*
 Funzione: dimensione_hash
 -------------------------
 Restituisce la dimensione della tabella hash.

 Parametri:
   h: puntatore alla tabella hash.

  Pre-condizione:
   h deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica alla tabella.

 Ritorna:
   La dimensione della tabella se h è valido,
   altrimenti 0 se il puntatore è NULL.
*/
int dimensione_hash(ptr_hash h)
{
  // Restituisce 0 se h punta a NULL.
    return h ? h->dimensione : 0;
}