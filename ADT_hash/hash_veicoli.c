/*
Autore: Roberto Saporoso, Carmine Saporoso
Data: 07/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tab_hash.h"
#include "Modello_veicolo/veicolo.h"
#include "hash_veicoli.h"
#include "utili/utile_veicolo.h"


/*
 Funzione: crea_hash_veicoli
 ---------------------------

 Crea una nuova tabella hash specificamente per la gestione dei veicoli.

 Implementazione:
    Chiama la funzione `crea_tabella_hash` passando la dimensione desiderata.

 Parametri:
    dimensione: numero di bucket da allocare nella tabella hash

 Pre-condizioni:
    dimensione deve essere maggiore di 0

 Post-condizioni:
    restituisce un puntatore a una nuova tabella hash per veicoli, oppure NULL in caso di errore

 Ritorna:
    un puntatore a una struttura `ptr_hash_veicoli`, o NULL se la creazione fallisce

 Side-effect:
    alloca memoria dinamicamente per la nuova tabella hash
 */
ptr_hash_veicoli crea_hash_veicoli(int dimensione)
{
    return crea_tabella_hash(dimensione);
}

/*
 Funzione: libera_veicolo_hash
 -----------------------------

 Funzione ausiliaria per liberare correttamente la memoria associata a un veicolo,
 da usare come callback nei processi di distruzione della tabella hash.

 Implementazione:
    Converte il puntatore generico `void *` in un `ptr_veicolo`,
    quindi chiama la funzione `libera_veicolo` per deallocare la memoria del veicolo.

 Parametri:
    veicolo: puntatore generico a un veicolo da liberare

 Pre-condizioni:
    veicolo deve essere non NULL e puntare a una struttura `veicolo` valida

 Post-condizioni:
    la memoria associata al veicolo viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata al veicolo
 */
static void libera_veicolo_hash(void *veicolo)
{
    ptr_veicolo ve = (ptr_veicolo)veicolo;
    libera_veicolo(ve);
}

/*
 Funzione: distruggi_hash_veicoli
 --------------------------------

 Distrugge una tabella hash contenente veicoli, liberando tutta la memoria associata.

 Implementazione:
    Verifica che il puntatore alla tabella hash sia valido.
    Se lo è, chiama `distruggi_hash` passando la funzione `libera_veicolo_hash` 
    per liberare correttamente ogni valore (veicolo) memorizzato.

 Parametri:
    h: puntatore alla tabella hash di veicoli

 Pre-condizioni:
    h può essere NULL; se non lo è, deve essere una tabella hash valida creata con `crea_hash_veicoli`

 Post-condizioni:
    la memoria associata alla tabella hash e ai veicoli viene deallocata

 Ritorna:
    niente (void)

 Side-effect:
    dealloca memoria dinamicamente associata alla tabella hash e ai veicoli
 */
void distruggi_hash_veicoli(ptr_hash_veicoli h)
{
    if(h){
        distruggi_hash(h, libera_veicolo_hash);
    }
}

/*
 Funzione: inserisci_veicolo_in_hash
 -----------------------------------

 Inserisce un veicolo nella tabella hash usando la targa come chiave.

 Implementazione:
    Verifica che la tabella hash e il veicolo siano non NULL.
    Recupera la targa del veicolo con `prendi_targa`.
    Se la targa è valida, chiama `inserisci_in_hash` per inserire nella tabella la coppia chiave-valore
    dove la chiave è la targa e il valore è il puntatore al veicolo.

 Parametri:
    h: puntatore alla tabella hash dei veicoli
    ve: puntatore al veicolo da inserire

 Pre-condizioni:
    h deve essere una tabella hash valida
    ve deve essere un veicolo valido
    la targa restituita da `prendi_targa(ve)` deve essere non NULL

 Post-condizioni:
    se la funzione ha successo, il veicolo è inserito nella tabella hash
    altrimenti la tabella non viene modificata

 Ritorna:
    true se l'inserimento è andato a buon fine,
    false in caso di errore (puntatori NULL, targa NULL o duplicato)

 Side-effect:
    può allocare memoria internamente tramite `inserisci_in_hash`
 */
bool inserisci_veicolo_in_hash(ptr_hash_veicoli h, ptr_veicolo ve)
{
  if(h && ve){
    char *nome = prendi_targa(ve);
    if (nome){
       return inserisci_in_hash(h, nome, (ptr_veicolo)ve);
    }
   
  }

  return false;
}

/*
 Funzione: cerca_veicolo_in_hash
 -------------------------------

 Cerca un veicolo nella tabella hash dato il numero di targa.

 Implementazione:
    Verifica che la tabella hash sia non NULL.
    Usa la funzione `cerca_in_hash` passando la targa come chiave.
    Se il veicolo viene trovato, ne restituisce il puntatore, altrimenti NULL.

 Parametri:
    h: puntatore alla tabella hash dei veicoli
    targa: stringa che rappresenta la targa del veicolo da cercare

 Pre-condizioni:
    h deve essere una tabella hash valida
    targa deve essere una stringa non NULL terminata da '\0'

 Post-condizioni:
    nessuna modifica alla tabella hash

 Ritorna:
    un puntatore al veicolo se trovato,
    NULL se la tabella è NULL o il veicolo non è presente

 Side-effect:
    nessuno
 */
ptr_veicolo cerca_veicolo_in_hash(ptr_hash_veicoli h, const char *targa)
{
    if(h){
        return (ptr_veicolo)cerca_in_hash(h, targa);
    }

    return NULL;
}



