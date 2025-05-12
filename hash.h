#ifndef HASH_H
#define HASH_H

#include "utente.h"

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT PtrHash
========================================================================

===============================
Specifica Sintattica
===============================

L’ADT PtrHash rappresenta una tabella hash che memorizza elementi di tipo `PtrUtente`.

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
- PtrHash  
    Puntatore opaco a una struttura dati che rappresenta una tabella hash.
    Ogni cella contiene una lista collegata di nodi con:
    - PtrUtente utente → utente memorizzato
    - nodo* prossimo → puntatore al nodo successivo

-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- hash                  : (char nome[], char email[], int dimensione) → unsigned int  
- NuovaTabellaHash      : (int dimensione) → PtrHash  
- InserisciHash         : (PtrHash h, PtrUtente utente) → bool  
- CercaUtente           : (PtrHash h, PtrUtente utente) → PtrUtente  
- DistruggiHash         : (PtrHash h) → void  

-------------------------------------------------------------
Operatori con descrizione e specifica:
-------------------------------------------------------------

1. unsigned int hash(char nome[], char email[], int dimensione)  
   • Descrizione: Funzione di hash che calcola un indice a partire da nome, email e dimensione.  
   • Specifica: Restituisce un valore compreso tra 0 e dimensione-1 calcolato da nome ed email.

2. PtrHash NuovaTabellaHash(int dimensione)  
   • Descrizione: Alloca e inizializza una nuova tabella hash.  
   • Specifica: Se l’allocazione ha successo, restituisce una nuova tabella hash con `dimensione` celle inizializzate a NULL.

3. bool InserisciHash(PtrHash h, PtrUtente utente)  
   • Descrizione: Inserisce un nuovo utente nella tabella hash se non già presente.  
   • Specifica: Se `utente != NULL` e non esiste già un utente con la stessa email in `h`, 
     inserisce l’utente nella lista collegata nella cella corrispondente all’hash, e restituisce `true`; altrimenti `false`.

4. PtrUtente CercaUtente(PtrHash h, PtrUtente utente)  
   • Descrizione: Cerca un utente nella tabella hash.  
   • Specifica: Se un utente con la stessa email è presente in `h`, restituisce il puntatore all'utente corrispondente; altrimenti `NULL`.

5. void DistruggiHash(PtrHash h)  
   • Descrizione: Libera tutta la memoria associata alla tabella hash.  
   • Specifica: Libera ogni nodo presente nelle liste collegate e tutti gli utenti associati, poi libera la tabella e la struttura `h`.

===============================
Specifica Semantica
===============================

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
PtrHash: insieme delle tabelle hash valide  
PtrUtente: struttura contenente dati di un utente (nome, email)  
char*: sequenza di caratteri terminata da '\0'  
BOOLEANO: {vero, falso}

-------------------------------------------------------------
Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:
-------------------------------------------------------------

1. hash(nome, email, dimensione)  
   • pre: nome ed email sono stringhe valide, dimensione > 0  
   • post: restituisce un valore compreso tra 0 e dimensione-1, derivato dai caratteri di nome ed email

2. NuovaTabellaHash(dimensione)  
   • pre: dimensione > 0  
   • post: alloca una nuova tabella hash con `dimensione` celle inizializzate a NULL

3. InserisciHash(h, utente)  
   • pre: h != NULL, utente != NULL  
   • post: se un utente con la stessa email non è presente, viene aggiunto e restituisce true; altrimenti restituisce false e libera `utente` duplicato

4. CercaUtente(h, utente)  
   • pre: h != NULL, utente != NULL  
   • post: restituisce un PtrUtente con stessa email se presente, altrimenti NULL

5. DistruggiHash(h)  
   • pre: h != NULL  
   • post: libera tutta la memoria associata a `h`, incluse le liste e i dati utente

*/


typedef struct tabellaHash *PtrHash;

unsigned int hash(char nome[], char email[], int dimensione);

PtrHash NuovaTabellaHash(int dimensione);

bool InserisciHash(PtrHash h, PtrUtente utente);

PtrUtente CercaUtente(PtrHash h, PtrUtente utente);

void DistruggiHash(PtrHash h);



#endif