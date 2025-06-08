#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utente.h"
#include "hash_utenti.h"
#include "utile_utente.h"
#include "tab_hash.h"





/*
 Funzione: crea_hash_utenti
 --------------------------

 Crea una nuova tabella hash specificamente per la gestione degli utenti.

 Implementazione:
    Chiama la funzione `crea_tabella_hash` passando la dimensione desiderata.

 Parametri:
    dimensione: numero di bucket da allocare nella tabella hash

 Pre-condizioni:
    dimensione deve essere maggiore di 0

 Post-condizioni:
    restituisce un puntatore a una nuova tabella hash per utenti, oppure NULL in caso di errore

 Ritorna:
    un puntatore a una struttura `ptr_hash_utenti`, o NULL se la creazione fallisce

 Side-effect:
    alloca memoria dinamicamente per la nuova tabella hash
 */


ptr_hash_utenti crea_hash_utenti(int dimensione)
{
  return crea_tabella_hash(dimensione);
}

/*
 Funzione: libera_utente_hash
 ----------------------------

 Funzione ausiliaria per liberare correttamente la memoria associata a un utente,
 da usare come callback nei processi di distruzione della tabella hash.

 Implementazione:
    Converte il puntatore generico `void *` in un `ptr_utente`,
    quindi chiama la funzione `libera_utente` per deallocare la memoria dell'utente.

 Parametri:
    utente: puntatore generico a un utente da liberare

 Pre-condizioni:
    utente deve essere non NULL e puntare a una struttura `utente` valida

 Post-condizioni:
    la memoria associata all'utente viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata all'utente
 */


static void libera_utente_hash(void *utente)
{
  ptr_utente ut = (ptr_utente)utente;
  libera_utente(ut);
}

/*
 Funzione: distruggi_hash_utenti

 Distrugge una tabella hash contenente utenti, liberando tutta la memoria associata.

 Implementazione:
    Verifica che il puntatore alla tabella hash sia valido.
    Se lo è, chiama `distruggi_hash` passando la funzione `libera_utente_hash` 
    per liberare correttamente ogni valore (utente) memorizzato.

 Parametri:
    h: puntatore alla tabella hash di utenti

 Pre-condizioni:
    h può essere NULL; se non lo è, deve essere una tabella hash valida creata con `crea_hash_utenti`

 Post-condizioni:
    la memoria associata alla tabella hash e agli utenti viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata alla tabella hash e agli utenti
 */


void distruggi_hash_utenti(ptr_hash_utenti h)
{
  if(h){
    distruggi_hash(h, libera_utente_hash);
  }
}

/*
 Funzione: inserisci_utente_in_hash
 ----------------------------------

 Inserisce un utente nella tabella hash usando il nome come chiave.

 Implementazione:
    Verifica che la tabella hash e l'utente siano non NULL.
    Recupera il nome dell'utente con `prendi_nome`.
    Se il nome è valido, chiama `inserisci_in_hash` per inserire nella tabella la coppia chiave-valore
    dove la chiave è il nome e il valore è il puntatore all'utente.

 Parametri:
    h: puntatore alla tabella hash degli utenti
    ut: puntatore all'utente da inserire

 Pre-condizioni:
    h deve essere una tabella hash valida
    ut deve essere un utente valido
    il nome restituito da `prendi_nome(ut)` deve essere non NULL

 Post-condizioni:
    se la funzione ha successo, l'utente è inserito nella tabella hash
    altrimenti la tabella non viene modificata

 Ritorna:
    true se l'inserimento è andato a buon fine,
    false in caso di errore (puntatori NULL, nome NULL o duplicato)

 Side-effect:
    può allocare memoria internamente tramite `inserisci_in_hash`
 */


bool inserisci_utente_in_hash(ptr_hash_utenti h, ptr_utente ut)
{
  if(h && ut){
    char *nome = prendi_nome(ut);
    if (nome){
       return inserisci_in_hash(h, nome, (ptr_utente)ut);
    }
   
  }
  return false;
}

/*
 Funzione: cerca_utente_in_hash
 ------------------------------

 Cerca un utente nella tabella hash dato il nome.

 Implementazione:
    Verifica che la tabella hash sia non NULL.
    Usa la funzione `cerca_in_hash` passando il nome come chiave.
    Se l'utente viene trovato, ne restituisce il puntatore, altrimenti NULL.

 Parametri:
    h: puntatore alla tabella hash degli utenti
    nome: stringa che rappresenta il nome dell'utente da cercare

 Pre-condizioni:
    h deve essere una tabella hash valida
    nome deve essere una stringa non NULL terminata da '\0'

 Post-condizioni:
    nessuna modifica alla tabella hash

 Ritorna:
    un puntatore all'utente se trovato,
    NULL se la tabella è NULL o l'utente non è presente

 Side-effect:
    nessuno
 */


ptr_utente cerca_utente_in_hash(ptr_hash_utenti h, const char* nome)
{
  if(h){
    return (ptr_utente)cerca_in_hash(h, nome);
  }

  return NULL;
}


