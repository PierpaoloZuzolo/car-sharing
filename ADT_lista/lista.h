/*
Autore: Carmine Saporoso
Data: 25/05/2025
*/

#ifndef LISTA_H
#define LISTA_H

typedef struct nodo *ptr_lista;

/*
 Funzione: crea_lista
 --------------------

 Crea e inizializza una nuova lista vuota.

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
ptr_lista crea_lista();

/*
 Funzione: lista_vuota
 ---------------------

 Verifica se una lista è vuota.

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
bool lista_vuota(ptr_lista l);

/*
 Funzione: metti_nodo
 --------------------

 Crea un nuovo nodo della lista con un valore specificato e collega il nodo successivo.

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
ptr_lista metti_nodo(void *valore, ptr_lista prossimo_nodo);

/*
 Funzione: prendi_prossimo
 ------------------------

 Restituisce il puntatore al nodo successivo nella lista collegata.

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
ptr_lista prendi_prossimo(ptr_lista nodo);

/*
 Funzione: cambia_prossimo_nodo
 ------------------------------

 Imposta il puntatore al nodo successivo di un nodo specificato.

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
void cambia_prossimo_nodo(ptr_lista nodo_corrente, ptr_lista nodo_prossimo);

/*
 Funzione: prendi_oggetto
 -----------------------

 Restituisce il puntatore all’oggetto contenuto in un nodo della lista.

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
void *prendi_oggetto(ptr_lista nodo);

/*
 Funzione: distruggi_nodo
 ------------------------

 Libera la memoria di un nodo della lista e dell’oggetto contenuto, usando una funzione distruttrice opzionale.

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
void distruggi_nodo(ptr_lista nodo, void (*distruggi_oggetto)(void *));

/*
 Funzione: distruggi_lista
 -------------------------

 Libera tutta la memoria occupata da una lista collegata, inclusi gli oggetti contenuti se fornita una funzione distruttrice.

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
void distruggi_lista(ptr_lista l, void (*distruggi_oggetto)(void *));


#endif