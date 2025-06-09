/*
Autore: Roberto Saporoso
Data: 12/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "utente.h"


struct utente{
    char nome[50];
    char email[100];
};



/*
 Funzione: inizia_utente
 -----------------------

 Crea e inizializza una nuova struttura `utente` con nome ed email forniti.

 Implementazione:
    Alloca memoria per una nuova struttura `utente` e copia i valori di nome ed email 
    nelle rispettive stringhe, assicurandosi che siano terminate da '\0'.

 Parametri:
    nome: stringa contenente il nome dell'utente
    email: stringa contenente l'email dell'utente

 Pre-condizioni:
    nome e email devono essere stringhe valide non NULL

 Post-condizioni:
    Viene restituito un puntatore a una nuova struttura `utente` inizializzata,
    oppure NULL in caso di errore di allocazione

 Ritorna:
    Puntatore a una nuova struttura `utente`, oppure NULL se la malloc fallisce

 Side-effect:
    Alloca memoria dinamicamente per la struttura `utente`
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

 Restituisce il nome memorizzato nella struttura `utente`.

 Implementazione:
    Verifica che il puntatore `utente` non sia NULL e ritorna il campo `nome`.
    Se il puntatore è NULL, ritorna la costante `NULLITEM` (presumibilmente una stringa per indicare valore mancante).

 Parametri:
    ut: puntatore a una struttura `utente`

 Pre-condizioni:
    ut può essere NULL

 Post-condizioni:
    Restituisce il nome utente se `ut` è valido, altrimenti NULLITEM

 Ritorna:
    Puntatore a una stringa contenente il nome utente, oppure NULLITEM se `ut` è NULL

 Side-effect:
    Nessuno
 */
char *prendi_nome(ptr_utente ut)
{
    // Se il puntatore utente è valido, restituisce il nome, altrimenti NULLITEM per indicare assenza.
    return ut ? ut->nome : NULLITEM; 
}


/*
 Funzione: prendi_email
 ----------------------

 Restituisce l'email memorizzata nella struttura `utente`.

 Implementazione:
    Verifica che il puntatore `utente` non sia NULL e ritorna il campo `email`.
    Se il puntatore è NULL, ritorna la costante `NULLITEM` (indica valore mancante).

 Parametri:
    ut: puntatore a una struttura `utente`

 Pre-condizioni:
    ut può essere NULL

 Post-condizioni:
    Restituisce l'email utente se `ut` è valido, altrimenti NULLITEM

 Ritorna:
    Puntatore a una stringa contenente l'email utente, oppure NULLITEM se `ut` è NULL

 Side-effect:
    Nessuno
 */
char *prendi_email(ptr_utente ut)
{
    // Se il puntatore utente è valido, restituisce l'email, altrimenti NULLITEM per indicare assenza.
    return ut ? ut->email : NULLITEM;
}

