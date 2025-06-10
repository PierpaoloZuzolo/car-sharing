/*
Autore: Roberto Saporoso
Data: 01/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Modello_storico_noleggio/storico_noleggio.h"
#include "lista_storico_noleggio.h"
#include "lista.h"


struct  lista_noleggi{
    ptr_lista testa;
    ptr_lista coda;
};

/*
 Funzione: prendi_testa
 ----------------------

 Restituisce il puntatore al primo elemento (testa) della lista dei noleggi.

 Implementazione:
    Verifica che la lista sia non nulla e restituisce il puntatore alla testa.
    In caso contrario, restituisce NULL.

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
ptr_lista prendi_testa(ptr_lista_noleggi l)
{
    return l ? l->testa : NULL;
}

/*
 Funzione: prendi_coda
 ---------------------

 Restituisce il puntatore all'ultimo elemento (coda) della lista dei noleggi.

 Implementazione:
    Verifica che la lista sia non nulla e restituisce il puntatore alla coda.
    In caso contrario, restituisce NULL.

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
ptr_lista prendi_coda(ptr_lista_noleggi l)
{
    return l ? l->coda : NULL;
}


/*
 Funzione: imposta_testa
 -----------------------

 Imposta il puntatore alla testa della lista dei noleggi.

 Implementazione:
    Se il puntatore alla lista è valido, assegna il nodo specificato al campo `testa`.

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
void imposta_testa(ptr_lista_noleggi lista, ptr_lista nodo) {
    if (!lista) return;
    lista->testa = nodo;
}


/*
 Funzione: imposta_coda
 ----------------------

 Imposta il puntatore alla coda della lista dei noleggi.

 Implementazione:
    Se il puntatore alla lista è valido, assegna il nodo specificato al campo `coda`.

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
void imposta_coda(ptr_lista_noleggi lista, ptr_lista nodo) {
    if (!lista) return;
    lista->coda = nodo;
}


/*
 Funzione: crea_lista_storico
 ----------------------------

 Alloca e inizializza una nuova lista per lo storico dei noleggi.

 Implementazione:
    Alloca memoria per la struttura `lista_noleggi`, inizializza `testa` a NULL tramite `crea_lista()`
    e imposta `coda` a NULL.

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
ptr_lista_noleggi crea_lista_storico() {
    ptr_lista_noleggi lista = malloc(sizeof(struct lista_noleggi));
    if (!lista) {
        return NULL; 
    }
    lista->testa = crea_lista(); // cioè NULL
    lista->coda = NULL;
    return lista;
}



/*
 Funzione: lista_storico_vuota
 -----------------------------

 Verifica se la lista dello storico dei noleggi è vuota.

 Implementazione:
    Controlla se la testa della lista è NULL tramite la funzione `lista_vuota`.

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
bool lista_storico_vuota(ptr_lista_noleggi l) {
    return lista_vuota(l->testa);
}


/*
 Funzione: metti_nodo_in_testa
 -----------------------------

 Inserisce un nuovo nodo contenente un valore all'inizio della lista storico.

 Implementazione:
    Se la lista è vuota, crea un nuovo nodo con valore e prossimo NULL.
    Altrimenti, crea un nuovo nodo con valore e prossimo la testa attuale della lista.
    Aggiorna la testa della lista con il nuovo nodo.

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
void metti_nodo_in_testa(ptr_lista_noleggi l, ptr_storico valore) {
    if(lista_vuota(l->testa)) {
        l->testa = metti_nodo(valore, NULL);
    } else {
        l->testa = metti_nodo(valore, l->testa);
    }
}



/*
 Funzione: sposta_puntatore_coda
 -------------------------------

 Avanza il puntatore `coda` della lista storico al nodo successivo.

 Implementazione:
    Se la lista e il puntatore `coda` sono validi, aggiorna `coda` al nodo successivo.

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
void sposta_puntatore_coda(ptr_lista_noleggi l) {
    if (l) {
        if (l->coda) {
            l->coda = prendi_prossimo(l->coda);
        }
    }
}


/*
 Funzione: prendi_prenotazione_da_lista
 --------------------------------------

 Restituisce il puntatore alla struttura `storico` contenuta in un nodo della lista.

 Implementazione:
    Se il nodo è valido, ritorna l’oggetto contenuto nel nodo castato a `ptr_storico`.

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
ptr_storico prendi_prenotazione_da_lista(ptr_lista nodo) {
    if(nodo) {
        return (ptr_storico) prendi_oggetto(nodo);
    }
    return NULL;
}



/*
 Funzione: metti_dopo_coda
 -------------------------

 Inserisce un nuovo nodo dopo il nodo attualmente puntato da `coda` nella lista dei noleggi.

 Implementazione:
    Se la lista e la coda esistono, crea un nuovo nodo con il valore dato e lo inserisce subito dopo il nodo di coda, aggiornando i puntatori di collegamento.

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
void metti_dopo_coda(ptr_lista_noleggi l, ptr_storico valore) {
    if (l && l->coda) {
        ptr_lista nuovo = metti_nodo(valore, prendi_prossimo(l->coda));
        cambia_prossimo_nodo(l->coda, nuovo);
    }
}


/*
 Funzione: distruggi_storico_in_lista
 ------------------------------------

 Funzione ausiliaria per liberare correttamente la memoria di un oggetto `storico` contenuto in una lista.

 Implementazione:
    Esegue il cast del puntatore generico a `ptr_storico` e chiama il distruttore specifico `distruggi_storico_noleggio`.

 Parametri:
    s: puntatore generico all'oggetto da distruggere, deve essere un `ptr_storico`

 Pre-condizioni:
    `s` deve essere un puntatore valido a una struttura `storico`

 Post-condizioni:
    La memoria associata all'oggetto storico viene liberata

 Ritorna:
    Nessuno

 Side-effect:
    Libera memoria dinamica allocata per l'oggetto storico
 */
static void distruggi_storico_in_lista(void *s) {
    ptr_storico ptr = (ptr_storico)s;
    distruggi_storico_noleggio(ptr);
}


/*
 Funzione: distruggi_lista_storico_noleggio
 ------------------------------------------

 Distrugge completamente la lista dello storico dei noleggi, liberando tutta la memoria associata.

 Implementazione:
    Chiama `distruggi_lista` sulla testa della lista passando come distruttore `distruggi_storico_in_lista` e quindi libera la struttura lista.

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
void distruggi_lista_storico_noleggio(ptr_lista_noleggi l) {
    if (l) {
        distruggi_lista(l->testa, distruggi_storico_in_lista);  
        free(l);
    }
}
