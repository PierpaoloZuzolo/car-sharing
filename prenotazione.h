#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <stdbool.h>

/*
 Tipo astratto di dato: prenotazioni
 ----------------------------------
 Struttura che rappresenta le prenotazioni di un veicolo
 suddivise in celle giornaliere (es. 48 slot per 24 ore a intervalli di 30 min)
 per un periodo di 6 giorni (lunedì-sabato).
*/
typedef struct prenotazioni *ptr_prenotazione;


/*
 Funzione: inizializza_prenotazioni
 ----------------------------------
 Alloca e inizializza una struttura prenotazioni con tutte le celle libere.

 Parametri:
   Nessuno.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   La struttura prenotazioni è allocata e tutte le celle sono azzerate (libere).

 Ritorna:
   Puntatore alla nuova struttura prenotazioni,
   oppure NULL se l’allocazione fallisce.
*/
ptr_prenotazione inizializza_prenotazioni();


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
 Funzione: leggi_cella_da_orario
 -------------------------------
 Richiede all’utente di inserire un orario (HH MM),
 verifica la correttezza e lo converte in indice di slot.

 Parametri:
   messaggio: stringa da visualizzare come prompt per l’inserimento.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   Nessuna modifica.

 Ritorna:
   Indice della cella corrispondente all’orario,
   oppure -1 se l’orario inserito è non valido.
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
 Funzione: prenota_intervallo
 ----------------------------
 Tenta di prenotare un intervallo di celle consecutive.

 Parametri:
   p: puntatore alla struttura prenotazioni.
   inizio_cella: indice dello celle di inizio (incluso).
   fine_cella: indice dello slot di fine (escluso).

 Pre-condizione:
   p deve essere un puntatore valido.
   inizio_cella e fine_cella devono essere indici validi e inizio_cella < fine_cella.

 Post-condizione:
   Se possibile, le celle nell’intervallo sono marcate come prenotate.

 Ritorna:
   1 se la prenotazione ha successo,
   0 se uno o più celle nell’intervallo sono già occupate o intervallo non valido.
*/
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);


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
 Funzione: blocca_celle_passate
 -----------------------------
 Blocca le celle di prenotazione che sono già passate
 in base all’orario corrente.

 Parametri:
   p: puntatore alla struttura prenotazioni da aggiornare.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Tutti le celle antecedenti all’orario corrente sono marcate come occupate.
   
 Ritorna:
   Nessun valore.
*/
void blocca_celle_passate(ptr_prenotazione p);


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

#endif
