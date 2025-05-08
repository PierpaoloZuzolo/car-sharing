#ifndef PRIORITA_PRENOTAZIONE_H
#define PRIORITA_PRENOTAZIONE_H

#include "prenotazione.h"

typedef struct c_CP* CODAPRIORITA;

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT C_CP
========================================================================

Specifica Sintattica

L’ADT C_CP è definito come un tipo opaco che rappresenta una lista concatenata di prenotazioni,
gestita in ordine di priorità
Vengono definiti i seguenti tipi ed operatori:

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
- c_CP:
  Un record che rappresenta una prenotazione ed è definito come:
    - PRENOTAZIONE vet[MASSIMO]   -> Prenotazioni (PRENOTAZIONE, massimo 50 prenotazioni).
    - int grandezza               -> Numero attuale di prenotazione.

- CODAPRIORITA:
  Un puntatore a una struttura (tipo opaco) che rappresenta una coda a priorità di prenotazioni.
  La struttura interna (i nodi della lista) è nascosta agli utilizzatori.

-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- CPnuova     : ( ) → CODAPRIORITA
- CPvuota   : (CODAPRIORITA) → BOOLEAN
- ottieniMassimo    : (CODAPRIORITA) → ITEM
- eliminaMassimo : (CODAPRIORITA) → CODAPRIORITA
- scendi: (CODAPRIORITA coda) -> void
- inserisci  : (CODAPRIORITA, ITEM) → CODAPRIORITA
- sali: (CODAPRIORITA coda) -> void

1. CODAPRIORITA CPnuova ( )
   • Descrizione: Crea e restituisce una coda a priorità vuota.
   • Specifica: Restituisce una coda 'coda' tale che coda->grande == 0.

2. int CPvuota (CODAPRIORITA coda)
   • Descrizione: Verifica se la coda a priorità è vuota.
   • Specifica: Restituisce true se coda == NULL o se list->grandezza == 0, false altrimenti.

3 PRENOTAZIONE ottieniMassimo (CODAPRIORITA coda)
   • Descrizione: Ritorna la prenotazione al primo indice.
   • Specifica: Se la lista iniziale è [r₁, r₂, …, rₙ], ottieniMassimo(coda) restituisce [r₁].

4. int eliminaMassimo (CODAPRIORITA coda)
   • Descrizione: Rimuove il primo elemento della coda e restituisce la lista aggiornata.
   • Specifica: Se coda = [r₁, r₂, …, rₙ] allora eliminaMassimo(coda) restituisce [r₂, …, rₙ].

5. static void scendi (CODAPRIORITA coda)
   • Descrizione: Fa scendere un elemento nella lista secondo il tempo e restituisce la lista aggiornata.
   • Specifica: Se coda = [r₁, r₂, …, rₙ] allora scendi(coda) restituisce [r₂, …, rₙ, r₁].

6. int inserisci(CODAPRIORITA coda, int chiave)
   • Descrizione: Inserisce la prenotazione all'ultima posizione della coda.
   • Specifica: Se coda = [r₁, r₂, …, rₙ] allora inserisci(coda, chiave) restituisce [r₁, r₂, …, rₙ, rₙ₊₁].

7. static void sali (CODAPRIORITA coda)
   • Descrizione: Fa salire un elemento nella lista secondo il tempo e restituisce la lista aggiornata.
   • Specifica: Se coda = [r₁, r₂, …, rₙ, rₙ₊₁] allora sali(coda) restituisce [r₁, rₙ₊₁, r₂, …, rₙ].

========================================================================
SPECIFICA SEMANTICA

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
CODAPRIORITA= insieme delle code a priorità, dove:
ᴧ ϵ CODAPRIORITA (coda vuota)
BOOLEANO = {vero, falso}
ITEM = (K x V) è l’insieme delle coppie (k, v) con kϵK e vϵV
K è un insieme qualsiasi non vuoto sul quale è definita una relazione
d’ordine ≤
V è un insieme qualsiasi non vuoto

-------------------------------------------------------------
Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:

1.    CPnuova( ) = CP
            pre: nessuna
            post: CP = ᴧ

2.    CPvuota(CP) = v
            pre: CP deve essere valida
            post: se CP è vuota, allora v = vero, altrimenti v = falso

3.    ottieniMassimo(CP) = prenotazione
            pre: CP non è vuota
            post: prenotazione è la entry con la massima priorità fra quelle contenute in CP 

4.    eliminaMassimo(CP) = CP’
               pre: CP non è vuota
               post: CP’ contiene tutte le entry di CP tranne quella con massima priorità

5.    scendi (CP) = static void
               pre: CP deve essere valida e deve avere alemeno 2 elementi
               post: La funzione non restituisce nulla, ma modifica la struttura CP

6.    inserisci (CP, chiave) = CP’
               pre:  CP deve essere valida
                     chiave: deve essere un orario valido di inizio prenotazione
               post: CP’ contiene elem e tutte le entry contenute in CP 

7.    sali(CP) = static void
               pre: CP deve essere valida e deve avere almeno 2 elementi
               post: La funzione non restituisce nulla, ma modifica la struttura CP

*/

CODAPRIORITA CPnuova( );
int CPvuota(CODAPRIORITA coda);
PRENOTAZIONE ottieniMassimo(CODAPRIORITA coda);
int eliminaMassimo(CODAPRIORITA coda);
static void scendi(CODAPRIORITA coda);
int inserisci(CODAPRIORITA coda, PRENOTAZIONE prenotazione);
static void sali(CODAPRIORITA coda);


#endif 