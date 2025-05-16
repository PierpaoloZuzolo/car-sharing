#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utente.h"
#include "hash.h"



typedef struct nodo{
    ptr_utente utente;
    struct nodo *prossimo;
}nodo;

struct tabella_hash{
    int dimensione;
    nodo **tabella;
};



/*
 Calcola un valore hash a partire da nome ed email.
 Utilizzato per indicizzare un utente all'interno di una tabella hash.

 Parametri:
   nome: stringa contenente il nome dell'utente (massimo 50 caratteri considerati).
   email: stringa contenente l'email dell'utente (massimo 100 caratteri considerati).
   dimensione: dimensione della tabella hash.

 Ritorna:
   Un valore hash (unsigned int) calcolato in base ai caratteri di nome ed email,
   compreso tra 0 e dimensione - 1.
*/
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


/*
 Alloca e inizializza una nuova tabella hash con la dimensione specificata.

 Parametri:
   dimensione: numero di posizioni della tabella hash (numero di bucket).

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
 Inserisce un nuovo utente nella tabella hash, evitando duplicati per email.

 Parametri:
   h: puntatore alla tabella hash in cui inserire l'utente.
   ut: puntatore alla struttura utente da inserire.

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
    int indice = hash(prendi_nome(ut), prendi_email(ut), h->dimensione); 

    // Scorre la lista collegate per verificare duplicati in base all'email e libera l'utente duplicato
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(prendi_email(attuale->utente), prendi_email(ut)) == 0){
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
 Cerca un utente nella tabella hash in base a nome ed email.

 Parametri:
   h: puntatore alla tabella hash in cui cercare.
   ut: puntatore a una struttura utente con nome ed email da confrontare.

 Ritorna:
   Un puntatore all'utente trovato, oppure NULL se non è presente nella tabella.
*/
ptr_utente cerca_utente(ptr_hash h, ptr_utente ut)
{
    int indice = hash(prendi_nome(ut), prendi_email(ut), h->dimensione); 

    //Scorre la lista per trovare un utente con la stessa email
    nodo *attuale = h->tabella[indice];
    while(attuale){
        if(strcmp(prendi_email(attuale->utente), prendi_email(ut)) == 0){
            return attuale->utente;
        }
        attuale = attuale->prossimo;
    }

    return NULL;
}


/*
 Libera tutta la memoria allocata per la tabella hash, inclusi gli utenti e i nodi.

 Parametri:
   h: puntatore alla tabella hash da distruggere.

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

            LiberaUtente(temp->utente);
            free(temp);
        }
    }

    free(h->tabella);
    free(h);
}


/*
 Restituisce la dimensione della tabella hash.

 Parametri:
   h: puntatore alla tabella hash.

 Ritorna:
   La dimensione della tabella se h è valido,
   altrimenti 0 se il puntatore è NULL.
*/
int dimensione_hash(ptr_hash h)
{
  // Restituisce 0 se h punta a NULL.
    return h ? h->dimensione : 0;
}


/*
 Verifica se esiste un utente con lo stesso nome o email nella tabella hash.

 Parametri:
   h: puntatore alla tabella hash.
   nome: stringa del nome da verificare.
   email: stringa dell'email da verificare.

 Ritorna:
   true se trova un utente con nome o email già presenti,
   false altrimenti.

 Nota:
   In caso di tabella hash non valida, stampa un errore e termina il programma.
*/
bool verifica_duplicati_utenti(ptr_hash h, const char *nome, const char *email)
{
    if(!h){
        printf("Errore tabella hash.");
        exit(1);
    }

    int dimensione = dimensione_hash(h);
    if (0 == dimensione){
        printf("Errore tabella hash.");
        exit(1);
    }

    for(int i = 0; i < dimensione; i++){
        nodo *attuale = h->tabella[i];
        while(attuale){
            ptr_utente ut = attuale->utente;

            if(strcmp(prendi_nome(ut), nome) == 0 || strcmp(prendi_email(ut), email) == 0){
                return true;
            }

            attuale = attuale->prossimo;
        }
    }
    
    return false;
}