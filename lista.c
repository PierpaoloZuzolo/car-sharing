/*
Autore: Carmine Saporoso
Data: 25/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"

struct nodo{
    void *oggetto;
    struct nodo *prossimo;
};


/*
 Funzione: crea_lista
 --------------------

 Crea e inizializza una nuova lista vuota.

 Implementazione:
    Restituisce semplicemente NULL, che indica una lista vuota.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Viene restituito un puntatore NULL, rappresentante una lista vuota.

 Ritorna:
    NULL, che indica una lista vuota

 Side-effect:
    Nessuno
 */
ptr_lista crea_lista()
{
    return NULL;
}


/*
 Funzione: lista_vuota
 ---------------------

 Verifica se una lista è vuota.

 Implementazione:
    Controlla se il puntatore alla lista è NULL.

 Parametri:
    l: puntatore alla lista da verificare

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    Nessuna

 Ritorna:
    true se la lista è vuota (NULL), false altrimenti

 Side-effect:
    Nessuno
 */
bool lista_vuota(ptr_lista l)
{
    return l == NULL;
}


/*
 Funzione: metti_nodo
 --------------------

 Crea un nuovo nodo della lista con un valore specificato e collega il nodo successivo.

 Implementazione:
    Alloca memoria per un nuovo nodo, assegna il valore e imposta il puntatore al nodo successivo.

 Parametri:
    valore: puntatore al dato da memorizzare nel nodo
    prossimo_nodo: puntatore al nodo successivo nella lista

 Pre-condizioni:
    valore deve essere diverso da NULL

 Post-condizioni:
    Viene creato un nuovo nodo con il valore specificato collegato al prossimo nodo

 Ritorna:
    Puntatore al nuovo nodo creato, oppure NULL se fallisce l'allocazione o valore è NULL

 Side-effect:
    Alloca memoria dinamicamente
 */
ptr_lista metti_nodo(void *valore, ptr_lista prossimo_nodo)
{
    if(valore){
        ptr_lista nuovo_nodo = malloc(sizeof(struct nodo));
        nuovo_nodo->oggetto = valore;
        nuovo_nodo->prossimo = prossimo_nodo;
        return nuovo_nodo;
    }

    return NULL;
}


/*
 Funzione: prendi_prossimo
 ------------------------

 Restituisce il puntatore al nodo successivo nella lista collegata.

 Implementazione:
    Controlla se il nodo è valido e ritorna il puntatore al nodo successivo, altrimenti NULL.

 Parametri:
    nodo: puntatore al nodo corrente della lista

 Pre-condizioni:
    nodo può essere NULL o valido

 Post-condizioni:
    Nessuna modifica alla lista

 Ritorna:
    Puntatore al nodo successivo, oppure NULL se il nodo è NULL o non ha successivo

 Side-effect:
    Nessuno
 */
ptr_lista prendi_prossimo(ptr_lista nodo)
{
    if(nodo){
        return nodo->prossimo;
    }

    return NULL;
}


/*
 Funzione: cambia_prossimo_nodo
 ------------------------------

 Imposta il puntatore al nodo successivo di un nodo specificato.

 Implementazione:
    Verifica che il nodo corrente sia valido, quindi assegna il nuovo nodo successivo.

 Parametri:
    nodo_corrente: puntatore al nodo della lista da modificare
    nodo_prossimo: puntatore al nodo che sarà il nuovo successivo

 Pre-condizioni:
    nodo_corrente deve essere diverso da NULL

 Post-condizioni:
    Il campo `prossimo` di `nodo_corrente` viene aggiornato a `nodo_prossimo`

 Ritorna:
    Nessuno

 Side-effect:
    Modifica il collegamento della lista puntata da `nodo_corrente`
 */
void cambia_prossimo_nodo(ptr_lista nodo_corrente, ptr_lista nodo_prossimo)
{
    if(nodo_corrente){
        nodo_corrente->prossimo = nodo_prossimo;
    }
}


/*
 Funzione: prendi_oggetto
 -----------------------

 Restituisce il puntatore all’oggetto contenuto in un nodo della lista.

 Implementazione:
    Controlla se il nodo è valido e ritorna il puntatore all’oggetto memorizzato, altrimenti NULL.

 Parametri:
    nodo: puntatore al nodo della lista

 Pre-condizioni:
    nodo può essere NULL o valido

 Post-condizioni:
    Nessuna modifica alla lista o all’oggetto

 Ritorna:
    Puntatore all’oggetto contenuto nel nodo, oppure NULL se il nodo è NULL

 Side-effect:
    Nessuno
 */
void *prendi_oggetto(ptr_lista nodo)
{
    if(nodo){
        return nodo->oggetto;
    }

    return NULL;
}


/*
 Funzione: distruggi_nodo
 ------------------------

 Libera la memoria di un nodo della lista e dell’oggetto contenuto, usando una funzione distruttrice opzionale.

 Implementazione:
    Se il nodo è valido, chiama la funzione distruttrice sull’oggetto se fornita, poi libera la memoria del nodo.

 Parametri:
    nodo: puntatore al nodo da distruggere
    distruggi_oggetto: puntatore a funzione per liberare la memoria dell’oggetto contenuto, oppure NULL

 Pre-condizioni:
    nodo può essere NULL o valido
    distruggi_oggetto può essere NULL

 Post-condizioni:
    La memoria del nodo e dell’oggetto (se distruggi_oggetto è fornito) è liberata

 Ritorna:
    Nessuno

 Side-effect:
    Libera memoria dinamica
 */
void distruggi_nodo(ptr_lista nodo, void (*distruggi_oggetto)(void *)) 
{
    if (nodo) {
        if (nodo->oggetto && distruggi_oggetto) {
            distruggi_oggetto(nodo->oggetto);  // chiama il distruttore specifico per l'oggetto
        }
        free(nodo);  // libera il nodo
    }
}


/*
 Funzione: distruggi_lista
 -------------------------

 Libera tutta la memoria occupata da una lista collegata, inclusi gli oggetti contenuti se fornita una funzione distruttrice.

 Implementazione:
    Itera su tutti i nodi della lista, per ogni nodo chiama la funzione distruttrice sull’oggetto (se fornita) e libera il nodo.

 Parametri:
    l: puntatore al primo nodo della lista
    distruggi_oggetto: puntatore a funzione per liberare la memoria degli oggetti contenuti, oppure NULL

 Pre-condizioni:
    l può essere NULL o puntare a una lista valida
    distruggi_oggetto può essere NULL

 Post-condizioni:
    Tutta la memoria dei nodi e degli oggetti (se distruggi_oggetto è fornito) è liberata

 Ritorna:
    Nessuno

 Side-effect:
    Libera memoria dinamica
 */
void distruggi_lista(ptr_lista l, void (*distruggi_oggetto)(void *)) 
{
    while (l != NULL) {
        ptr_lista temp = l;
        l = l->prossimo;
        if (distruggi_oggetto && temp->oggetto) {
            distruggi_oggetto(temp->oggetto);  // chiama il distruttore
        }
        free(temp);
    }
}


