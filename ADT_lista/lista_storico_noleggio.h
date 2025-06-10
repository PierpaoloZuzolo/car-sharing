/*
Autore: Roberto Saporoso
Data: 01/06/2025
*/

#ifndef LISTA_STORICO_PRENOTAZIONI_H
#define LISTA_STORICO_PRENOTAZIONI_H

#include "lista.h"

typedef struct lista_noleggi *ptr_lista_noleggi;

/*
 Funzione: prendi_testa
 ----------------------

 Restituisce il puntatore al primo elemento (testa) della lista dei noleggi.

 Parametri:
    l: puntatore alla struttura `lista_noleggi`

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    - un puntatore al primo elemento della lista (`ptr_lista`)
    - NULL se la lista è vuota o non inizializzata

 Side-effect:
    Nessuno
 */
ptr_lista prendi_testa(ptr_lista_noleggi l);

/*
 Funzione: prendi_coda
 ---------------------

 Restituisce il puntatore all'ultimo elemento (coda) della lista dei noleggi.

 Parametri:
    l: puntatore alla struttura `lista_noleggi`

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    - un puntatore all’ultimo elemento della lista (`ptr_lista`)
    - NULL se la lista è vuota o non inizializzata

 Side-effect:
    Nessuno
 */
ptr_lista prendi_coda(ptr_lista_noleggi l);

/*
 Funzione: imposta_testa
 -----------------------

 Imposta il puntatore alla testa della lista dei noleggi.


 Parametri:
    lista: puntatore alla struttura `lista_noleggi`
    nodo: puntatore al nodo da impostare come testa

 Pre-condizioni:
    `lista` deve essere diverso da NULL

 Post-condizioni:
    La testa della lista punta al nodo specificato

 Ritorna:
    Nessuno

 Side-effect:
    Modifica il campo `testa` della struttura
 */
void imposta_testa(ptr_lista_noleggi lista, ptr_lista nodo);

/*
 Funzione: imposta_coda
 ----------------------

 Imposta il puntatore alla coda della lista dei noleggi.

 Parametri:
    lista: puntatore alla struttura `lista_noleggi`
    nodo: puntatore al nodo da impostare come coda

 Pre-condizioni:
    `lista` deve essere diverso da NULL

 Post-condizioni:
    La coda della lista punta al nodo specificato

 Ritorna:
    Nessuno

 Side-effect:
    Modifica il campo `coda` della struttura
 */
void imposta_coda(ptr_lista_noleggi lista, ptr_lista nodo);

/*
 Funzione: crea_lista_storico
 ----------------------------

 Alloca e inizializza una nuova lista per lo storico dei noleggi.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    La struttura `lista_noleggi` è inizializzata con testa e coda a NULL

 Ritorna:
    Puntatore alla nuova lista, oppure NULL in caso di errore di allocazione

 Side-effect:
    Alloca memoria dinamicamente
 */
ptr_lista_noleggi crea_lista_storico();

/*
 Funzione: lista_storico_vuota
 -----------------------------

 Verifica se la lista dello storico dei noleggi è vuota.

 Parametri:
    l: puntatore alla struttura `lista_noleggi`

 Pre-condizioni:
    `l` deve essere valido e inizializzato

 Post-condizioni:
    Nessuna

 Ritorna:
    true se la lista è vuota, false altrimenti

 Side-effect:
    Nessuno
 */
bool lista_storico_vuota(ptr_lista_noleggi l);

/*
 Funzione: metti_nodo_in_testa
 -----------------------------

 Inserisce un nuovo nodo contenente un valore all'inizio della lista storico.

 Parametri:
    l: puntatore alla struttura `lista_noleggi`
    valore: puntatore alla struttura `storico` da inserire

 Pre-condizioni:
    `l` deve essere valido e inizializzato

 Post-condizioni:
    La lista ha un nuovo nodo in testa contenente `valore`

 Ritorna:
    Nessuno

 Side-effect:
    Modifica il puntatore `testa` della lista
 */
void metti_nodo_in_testa(ptr_lista_noleggi l, ptr_storico valore);

/*
 Funzione: sposta_puntatore_coda
 -------------------------------

 Avanza il puntatore `coda` della lista storico al nodo successivo.

 Parametri:
    l: puntatore alla struttura `lista_noleggi`

 Pre-condizioni:
    `l` deve essere valido

 Post-condizioni:
    Il puntatore `coda` punta al nodo successivo, o NULL se non esiste

 Ritorna:
    Nessuno

 Side-effect:
    Modifica il campo `coda` della struttura `lista_noleggi`
 */
void sposta_puntatore_coda(ptr_lista_noleggi l);

/*
 Funzione: prendi_prenotazione_da_lista
 --------------------------------------

 Restituisce il puntatore alla struttura `storico` contenuta in un nodo della lista.

 Parametri:
    nodo: puntatore al nodo della lista

 Pre-condizioni:
    `nodo` deve essere valido (non NULL)

 Post-condizioni:
    Nessuna

 Ritorna:
    Puntatore alla struttura `storico` contenuta nel nodo, oppure NULL se il nodo è NULL

 Side-effect:
    Nessuno
 */
ptr_storico prendi_prenotazione_da_lista(ptr_lista nodo);

/*
 Funzione: metti_dopo_coda
 -------------------------

 Inserisce un nuovo nodo dopo il nodo attualmente puntato da `coda` nella lista dei noleggi.

 Parametri:
    l: puntatore alla struttura `lista_noleggi`
    valore: puntatore alla struttura `storico` da inserire

 Pre-condizioni:
    `l` e `l->coda` devono essere validi (non NULL)

 Post-condizioni:
    Un nuovo nodo contenente `valore` è inserito dopo il nodo puntato da `coda`

 Ritorna:
    Nessuno

 Side-effect:
    Modifica la lista collegata aggiornando i puntatori dei nodi
 */
void metti_dopo_coda(ptr_lista_noleggi l, ptr_storico valore);

/*
 Funzione: distruggi_lista_storico_noleggio
 ------------------------------------------

 Distrugge completamente la lista dello storico dei noleggi, liberando tutta la memoria associata.

 Parametri:
    l: puntatore alla struttura `lista_noleggi` da distruggere

 Pre-condizioni:
    `l` deve essere un puntatore valido o NULL

 Post-condizioni:
    Tutta la memoria associata alla lista e ai suoi elementi è liberata

 Ritorna:
    Nessuno

 Side-effect:
    Libera memoria dinamica e invalida i puntatori alla lista
 */
void distruggi_lista_storico_noleggio(ptr_lista_noleggi l);




#endif






