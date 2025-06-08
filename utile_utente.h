#ifndef UTILE_UTENTE_H
#define UTILE_UTENTE_H

#include "utente.h"

#define NULLITEM NULL


/*
 Funzione: stampa_utente
 -----------------------
 Stampa a video le informazioni dell'utente.

 Parametri:
   ut: puntatore all'utente da stampare.

 Pre-condizione:
   ut deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica all'utente.

 Ritorna:
   Nessun valore. Produce stampa a video.
*/
void stampa_utente(ptr_utente ut);


/*
 Funzione: salva_utente_su_file
 ------------------------------
 Salva i dati di un utente su due file:
  - Un file generico (append) che elenca nome ed email di tutti gli utenti
  - Un file dedicato all'utente, con nome "nome_utente.txt",
    contenente i dettagli specifici (nome, email, sconto, ecc.)

 Parametri:
   nome_file: percorso del file generico dove aggiungere utente
   ut: puntatore alla struttura utente da salvare

 Pre-condizione:
   ut deve essere un puntatore valido

 Post-condizione:
   I file vengono creati/aggiornati con i dati dell'utente

 Valore di ritorno:
   Nessuno (void)
*/
void salva_utente_su_file(char *nome_file, ptr_utente ut);


/*
 Funzione: carica_utente_da_file
 -------------------------------
 Carica un utente da un file e lo inserisce in una struttura hash.

 Parametri:
   nome_file: stringa contenente il nome del file da cui leggere.
   h: puntatore alla tabella hash in cui inserire l'utente.

 Pre-condizione:
   nome_file e h devono essere puntatori validi.

 Post-condizione:
   Un utente viene caricato dal file e inserito nella tabella hash.

 Ritorna:
   Nessun valore.
*/
void carica_utente_da_file(const char *nome_file, ptr_hash_utenti h);


/*
 Funzione: libera_utente
 -----------------------
 Libera la memoria occupata da un utente.

 Parametri:
   ut: puntatore all'utente da liberare.

 Pre-condizione:
   ut deve essere un puntatore valido.

 Post-condizione:
   La memoria occupata dall'utente è liberata.

 Ritorna:
   Nessun valore.
*/
void libera_utente(ptr_utente ut);


#endif