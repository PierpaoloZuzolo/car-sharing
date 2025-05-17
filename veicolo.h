#ifndef VEICOLO_H
#define VEICOLO_H

typedef struct veicolo *ptr_veicolo;

#include "lista_veicoli.h"


/*
 Funzione: inizia_veicolo
 ------------------------
 Crea e inizializza un nuovo veicolo con i dati specificati.

 Parametri:
   marca_veicolo: stringa contenente la marca del veicolo
   modello_veicolo: stringa contenente il modello del veicolo
   targa_veicolo: stringa contenente la targa del veicolo
   posizione_veicolo: stringa che rappresenta la posizione attuale del veicolo

 Pre-condizione:
   Tutti i parametri devono essere stringhe valide terminate da '\0'.

 Post-condizione:
   Alloca dinamicamente una struttura veicolo e copia i dati ricevuti nei rispettivi campi.

 Ritorna:
   Un puntatore alla nuova struttura veicolo allocata,
   oppure NULL in caso di errore di allocazione.
*/
ptr_veicolo inizia_veicolo(const char *marca_veicolo, const char *modello_veicolo, const char *targa_veicolo, const char *posizione_veicolo);

/*
 Funzione: prendi_marca
 ----------------------
 Restituisce la marca di un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare la marca

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente la marca del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_marca(ptr_veicolo ve);

/*
 Funzione: prendi_modello
 ------------------------
 Restituisce il modello di un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare il modello

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente il modello del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_modello(ptr_veicolo ve);


/*
 Funzione: prendi_targa
 ----------------------
 Restituisce la targa di un veicolo.

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare la targa

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente la targa del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_targa(ptr_veicolo ve);

/*
 Funzione: prendi_stato
 ----------------------
 Restituisce lo stato corrente del veicolo (es. "disponibile", "occupato").

 Parametri:
   ve: puntatore alla struttura veicolo da cui prelevare lo stato

 Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica allo stato del veicolo

 Ritorna:
   Una stringa contenente lo stato del veicolo,
   oppure NULL se il puntatore ve è NULL
*/
char *prendi_stato(ptr_veicolo ve);



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
 Libera la memoria associata a un veicolo.

 Parametri:
   ve: puntatore al veicolo da liberare

 Pre-condizione:
   ve deve essere un puntatore valido a una struttura veicolo allocata dinamicamente

 Post-condizione:
   La memoria occupata dal veicolo viene liberata

 Ritorna:
   Nessun valore
*/
void libera_veicolo(ptr_veicolo ve);



#endif