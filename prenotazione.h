#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <stdbool.h>

/*
 Tipo astratto di dato: prenotazioni
 ----------------------------------
 Struttura che rappresenta le prenotazioni di un veicolo
 suddivise in slot giornalieri (es. 48 slot per 24 ore a intervalli di 30 min)
 per un periodo di 6 giorni (lunedì-sabato).
*/
typedef struct prenotazioni *ptr_prenotazione;


/*
 Funzione: inizializza_prenotazioni
 ----------------------------------
 Alloca e inizializza una struttura prenotazioni con tutti gli slot liberi.

 Parametri:
   Nessuno.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   La struttura prenotazioni è allocata e tutti gli slot sono azzerati (liberi).

 Ritorna:
   Puntatore alla nuova struttura prenotazioni,
   oppure NULL se l’allocazione fallisce.
*/
ptr_prenotazione inizializza_prenotazioni();


/*
 Funzione: carica_prenotazioni_da_file
 ------------------------------------
 Legge da file il contenuto delle prenotazioni per un veicolo,
 gestendo il reset automatico degli slot se è cambiato il giorno.

 Parametri:
   p: puntatore alla struttura prenotazioni da aggiornare.
   targa: stringa contenente la targa del veicolo, usata per costruire il nome file.

 Pre-condizione:
   p deve essere un puntatore valido.
   targa deve essere una stringa valida.

 Post-condizione:
   La struttura prenotazioni è aggiornata con i dati letti dal file,
   oppure azzerata se il file non esiste o il giorno è cambiato.
   Gli slot passati vengono bloccati.

 Ritorna:
   1 se la lettura da file è avvenuta con successo,
   0 se il file non esiste o il giorno è cambiato (prenotazioni resettate).
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
   Indice dello slot corrispondente all’orario,
   oppure -1 se l’orario inserito è non valido.
*/
int leggi_cella_da_orario(const char *messaggio);


/*
 Funzione: veicolo_disponibile_oggi
 ----------------------------------
 Verifica se esiste almeno uno slot libero oggi.

 Parametri:
   p: puntatore alla struttura prenotazioni da controllare.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica.

 Ritorna:
   true se almeno uno slot è libero,
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
 Tenta di prenotare un intervallo di slot consecutivi.

 Parametri:
   p: puntatore alla struttura prenotazioni.
   inizio_slot: indice dello slot di inizio (incluso).
   fine_slot: indice dello slot di fine (escluso).

 Pre-condizione:
   p deve essere un puntatore valido.
   inizio_slot e fine_slot devono essere indici validi e inizio_slot < fine_slot.

 Post-condizione:
   Se possibile, gli slot nell’intervallo sono marcati come prenotati.

 Ritorna:
   1 se la prenotazione ha successo,
   0 se uno o più slot nell’intervallo sono già occupati o intervallo non valido.
*/
int prenota_intervallo(ptr_prenotazione p, int inizio_slot, int fine_slot);


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
 Blocca gli slot di prenotazione che sono già passati
 in base all’orario corrente.

 Parametri:
   p: puntatore alla struttura prenotazioni da aggiornare.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Tutti gli slot antecedenti all’orario corrente sono marcati come occupati.
   
 Ritorna:
   Nessun valore.
*/
void blocca_celle_passate(ptr_prenotazione p);

#endif
