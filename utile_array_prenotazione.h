/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

#ifndef UTILE_PRENOTAZIONE_H
#define UTILE_PRENOTAZIONE_H

#include "array_prenotazione.h"

/*
 Funzione: carica_prenotazioni_da_file
 ------------------------------------

 Carica le prenotazioni giornaliere da file per un dato veicolo identificato dalla targa,
 aggiorna la struttura in memoria, e gestisce il reset e il blocco delle celle temporali
 in base alla data corrente.

 Parametri:
    p     : puntatore alla struttura prenotazione da aggiornare
    targa : stringa identificativa del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido a una struttura prenotazione
    targa deve essere una stringa valida e non NULL
    Le funzioni vedi_se_giorno_nuovo, azzera_celle, blocca_celle_passate,
    salva_prenotazioni_su_file e imposta_cella devono essere definite e funzionanti

 Post-condizioni:
    La struttura prenotazione è aggiornata con i dati caricati dal file o inizializzata se necessario.
    Il file storico delle prenotazioni viene aggiornato in base allo stato attuale.

 Ritorna:
    1 se la struttura è stata caricata da file con successo
    0 se è stato un nuovo giorno o il file non esisteva (dunque struttura inizializzata)

 Side-effect:
    Modifica la struttura prenotazione in memoria
    Effettua letture e scritture su file corrispondente alla targa
    Effettua stampe di errore su stdout se presenti (non implementato esplicitamente)
*/
int carica_prenotazioni_da_file(ptr_prenotazione p, const char *targa);


/*
 Funzione: salva_prenotazioni_su_file
 -----------------------------------
 Salva su file le prenotazioni aggiornate di un veicolo.

 Parametri:
   p: puntatore alla struttura prenotazioni da salvare.
   targa: stringa contenente la targa del veicolo, usata per costruire il nome file.

 Pre-condizione:
   p deve essere un puntatore valido.
   targa deve essere una stringa valida.

 Post-condizione:
   Il file con le prenotazioni viene aggiornato.

 Ritorna:
   Nessun valore.
*/
void salva_prenotazioni_su_file(ptr_prenotazione p, const char *targa);


//DA FAREEEE
float costo_noleggio(int inizio_cella, int fine_cella, int sconto);



/*
 Funzione: leggi_cella_da_orario
 -------------------------------

 Legge da input un orario nel formato "HH MM" (ore minuti) e lo converte nell'indice
 di una cella oraria, considerando che ogni ora è divisa in due celle (00 e 30 minuti).

 Parametri:
    messaggio : stringa da mostrare come prompt all'utente per la lettura dell'orario

 Pre-condizioni:
    messaggio deve essere una stringa valida non nulla

 Post-condizioni:
    Nessuna modifica a variabili esterne

 Ritorna:
    L'indice intero della cella oraria corrispondente all'orario inserito (da 0 a 48)

 Side-effect:
    Stampa messaggi su stdout e legge da stdin
*/
int leggi_cella_da_orario(const char *messaggio);



/*
 Funzione: veicolo_disponibile_oggi
 ----------------------------------

 Verifica se un veicolo ha almeno una cella oraria libera (non prenotata) nell'arco
 della giornata corrente.

 Parametri:
    p: puntatore alla struttura prenotazione del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido a una struttura prenotazione

 Post-condizioni:
    Nessuna modifica ai dati puntati da p

 Ritorna:
    true se esiste almeno una cella libera (valore 0) nella giornata
    false se tutte le celle sono occupate o p è NULL

 Side-effect:
    Nessuno
*/
bool veicolo_disponibile_oggi(ptr_prenotazione p);


/*
 Funzione: libera_prenotazioni
 -----------------------------

 Libera la memoria allocata per la struttura prenotazione puntata da p.

 Parametri:
    p: puntatore alla struttura prenotazione da liberare

 Pre-condizioni:
    p deve essere un puntatore valido ottenuto da malloc o simile,
    oppure NULL (in questo caso la funzione non fa nulla).

 Post-condizioni:
    La memoria puntata da p viene liberata.

 Ritorna:
    void

 Side-effect:
    Libera memoria allocata dinamicamente.
*/
void libera_prenotazioni(ptr_prenotazione p);


/*
 Funzione: mostra_orari_disponibili
 ----------------------------------

 Stampa a video gli intervalli orari disponibili (liberi) rappresentati
 dalla struttura delle prenotazioni.

 Parametri:
    p: puntatore alla struttura prenotazione

 Pre-condizioni:
    p deve essere un puntatore valido.

 Post-condizioni:
    Vengono stampati su stdout gli intervalli orari liberi presenti nella prenotazione.

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout.
*/
void mostra_orari_disponibili(ptr_prenotazione p);


/*
 Funzione: blocca_celle_passate
 ------------------------------

 Blocca (imposta a 1) tutte le celle corrispondenti agli intervalli orari
 già trascorsi rispetto all’orario corrente, rendendoli indisponibili per prenotazioni.

 Parametri:
    p: puntatore alla struttura prenotazione da aggiornare.

 Pre-condizioni:
    p deve essere un puntatore valido.

 Post-condizioni:
    Le celle degli orari già trascorsi sono impostate a 1 (non prenotabili).

 Ritorna:
    void

 Side-effect:
    Modifica lo stato delle celle nella struttura prenotazione.
*/
void blocca_celle_passate(ptr_prenotazione p);



#endif