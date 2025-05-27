#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utente.h"
#include "hash.h"


struct utente{
    char nome[50];
    char email[100];
};



/*
 Funzione: inizia_utente
 -----------------------
 Crea e inizializza un nuovo utente con nome ed email forniti.

 Parametri:
   nome: stringa contenente il nome dell'utente.
   email: stringa contenente l'email dell'utente.

  Pre-condizione:
   nome ed email devono essere puntatori validi (non NULL).

 Post-condizione:
   Un nuovo utente viene creato con i dati forniti.

 Ritorna:
   Un puntatore al nuovo utente allocato e inizializzato,
   oppure NULL se l'allocazione fallisce.
*/
ptr_utente inizia_utente(const char *nome, const char *email)
{
    ptr_utente nuovo_utente = malloc(sizeof(struct utente));
    if(nuovo_utente){
        strncpy(nuovo_utente->nome, nome, sizeof(nuovo_utente->nome) - 1);
        nuovo_utente->nome[sizeof(nuovo_utente->nome) - 1] = '\0';

        strncpy(nuovo_utente->email, email, sizeof(nuovo_utente->email) - 1);
        nuovo_utente->email[sizeof(nuovo_utente->email) - 1] = '\0';

    } 
    
    return nuovo_utente; 
}


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
   La stringa nome se ut è valido,
   altrimenti NULLITEM.
*/
char *prendi_nome(ptr_utente ut)
{
    // Se il puntatore utente è valido, restituisce il nome, altrimenti NULLITEM per indicare assenza.
    return ut ? ut->nome : NULLITEM; 
}


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
   La stringa email se ut è valido,
   altrimenti NULLITEM.
*/
char *prendi_email(ptr_utente ut)
{
    // Se il puntatore utente è valido, restituisce l'email, altrimenti NULLITEM per indicare assenza.
    return ut ? ut->email : NULLITEM;
}

