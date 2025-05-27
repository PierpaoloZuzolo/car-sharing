#ifndef UTENTE_H
#define UTENTE_H

#define NULLITEM NULL

/*
 Tipo astratto di dato: utente
 -----------------------------
 Rappresenta un utente con nome ed email.
*/
typedef struct utente *ptr_utente;

#include "hash.h"


/*
 Funzione: inizia_utente
 -----------------------
 Crea e inizializza un nuovo utente con nome ed email.

 Parametri:
   nome: stringa contenente il nome dell'utente.
   email: stringa contenente l'email dell'utente.

 Pre-condizione:
   nome ed email devono essere puntatori validi (non NULL).

 Post-condizione:
   Un nuovo utente viene creato con i dati forniti.

 Ritorna:
   Puntatore all'utente creato,
   oppure NULL in caso di errore.
*/
ptr_utente inizia_utente(const char *nome, const char *email);


/*
 Funzione: prendi_nome
 ---------------------
 Restituisce il nome dell'utente.

 Parametri:
   ut: puntatore all'utente.

 Pre-condizione:
   ut deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica all'utente.

 Ritorna:
   Puntatore alla stringa contenente il nome dell'utente.
*/
char *prendi_nome(ptr_utente ut);


/*
 Funzione: prendi_email
 ----------------------
 Restituisce l'email dell'utente.

 Parametri:
   ut: puntatore all'utente.

 Pre-condizione:
   ut deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica all'utente.

 Ritorna:
   Puntatore alla stringa contenente l'email dell'utente.
*/
char *prendi_email(ptr_utente ut);


#endif
