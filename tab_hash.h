#ifndef HASH_H
#define HASH_H

typedef struct tabella_hash *TabellaHash;


/*
  Funzione: crea_tabella_hash
  ----------------------------
 
  Crea e inizializza una nuova tabella hash della dimensione specificata.
  
  Parametri:
     dimensione: dimensione della tabella hash (numero di bucket)
 
  Pre-condizioni:
     dimensione > 0
 
  Post-condizioni:
     se l'allocazione della memoria ha successo, viene restituito un puntatore a una struttura TabellaHash inizializzata;
     altrimenti viene restituito NULL.
 
  Ritorna:
     un puntatore a una nuova struttura TabellaHash o NULL in caso di errore
 
  Side-effect:
     alloca memoria dinamicamente per la struttura tabella hash e l'array di bucket
 */

TabellaHash crea_tabella_hash(int dimensione);

/*
 Funzione: inserisci_in_hash
 ---------------------------

 Inserisce un nuovo elemento nella tabella hash associando una chiave a un valore.

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

bool inserisci_in_hash(TabellaHash h, const char *chiave, void *valore);

/*
 Funzione: cerca_in_hash
 -----------------------

 Cerca un elemento nella tabella hash dato il valore della sua chiave.

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

void *cerca_in_hash(TabellaHash h, const char *chiave);

/*
 Funzione: distruggi_hash
 ------------------------

 Libera tutta la memoria allocata per la tabella hash, inclusi i nodi, le chiavi,
 gli item e i valori associati se specificato.

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

void distruggi_hash(TabellaHash h, void (*distruggi_valore)(void *));

/*
 Funzione: dimensione_hash
 -------------------------

 Restituisce la dimensione (cioè il numero di bucket) della tabella hash.

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

int dimensione_hash(TabellaHash h);

#endif