/*
Autore: Roberto Saporoso
Data: 10/05/2025
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "tab_hash.h"

typedef struct item {
    char *chiave;
    void *valore;
} Item;

typedef struct nodo {
    Item *item;
    struct nodo *prossimo;
} Nodo;

struct tabella_hash {
    int dimensione;
    Nodo **buckets;
};


/*
 Funzione: hash_fun
 ------------------

 Calcola un valore di hash per una stringa utilizzando l'algoritmo SDBM.

 Implementazione:
    Inizializza un valore `hash` a 0.
    Per ogni carattere della stringa, aggiorna il valore di hash secondo la formula:
        hash = c + (hash << 6) + (hash << 16) - hash;
    L'uso di shift e sottrazione permette una buona distribuzione dei bit.

 Parametri:
    str: puntatore alla stringa da convertire in valore hash

 Pre-condizioni:
    str deve essere non NULL e puntare a una stringa terminata da '\0'

 Post-condizioni:
    nessuna

 Ritorna:
    un numero intero positivo di tipo unsigned long che rappresenta l'hash della stringa

 Side-effect:
    nessuno
 */
static unsigned long hash_fun(const char *str) {
    unsigned long hash = 0;
    int c;

    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

/*
  Funzione: crea_tabella_hash
  ----------------------------
 
  Crea e inizializza una nuova tabella hash della dimensione specificata.
 
  Implementazione:
     Alloca memoria per una struttura `tabella_hash` e per un array di puntatori a bucket.
     Ogni bucket è inizializzato a NULL tramite `calloc`.
 
  Parametri:
     dimensione: dimensione della tabella hash (numero di bucket)
 
  Pre-condizioni:
     dimensione > 0
 
  Post-condizioni:
     se l'allocazione della memoria ha successo, viene restituito un puntatore a una struttura ptr_tabella_hash inizializzata;
     altrimenti viene restituito NULL.
 
  Ritorna:
     un puntatore a una nuova struttura ptr_tabella_hash o NULL in caso di errore
 
  Side-effect:
     alloca memoria dinamicamente per la struttura tabella hash e l'array di bucket
 */

ptr_tabella_hash crea_tabella_hash(int dimensione) {
    if (dimensione <= 0) return NULL;

    ptr_tabella_hash h = malloc(sizeof(struct tabella_hash));
    if (!h) return NULL;

    h->dimensione = dimensione;
    h->buckets = calloc(dimensione, sizeof(Nodo *));
    if (!h->buckets) {
        free(h);
        return NULL;
    }

    return h;
}

/*
 Funzione: inserisci_in_hash
 ---------------------------

 Inserisce un nuovo elemento nella tabella hash associando una chiave a un valore.

 Implementazione:
    Calcola l'indice del bucket tramite la funzione di hash `djb2_hash`.
    Controlla se la chiave è già presente nel bucket corrispondente, evitando duplicati.
    Se non è presente, alloca un nuovo Item e un nuovo Nodo, copia la chiave,
    collega il nodo all'inizio della lista del bucket.

 Parametri:
    h: puntatore alla tabella hash
    chiave: stringa che rappresenta la chiave dell'elemento da inserire
    valore: puntatore al valore da associare alla chiave

 Pre-condizioni:
    h deve essere non NULL
    chiave deve essere non NULL
    valore deve essere non NULL

 Post-condizioni:
    se l'inserimento ha successo, la tabella conterrà un nuovo elemento con la chiave indicata;
    se la chiave è già presente o si verifica un errore di allocazione, la tabella non viene modificata.

 Ritorna:
    true se l'inserimento è andato a buon fine,
    false in caso di errore o chiave duplicata

 Side-effect:
    alloca memoria dinamicamente per la nuova chiave, per l'item e per il nodo
 */

bool inserisci_in_hash(ptr_tabella_hash h, const char *chiave, void *valore) {
    if (!h || !chiave || !valore) return false;

    unsigned long indice = hash_fun(chiave) % h->dimensione;
    Nodo *corrente = h->buckets[indice];

    while (corrente) {
        if (strcmp(corrente->item->chiave, chiave) == 0) {
            return false; // duplicato
        }
        corrente = corrente->prossimo;
    }

    Item *nuovo_item = malloc(sizeof(Item));
    if (!nuovo_item) return false;

    nuovo_item->chiave = strdup(chiave);
    nuovo_item->valore = valore;

    Nodo *nuovo_nodo = malloc(sizeof(Nodo));
    if (!nuovo_nodo) {
        free(nuovo_item->chiave);
        free(nuovo_item);
        return false;
    }

    nuovo_nodo->item = nuovo_item;
    nuovo_nodo->prossimo = h->buckets[indice];
    h->buckets[indice] = nuovo_nodo;

    return true;
}


/*
 Funzione: cerca_in_hash
 -----------------------

 Cerca un elemento nella tabella hash dato il valore della sua chiave.

 Implementazione:
    Calcola l'indice del bucket tramite la funzione di hash `djb2_hash`.
    Scorre la lista di nodi nel bucket corrispondente, confrontando le chiavi.
    Se trova un nodo con chiave uguale a quella cercata, restituisce il valore associato.

 Parametri:
    h: puntatore alla tabella hash
    chiave: stringa che rappresenta la chiave da cercare

 Pre-condizioni:
    h deve essere non NULL
    chiave deve essere non NULL

 Post-condizioni:
    la tabella non viene modificata

 Ritorna:
    il puntatore al valore associato alla chiave se trovato,
    NULL se la chiave non è presente o se i parametri sono invalidi

 Side-effect:
    nessuno
 */

void *cerca_in_hash(ptr_tabella_hash h, const char *chiave) {
    if (!h || !chiave) return NULL;

    unsigned long indice = hash_fun(chiave) % h->dimensione;
    Nodo *corrente = h->buckets[indice];

    while (corrente) {
        if (strcmp(corrente->item->chiave, chiave) == 0) {
            return corrente->item->valore;
        }
        corrente = corrente->prossimo;
    }

    return NULL;
}

/*
 Funzione: distruggi_hash
 ------------------------

 Libera tutta la memoria allocata per la tabella hash, inclusi i nodi, le chiavi,
 gli item e i valori associati se specificato.

 Implementazione:
    Itera su ogni bucket della tabella, scorrendo la lista collegata di nodi.
    Per ogni nodo, libera prima l'item, poi la chiave, e infine il nodo stesso.
    Se è fornita una funzione `distruggi_valore`, la chiama per liberare il valore associato.
    Infine libera l'array dei bucket e la struttura della tabella.

 Parametri:
    h: puntatore alla tabella hash da distruggere
    distruggi_valore: funzione per liberare la memoria occupata da ciascun valore (può essere NULL)

 Pre-condizioni:
    h può essere NULL; se non lo è, deve essere stato creato correttamente

 Post-condizioni:
    tutta la memoria associata alla tabella viene liberata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente
    può chiamare una funzione fornita dall'utente per liberare i valori
 */

void distruggi_hash(ptr_tabella_hash h, void (*distruggi_valore)(void *)) {
    if (!h) return;

    for (int i = 0; i < h->dimensione; ++i) {
        Nodo *corrente = h->buckets[i];
        while (corrente) {
            Nodo *tmp = corrente;
            corrente = corrente->prossimo;

            if (tmp->item) {
                free(tmp->item->chiave);
                if (distruggi_valore && tmp->item->valore)
                    distruggi_valore(tmp->item->valore);
                free(tmp->item);
            }
            free(tmp);
        }
    }

    free(h->buckets);
    free(h);
}

/*
 Funzione: dimensione_hash
 -------------------------

 Restituisce la dimensione (cioè il numero di bucket) della tabella hash.

 Implementazione:
    Verifica se il puntatore alla tabella è valido.
    In caso positivo, restituisce il valore del campo `dimensione`.
    In caso contrario, restituisce 0.

 Parametri:
    h: puntatore alla tabella hash

 Pre-condizioni:
    nessuna (il puntatore può essere NULL)

 Post-condizioni:
    nessuna

 Ritorna:
    la dimensione della tabella se `h` è valido, 0 altrimenti

 Side-effect:
    nessuno
 */

int dimensione_hash(ptr_tabella_hash h) {
    return h ? h->dimensione : 0;
}


/*
 Funzione: ottieni_valori_hash
 -----------------------------

 Restituisce un array di tutti i valori presenti nella tabella hash.

 Implementazione:
    Scorre tutti i bucket della tabella hash.
    Conta quanti elementi totali ci sono e poi crea un array di puntatori ai valori.
    Popola l'array con i valori contenuti in ogni nodo.

 Parametri:
    h: puntatore alla tabella hash
    numero_elementi: puntatore a intero dove verrà scritto il numero di elementi trovati

 Pre-condizioni:
    h deve essere non NULL
    numero_elementi deve essere un puntatore valido

 Post-condizioni:
    se la tabella contiene elementi, restituisce un array di puntatori ai valori;
    il chiamante è responsabile di liberare la memoria dell'array (ma non i valori).

 Ritorna:
    un array allocato dinamicamente di `void *` contenente i valori,
    o NULL in caso di errore o se la tabella è vuota

 Side-effect:
    alloca memoria per l'array dei risultati
*/
void **ottieni_valori_hash(ptr_tabella_hash h, int *numero_elementi) 
{
    if (!h || !numero_elementi) return NULL;

    *numero_elementi = 0;

    // Prima passata: conta gli elementi
    for (int i = 0; i < h->dimensione; ++i) {
        Nodo *corrente = h->buckets[i];
        while (corrente) {
            (*numero_elementi)++;
            corrente = corrente->prossimo;
        }
    }

    if (*numero_elementi == 0) return NULL;

    // Seconda passata: raccoglie i valori
    void **valori = malloc(sizeof(void *) * (*numero_elementi));
    if (!valori) return NULL;

    int idx = 0;
    for (int i = 0; i < h->dimensione; ++i) {
        Nodo *corrente = h->buckets[i];
        while (corrente) {
            valori[idx++] = corrente->item->valore;
            corrente = corrente->prossimo;
        }
    }

    return valori;
}
