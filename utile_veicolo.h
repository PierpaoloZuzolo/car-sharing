#ifndef UTILE_VEICOLO_H
#define UTILE_VEICOLO_H

#include "veicolo.h"
#include "lista_veicoli.h"

/*
 Funzione: stampa_veicolo
 ------------------------
 Stampa a schermo le informazioni principali di un veicolo:
 marca, modello, targa, posizione e stato.

 Parametri:
   ve: puntatore alla struttura veicolo da stampare

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica alla struttura veicolo

 Ritorna:
   Nessun valore. La funzione produce output a video.
*/
void stampa_veicolo(ptr_veicolo ve);


/*
 Funzione: carica_veicoli_da_file
 -------------------------------
 Carica i dati dei veicoli da un file di testo e li inserisce in una lista.

 Parametri:
   nome_file: nome del file da cui leggere i veicoli
   l: puntatore alla lista in cui inserire i veicoli letti

 Pre-condizione:
   Il file deve essere formattato correttamente con righe contenenti marca, modello, targa e posizione

 Post-condizione:
   Tutti i veicoli letti dal file vengono inseriti nella lista l

 Ritorna:
   Nessun valore. Se il file non è accessibile, il programma termina con errore.
*/
void carica_veicoli_da_file(const char *nome_file, ptr_lista l);



/*
 Funzione: libera_veicolo
 ------------------------
 Libera la memoria associata a un veicolo, inclusa la memoria delle sue prenotazioni.

 Parametri:
   ve: puntatore al veicolo da liberare

 Pre-condizione:
   ve deve essere un puntatore valido a una struttura veicolo allocata dinamicamente

 Post-condizione:
   La memoria occupata dal veicolo e dalle sue prenotazioni viene liberata

 Ritorna:
   Nessun valore
*/
void libera_veicolo(ptr_veicolo ve);


/*
 Funzione: aggiorna_stato_veicolo
 --------------------------------
 Aggiorna lo stato del veicolo in base alla sua disponibilità odierna.

 Parametri:
   ve: puntatore al veicolo di cui aggiornare lo stato

 Pre-condizione:
   ve deve essere un puntatore valido a una struttura veicolo

 Post-condizione:
   Il campo 'stato' del veicolo viene aggiornato a "disponibile" se il veicolo è disponibile oggi,
   altrimenti a "non disponibile".

 Ritorna:
   true se il veicolo non è disponibile oggi,
   false se il veicolo è disponibile o se il puntatore è nullo
*/
bool aggiorna_stato_veicolo(ptr_veicolo ve);



#endif