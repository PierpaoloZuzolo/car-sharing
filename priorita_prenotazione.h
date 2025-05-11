#ifndef PRIORITA_PRENOTAZIONE_H
#define PRIORITA_PRENOTAZIONE_H

#define MASSIMO 100

typedef struct c_CP* codapriorita;

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT C_CP
========================================================================

Specifica Sintattica

L’ADT C_CP è definito come un tipo opaco che rappresenta una lista concatenata di prenotazioni,
gestita in ordine di priorità
Vengono definiti i seguenti tipi ed operatori:

-------------------------------------------------------------
Tipi: C_CP, CODAPRIORITA
-------------------------------------------------------------
- C_CP:
  Un record che rappresenta una prenotazione ed è definito come:
    - PRENOTAZIONE vet[MASSIMO]   → Prenotazioni (PRENOTAZIONE, massimo 50 prenotazioni).
    - int grandezza               → Numero attuale di prenotazione.

- CODAPRIORITA:
  Un puntatore a una struttura (tipo opaco) che rappresenta una coda a priorità di prenotazioni.
  La struttura interna (i nodi della lista) è nascosta agli utilizzatori.

-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- CPnuova     : ( ) → CODAPRIORITA
- CPvuota   : (CODAPRIORITA) → BOOLEAN
- ottieniMassimo    : (CODAPRIORITA) → ITEM
- scendi: (CODAPRIORITA coda) → VOID
- eliminaMassimo : (CODAPRIORITA) → CODAPRIORITA
- sali: (CODAPRIORITA coda) → VOID
- inserisci  : (CODAPRIORITA, ITEM) → CODAPRIORITA

1. codapriorita CPnuova ( )
   • Descrizione: Crea e restituisce una coda a priorità vuota.
   • Specifica: Restituisce una coda 'coda' tale che coda->grande == 0.

2. int CPvuota (codapriorita coda)
   • Descrizione: Verifica se la coda a priorità è vuota.
   • Specifica: Restituisce true se coda == NULL o se list->grandezza == 0, false altrimenti.

3 PRENOTAZIONE ottieniMassimo (codapriorita coda)
   • Descrizione: Ritorna la prenotazione al primo indice.
   • Specifica: Se la lista iniziale è [r₁, r₂, …, rₙ], ottieniMassimo(coda) restituisce [r₁].

4. static void scendi (codapriorita coda)
   • Descrizione: Fa scendere un elemento nella lista secondo il tempo e restituisce la lista aggiornata.
   • Specifica: Se coda = [r₁, r₂, …, rₙ] allora scendi(coda) restituisce [r₂, …, rₙ, r₁].

5. int eliminaMassimo (codapriorita coda)
   • Descrizione: Rimuove il primo elemento della coda e restituisce la lista aggiornata.
   • Specifica: Se coda = [r₁, r₂, …, rₙ] allora eliminaMassimo(coda) restituisce [r₂, …, rₙ].

6. static void sali (codapriorita coda)
   • Descrizione: Fa salire un elemento nella lista secondo il tempo e restituisce la lista aggiornata.
   • Specifica: Se coda = [r₁, r₂, …, rₙ, rₙ₊₁] allora sali(coda) restituisce [r₁, rₙ₊₁, r₂, …, rₙ].

7. int inserisci(codapriorita coda, prenotazione* richiesta)
   • Descrizione: Inserisce la prenotazione all'ultima posizione della coda.
   • Specifica: Se coda = [r₁, r₂, …, rₙ] allora inserisci(coda, chiave) restituisce [r₁, r₂, …, rₙ, rₙ₊₁].

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
            pre: Nessuna.
            post: CP = ᴧ.

2.    CPvuota(CP) = v
            pre: CP deve essere valida.
            post: Se CP è vuota, allora v = vero, altrimenti v = falso.

3.    ottieniMassimo(CP) = richiesta
            pre: CP non è vuota.
            post: Richiesta è la entry con la massima priorità fra quelle contenute in CP.

4.    scendi (CP) = static void
               pre: CP deve essere valida e deve avere alemeno 2 elementi.
               post: La funzione non restituisce nulla, ma modifica la struttura CP.
               side effect: Non restituisce nulla, ma va a modificare CP, poiché è un puntatore
               poiché viene passata per riferimento

5.    eliminaMassimo(CP) = CP’
               pre: CP non è vuota.
               post: CP’ contiene tutte le entry di CP tranne quella con massima priorità.

6.    sali(CP) = static void
               pre: CP deve essere valida e deve avere almeno 2 elementi.
               post: nessuna.
               side effect: Non restituisce nulla, ma va a modificare CP, poiché è un puntatore
               poiché viene passata per riferimento
               
7.    inserisci (CP, Richiesta) = CP’
               pre:  CP deve essere valida.
                     Richiesta deve essere una prenotazione valida.
               post: CP’ contiene elem e tutte le entry contenute in CP. 

*/

codapriorita CPnuova( );
int CPvuota(codapriorita coda);
prenotazione* ottieniMassimo(codapriorita coda);
static void scendi(codapriorita coda);
int eliminaMassimo(codapriorita coda);
static void sali(codapriorita coda);
int inserisci(codapriorita coda, prenotazione* richiesta);


#endif 