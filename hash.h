#ifndef HASH_H
#define HASH_H

#include "utente.h"

typedef struct tabella_hash *ptr_hash;

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT TABELLAHASH
========================================================================

===============================
Specifica Sintattica
===============================

L’ADT tabella_hash rappresenta una tabella hash che memorizza elementi di tipo `PtrUtente`.

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
- ptr_hash  
   Puntatore opaco a una struttura dati che rappresenta una tabella hash.
   Ogni cella contiene una lista collegata di nodi con:
   - ptr_utente utente -> utente memorizzato
   - nodo* prossimo -> puntatore al nodo successivo

-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- hash                      : (char nome[], char email[], int dimensione) -> unsigned int  
- nuova_tabella_hash        : (int dimensione) -> ptr_hash  
- inserisci_hash            : (ptr_hash h, ptr_utente utente) -> bool  
- cerca_utente              : (ptr_hash h, ptr_utente utente) -> ptr_utente  
- distruggi_hash            : (ptr_hash h) -> void  
- dimensione_hash           : (ptr_hash h) -> int
- verifica_duplicati_utenti : (ptr_hash h, consta char *nome, const char *email) -> bool

-------------------------------------------------------------
Operatori con descrizione e specifica:
-------------------------------------------------------------

1. unsigned int hash(char nome[], char email[], int dimensione)  
   • Descrizione: Funzione di hash che calcola un indice a partire da nome, email e dimensione.  
   • Specifica: Restituisce un valore compreso tra 0 e dimensione-1 calcolato da nome ed email.

2. ptr_hash nuova_tabella_hash(int dimensione)  
   • Descrizione: Alloca e inizializza una nuova tabella hash.  
   • Specifica: Se l’allocazione ha successo, restituisce una nuova tabella hash con `dimensione` celle inizializzate a NULL.

3. bool inserisci_hash(ptr_hash h, ptr_utente utente)  
   • Descrizione: Inserisce un nuovo utente nella tabella hash se non già presente.  
   • Specifica: Se `utente != NULL` e non esiste già un utente con la stessa email in `h`, 
     inserisce l’utente nella lista collegata nella cella corrispondente all’hash, e restituisce `true`; altrimenti `false`.

4. ptr_utente cerca_utente(ptr_hash h, ptr_utente utente)  
   • Descrizione: Cerca un utente nella tabella hash.  
   • Specifica: Se un utente con la stessa email è presente in `h`, restituisce il puntatore all'utente corrispondente; altrimenti `NULL`.

5. void distruggi_hash(ptr_hash h)  
   • Descrizione: Libera tutta la memoria associata alla tabella hash.  
   • Specifica: Libera ogni nodo presente nelle liste collegate e tutti gli utenti associati, poi libera la tabella e la struttura `h`.

6. int dimensione_hash(ptr_hash h)
   • Descrizione: Restituisce la dimensione della tabella hash.
   • Specifica: Se h != NULL, restituisce h->dimensione, altrimenti 0.

7. bool verifica_duplicati_utenti(ptr_hash h, const char *nome, const char *email)
   • Descrizione: Cerca nella tabella hash se il nome o il cognome sono già inseriti.
   • Specifica: Se il nome inserito o la email inserita sono già presenti nella tabella hash, la funzione restituisce true, false altrimenti.
===============================
Specifica Semantica
===============================

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
ptr_hash: insieme delle tabelle hash valide  
ptr_utente: struttura contenente dati di un utente (nome, email)  
char*: sequenza di caratteri terminata da '\0'  
BOOLEANO: {vero, falso}

-------------------------------------------------------------
Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:
-------------------------------------------------------------

1. hash(nome, email, dimensione) =  valore_hash
   • pre: nome ed email sono stringhe valide, dimensione > 0  
   • post: restituisce un valore compreso tra 0 e dimensione-1, derivato dai caratteri di nome ed email

2. nuova_tabella_hash(dimensione)  = h
   • pre: dimensione > 0  
   • post: alloca una nuova tabella hash con `dimensione` celle inizializzate a NULL

3. inserisci_hash(h, utente)  = true\false
   • pre: h != NULL, utente != NULL  
   • post: se un utente con la stessa email non è presente, viene aggiunto e restituisce true; altrimenti restituisce false e libera `utente` duplicato

4. cerca__utente(h, utente)  = attuale->utente
   • pre: h != NULL, utente != NULL  
   • post: restituisce un PtrUtente con stessa email se presente, altrimenti NULL

5. distruggi_hash(h) 
   • pre: h != NULL  
   • post: libera tutta la memoria associata a `h`, incluse le liste e i dati utente

6. dimensione_hash(h) = h->dimensione
   • pre: h != NULL
   • post: restituisce un int che ha come valore la dimensione della tabella hash

7. verifica_duplicati_utenti(h, nome, email) = true\false
   • pre: nome e email sono stringhe valide e h != NULL
   • post: restituisce true se trova nome o email già esistenti, altrimenti false
*/


unsigned int hash(char nome[], char email[], int dimensione);

ptr_hash nuova_tabella_hash(int dimensione);

bool inserisci_hash(ptr_hash h, ptr_utente utente);

ptr_utente cerca_utente(ptr_hash h, ptr_utente utente);

void distruggi_hash(ptr_hash h);

int dimensione_hash(ptr_hash h);

bool verifica_duplicati_utenti(ptr_hash h, const char *nome, const char *email);



#endif