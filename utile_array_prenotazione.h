#ifndef UTILE_PRENOTAZIONE_H
#define UTILE_PRENOTAZIONE_H

#include "array_prenotazione.h"

/*
 Funzione: carica_prenotazioni_da_file
 ------------------------------------
 Legge da file il contenuto delle prenotazioni per un veicolo,
 gestendo il reset automatico delle celle se è cambiato il giorno.

 Parametri:
   p: puntatore alla struttura prenotazioni da aggiornare.
   targa: stringa contenente la targa del veicolo, usata per costruire il nome file.

 Pre-condizione:
   p deve essere un puntatore valido.
   targa deve essere una stringa valida.

 Post-condizione:
   La struttura prenotazioni è aggiornata con i dati letti dal file,
   oppure azzerata se il file non esiste o il giorno è cambiato.
   Le celle passate vengono bloccate.

 Ritorna:
   1 se la lettura da file è avvenuta con successo,
   0 se il file non esiste o il giorno è cambiato (prenotazioni ripristinate).
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


/*
 Funzione: costo_noleggio
 -------------------------
 Calcola il costo totale del noleggio di un veicolo in base 
 all’intervallo orario specificato e ad un eventuale sconto.

 Parametri:
   inizio_cella: indice della cella iniziale del noleggio (inclusivo).
   fine_cella: indice della cella finale del noleggio (esclusivo).
   sconto: valore intero. Se multiplo di 5, applica una tariffa scontata.

 Pre-condizione:
   inizio_cella e fine_cella devono essere compresi tra 0 e 48,
   con inizio_cella < fine_cella.
   Il valore di sconto deve essere >= 0.

 Post-condizione:
   Viene stampato il costo totale del noleggio.
   Il valore di ritorno rappresenta il costo calcolato.

 Ritorna:
   Il costo del noleggio come valore float.
*/
float costo_noleggio(int inizio_cella, int fine_cella, int sconto);



/*
 Funzione: leggi_cella_da_orario
 -------------------------------
 Legge un orario da tastiera nel formato "HH MM" (ore e minuti)
 e converte l'orario nell'indice corrispondente della cella.

 Parametri:
   messaggio: messaggio da mostrare all'utente per richiedere l'input.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   Nessuna modifica a variabili esterne.

 Valore di ritorno:
   Restituisce l'indice della cella corrispondente all'orario inserito.
   Continua a richiedere l'input finché non viene inserito un orario valido
   con ore tra 0 e 24 e minuti solo 0 o 30.
*/
int leggi_cella_da_orario(const char *messaggio);



/*
 Funzione: veicolo_disponibile_oggi
 ----------------------------------
 Verifica se esiste almeno una cella libera oggi.

 Parametri:
   p: puntatore alla struttura prenotazioni da controllare.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica.

 Ritorna:
   true se almeno una cella è libera,
   false altrimenti.
*/
bool veicolo_disponibile_oggi(ptr_prenotazione p);


/*
 Funzione: libera_prenotazioni
 -----------------------------
 Libera la memoria allocata per la struttura prenotazioni.

 Parametri:
   p: puntatore alla struttura prenotazioni da liberare.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   La memoria della struttura è liberata.

 Ritorna:
   Nessun valore.
*/
void libera_prenotazioni(ptr_prenotazione p);


/*
 Funzione: mostra_orari_disponibili
 ----------------------------------
 Mostra tutti gli orari disponibili (liberi) per un veicolo in base alla struttura delle celle.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Gli intervalli orari disponibili (celle con valore 0) vengono stampati a video.

 Effetti:
   Nessuna modifica allo stato interno della struttura.
*/
void mostra_orari_disponibili(ptr_prenotazione p);



void blocca_celle_passate(ptr_prenotazione p);



#endif