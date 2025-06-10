/*
Autore: Carmine Saporoso, Pierpaolo Zuzolo
Data: 07/06/2025
*/

#ifndef UTILE_LISTA_STORICO_PRENOTAZIONI_H
#define UTILE_LISTA_STORICO_PRENOTAZIONI_H

#include <stdbool.h>

#include "Modello_storico_noleggio/storico_noleggio.h"
#include "ADT_lista/lista_storico_noleggio.h"
#include "ADT_lista/lista.h"

/*
 Funzione: inserisci_nodo_storico_noleggio
 -----------------------------------------

 Inserisce un nuovo nodo nella lista dello storico noleggi rispettando la
 distinzione tra nodi eliminabili e non eliminabili.

 Parametri:
    lista: puntatore alla lista dei noleggi
    prenotazione: puntatore allo storico noleggio da inserire nella lista

 Pre-condizioni:
    `lista` e `prenotazione` devono essere puntatori validi e non NULL.

 Post-condizioni:
    Il nodo viene inserito nella lista in posizione corretta,
    la coda viene aggiornata se necessario.

 Ritorna:
    void

 Side-effect:
    Modifica la lista collegata e può aggiornare la coda.
 */
void inserisci_nodo_storico_noleggio(ptr_lista_noleggi lista, ptr_storico prenotazione);

/*
 Funzione: elimina_nodo_storico_noleggio
 ---------------------------------------

 Permette di eliminare un nodo dalla lista dei noleggi storici, scegliendo tra
 i nodi eliminabili (tutti se la coda è NULL, oppure solo quelli successivi alla coda).

 Parametri:
    lista                  : puntatore alla lista dei noleggi storici
    targa_veicolo_eliminato: array di char dove verrà copiata la targa del veicolo eliminato (dimensione minima 8)
    ora_inizio             : puntatore a int per memorizzare l’ora di inizio del noleggio eliminato
    minuto_inizio          : puntatore a int per memorizzare il minuto di inizio
    ora_fine               : puntatore a int per memorizzare l’ora di fine
    minuto_fine            : puntatore a int per memorizzare il minuto di fine

 Pre-condizioni:
    lista deve essere valida e non vuota
    puntatori per copia dati devono essere validi

 Post-condizioni:
    nodo scelto viene eliminato dalla lista e memoria liberata
    dati della prenotazione eliminata copiati nei parametri passati

 Ritorna:
    1 se l’eliminazione è avvenuta con successo
    0 in caso di errore, input non valido o annullamento

 Side-effect:
    stampa messaggi su stdout
    modifica la lista e libera la memoria del nodo eliminato
*/
int elimina_nodo_storico_noleggio(ptr_lista_noleggi lista, char *targa_veicolo_eliminato, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine);

/*
 Funzione: salva_lista_storico_noleggio_su_file
 ----------------------------------------------

 Salva su file il contenuto della lista dei noleggi storici di un utente.

 Parametri:
    lista       : puntatore alla lista dei noleggi storici
    nome_utente : stringa con il nome utente usato per il nome del file

 Pre-condizioni:
    lista e nome_utente devono essere validi e non NULL

 Post-condizioni:
    Su file "%s.txt" (dove %s è nome_utente) viene scritto lo storico dei noleggi

 Ritorna:
    void

 Side-effect:
    Scrive su file e produce output su stdout in caso di errore
*/
void salva_lista_storico_noleggio_su_file(ptr_lista_noleggi lista, char *nome_utente);

/*
 Funzione: carica_lista_storico_noleggio_da_file
 ----------------------------------------------

 Carica da file lo storico dei noleggi di un utente, inserendo le prenotazioni nella lista.

 Parametri:
    lista       : puntatore alla lista dei noleggi storici in cui inserire i dati
    nome_utente : stringa contenente il nome utente usato per costruire il nome del file

 Pre-condizioni:
    lista e nome_utente devono essere puntatori validi e non NULL
    il file "%s.txt" (dove %s è nome_utente) deve esistere ed essere leggibile
    il file deve rispettare il formato previsto con 13 campi separati da ';'

 Post-condizioni:
    La lista viene popolata con i nodi storico noleggio corrispondenti alle righe lette dal file

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout in caso di errore apertura file
    Modifica la lista inserendo nuovi nodi
*/
void carica_lista_storico_noleggio_da_file(ptr_lista_noleggi lista, char *nome_utente);

/*
 Funzione: aggiungi_prenotazione_storico_su_file
 ----------------------------------------------

 Aggiunge una nuova prenotazione allo storico dell'utente salvandola su file.

 Parametri:
    targa           : stringa con la targa del veicolo prenotato
    tipo_veicolo    : stringa con il tipo del veicolo
    nome_utente     : stringa con il nome utente proprietario dello storico
    ora_inizio      : ora di inizio noleggio
    minuto_inizio   : minuto di inizio noleggio
    ora_fine        : ora di fine noleggio
    minuto_fine     : minuto di fine noleggio
    costo           : costo totale del noleggio

 Pre-condizioni:
    targa, tipo_veicolo e nome_utente devono essere puntatori validi e non NULL
    Le funzioni data_attuale e ottieni_orario_corrente devono essere definite e funzionanti

 Post-condizioni:
    La prenotazione viene aggiunta in fondo al file storico dell'utente

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout in caso di errore apertura file
    Modifica il file di testo con l'aggiunta della nuova prenotazione
*/
void aggiungi_prenotazione_storico_su_file(const char *targa, const char *tipo_veicolo, const char *nome_utente, int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, float costo);

/*
 Funzione: stampa_lista_noleggi
 ------------------------------

 Stampa a video l'intero contenuto della lista dei noleggi storici.

 Parametri:
    l: puntatore alla lista dei noleggi storici da stampare

 Pre-condizioni:
    l deve essere un puntatore valido o NULL.
    La lista deve contenere nodi validi.

 Post-condizioni:
    Viene stampata la lista dei noleggi a video.

 Ritorna:
    Il numero di elementi stampati più 1 (indice di fine lista),
    oppure 0 se la lista è vuota o nulla.

 Side-effect:
    Effettua stampe su stdout.
 */
int stampa_lista_noleggi(ptr_lista_noleggi l);

/*
 Funzione: stampa_dopo_coda
 --------------------------

 Stampa a video gli elementi della lista dei noleggi storici a partire dal nodo successivo
 al nodo puntato come "coda".

 Parametri:
    l: puntatore alla lista dei noleggi storici

 Pre-condizioni:
    l deve essere un puntatore valido.
    La lista deve avere un puntatore coda valido.

 Post-condizioni:
    Viene stampata la porzione di lista che segue la coda.

 Ritorna:
    Il numero di elementi stampati più 1 (indice di fine lista),
    oppure 0 se non ci sono nodi dopo la coda o se input non valido.

 Side-effect:
    Effettua stampe su stdout.
 */
int stampa_dopo_coda(ptr_lista_noleggi l);


/*
 Funzione: conta_fino_a_coda
 ---------------------------

 Conta il numero di elementi nella lista dei noleggi, partendo dalla testa fino ad arrivare alla coda inclusa.


 Parametri:
    l: puntatore a una lista di noleggi (ptr_lista_noleggi)

 Pre-condizioni:
    l deve essere un puntatore valido a una lista non vuota, con testa e coda correttamente impostate.

 Post-condizioni:
    Nessuna modifica alla lista originale.

 Ritorna:
    Un intero che rappresenta il numero di elementi dalla testa alla coda inclusa.
    Se la coda non è raggiungibile dalla testa, restituisce 0.

 Side-effect:
    Nessuno.
*/

int conta_fino_a_coda(ptr_lista_noleggi l);


#endif