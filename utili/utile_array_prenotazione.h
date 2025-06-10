/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

#ifndef UTILE_PRENOTAZIONE_H
#define UTILE_PRENOTAZIONE_H

#include "ADT_array/array_prenotazione.h"

/*
 Funzione: carica_prenotazioni_da_file
 -------------------------------------

 Carica le prenotazioni associate a una targa da un file, aggiornando la struttura
 di prenotazione fornita in input. Se il giorno è cambiato o il file non esiste,
 azzera la prenotazione e salva uno stato iniziale aggiornato.

 Parametri:
    p: puntatore a una struttura di prenotazione valida.
    targa: stringa che rappresenta la targa del veicolo, usata per accedere al file.

 Pre-condizioni:
    - p deve essere un puntatore valido a una struttura di prenotazione inizializzata.
    - targa deve essere una stringa valida e non NULL.

 Post-condizioni:
    - La struttura di prenotazione `p` sarà aggiornata in base al contenuto del file o inizializzata.
    - Il file associato alla targa sarà aggiornato con lo stato corrente delle prenotazioni.

 Ritorna:
    - 1 se il file è stato letto correttamente e i dati sono stati caricati.
    - 0 se era un nuovo giorno o se il file non esisteva (stato inizializzato).

 Side-effect:
    - Lettura/scrittura da/per file.
    - Output aggiornato salvato su file.
*/
int carica_prenotazioni_da_file(ptr_prenotazione p, const char *targa);


/*
 Funzione: salva_prenotazioni_su_file
 -----------------------------------

 Salva su file lo stato corrente delle prenotazioni giornaliere relative a un veicolo
 identificato tramite la sua targa.

 Parametri:
    p     : puntatore alla struttura contenente le prenotazioni
    targa : stringa identificativa del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido
    targa deve essere una stringa valida e non vuota
    La funzione ottiene_cella deve restituire il valore corretto della cella di prenotazione

 Post-condizioni:
    Il file associato alla targa è aggiornato con lo stato corrente delle prenotazioni.

 Ritorna:
    void

 Side-effect:
    Effettua scrittura su file
*/
void salva_prenotazioni_su_file(ptr_prenotazione p, const char *targa);





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