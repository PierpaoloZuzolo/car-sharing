/*
Autore: Roberto Saporoso
Data: 12/05/2025
*/

#ifndef UTENTE_H
#define UTENTE_H

#define NULLITEM NULL

/*
 Tipo astratto di dato: utente
 -----------------------------
 Rappresenta un utente con nome ed email.
*/
typedef struct utente *ptr_utente;

#include "ADT_hash/hash_utenti.h"


/*
 Funzione: inizia_utente
 -----------------------

 Crea e inizializza una nuova struttura `utente` con nome ed email forniti.

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
ptr_utente inizia_utente(const char *nome, const char *email);


/*
 Funzione: prendi_nome
 ---------------------

 Restituisce il nome memorizzato nella struttura `utente`.

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
char *prendi_nome(ptr_utente ut);


/*
 Funzione: prendi_email
 ----------------------

 Restituisce l'email memorizzata nella struttura `utente`.

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
char *prendi_email(ptr_utente ut);


#endif
