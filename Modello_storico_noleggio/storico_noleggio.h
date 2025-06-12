/*
Autore: Roberto Saporoso
Data: 07/06/2025
*/

#ifndef STORICO_PRENOTAZIONE_H
#define STORICO_PRENOTAZIONE_H

#include <stdbool.h>

typedef struct storico_noleggio *ptr_storico;

/*
 Funzione: inizia_storico_noleggio
 ---------------------------------

 Alloca e inizializza una nuova struttura storico_noleggio con i dati forniti.

 Parametri:
    gg: giorno della prenotazione
    mm: mese della prenotazione
    aa: anno della prenotazione
    ora: ora della prenotazione
    minuto: minuto della prenotazione
    tipo_v: stringa che rappresenta il tipo di veicolo
    targa_v: stringa che rappresenta la targa del veicolo
    nome_ut: stringa con il nome dell’utente
    costo: costo totale del noleggio
    inizio_ora: ora di inizio noleggio
    inizio_minuto: minuto di inizio noleggio
    fine_ora: ora di fine noleggio
    fine_minuto: minuto di fine noleggio

 Pre-condizioni:
    Le stringhe tipo_v, targa_v e nome_ut devono essere valide e terminate da '\0'

 Post-condizioni:
    Viene creato un nuovo storico di noleggio con i valori impostati

 Ritorna:
    Puntatore alla struttura storico inizializzata, oppure NULL se fallisce l’allocazione

 Side-effect:
    Alloca memoria dinamicamente
*/
ptr_storico inizia_storico_noleggio( int gg, int mm, int aa, int ora, int minuto ,char *tipo_v, char *targa_v, char *nome_ut, float costo, int inizio_ora, int inizio_minuto, int fine_ora, int fine_minuto);

/*
 Funzione: prendi_giorno_noleggiato
 ----------------------------------

 Restituisce il giorno associato al noleggio storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il valore intero del giorno se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
*/
int prendi_giorno_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_mese_noleggiato
 -------------------------------

 Restituisce il mese associato al noleggio storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il valore intero del mese se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_mese_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_anno_noleggiato
 -------------------------------

 Restituisce l'anno associato al noleggio storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il valore intero dell'anno se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_anno_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_ora_noleggiato
 ------------------------------

 Restituisce l'ora associata al noleggio storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    L'ora (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_ora_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_minuto_noleggiato
 ---------------------------------

 Restituisce il minuto associato al noleggio storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il minuto (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_minuto_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_ora_inizio_noleggiato
 -------------------------------------

 Restituisce l'ora di inizio del noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    L'ora di inizio (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_ora_inizio_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_minuto_inizio_noleggiato
 ----------------------------------------

 Restituisce il minuto di inizio del noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il minuto di inizio (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_minuto_inizio_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_ora_fine_noleggiato
 -----------------------------------

 Restituisce l'ora di fine del noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    L'ora di fine (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_ora_fine_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_minuto_fine_noleggiato
 --------------------------------------

 Restituisce il minuto di fine del noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il minuto di fine (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_minuto_fine_noleggiato(ptr_storico pr);


/*
 Funzione: prendi_costo_noleggiato
 --------------------------------

 Restituisce il costo associato al noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il costo (float) se pr è valido, altrimenti -1.1

 Side-effect:
    Nessuno
 */
float prendi_costo_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_targa_veicolo_noleggiato
 ----------------------------------------

 Restituisce la targa del veicolo associato al noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Puntatore a stringa con la targa del veicolo, oppure NULL se pr è NULL

 Side-effect:
    Nessuno
 */
char *prendi_targa_veicolo_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_tipo_veicolo_noleggiato
 ---------------------------------------

 Restituisce il tipo di veicolo associato al noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Puntatore a stringa con il tipo di veicolo, oppure NULL se `pr` è NULL

 Side-effect:
    Nessuno
 */
char *prendi_tipo_veicolo_noleggiato(ptr_storico pr);

/*
 Funzione: prendi_utente_veicolo_noleggiato
 -----------------------------------------

 Restituisce il nome dell'utente associato al noleggio dallo storico.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Puntatore a stringa con il nome dell'utente, oppure NULL se `pr` è NULL

 Side-effect:
    Nessuno
 */
char *prendi_utente_veicolo_noleggiato(ptr_storico pr);

/*
 Funzione: stampa_storico_noleggio
 --------------------------------

 Stampa su standard output i dettagli di una prenotazione dallo storico noleggi.

 Parametri:
    s: puntatore a una struttura `storico_noleggio` contenente i dati della prenotazione

 Pre-condizioni:
    Il puntatore `s` può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    void

 Side-effect:
    Scrive su standard output (console)
 */
void stampa_storico_noleggio(ptr_storico s);


int vedi_se_noleggio_eliminabile(ptr_storico s);

/*
 Funzione: distruggi_storico_noleggio
 ------------------------------------

 Libera la memoria occupata da una struttura `storico_noleggio`.

 Parametri:
    s: puntatore a una struttura `storico_noleggio` da distruggere

 Pre-condizioni:
    s deve essere un puntatore valido o NULL

 Post-condizioni:
    La memoria puntata da s viene liberata

 Ritorna:
    void

 Side-effect:
    Libera memoria dinamica
 */
void distruggi_storico_noleggio(ptr_storico s);


#endif