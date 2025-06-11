#ifndef INTERFACCIA_UTENTE_H
#define INTERFACCIA_UTENTE_H

#include "ADT_hash/hash_utenti.h"
#include "Modello_utente/utente.h"
#include "ADT_hash/hash_veicoli.h"
#include "Modello_veicolo/veicolo.h"

/*
 Funzione: gestione_utente
 --------------------------

 Gestisce la logica di registrazione e login degli utenti.
 Carica gli utenti esistenti da file e permette la selezione tra:
    - Registrazione di un nuovo utente.
    - Login di un utente esistente.

 Parametri:
    h - puntatore alla tabella hash contenente gli utenti (ptr_hash_utenti)

 Pre-condizioni:
    - h deve essere una struttura hash valida e inizializzata.
    - Deve esistere il file "txt/Utenti/utenti.txt" per la lettura/scrittura.

 Post-condizioni:
    - Restituisce un puntatore a un utente valido (registrato o loggato), oppure termina il programma in caso di uscita.

 Ritorna:
    - Puntatore a una struttura `ptr_utente` contenente l'utente loggato o registrato.

 Side-effect:
    - Input/output su console.
    - Lettura e scrittura su file per la persistenza degli utenti.
    - Possibile terminazione del programma con `exit()` in caso di uscita o errori gravi.
*/
ptr_utente gestione_utente(ptr_hash_utenti h);

/*
 Funzione: avvia_menu_principale
 --------------------------------

 Gestisce il menu principale dell'applicazione per un utente autenticato.
 Permette:
    - Prenotare veicoli.
    - Consultare ed eventualmente modificare lo storico delle prenotazioni.
    - Terminare il programma.

 Parametri:
    utente       - puntatore all'utente attualmente loggato
    hash_veicoli - puntatore alla tabella hash contenente tutti i veicoli

 Pre-condizioni:
    - utente deve essere un puntatore valido e non NULL.
    - hash_veicoli deve essere una tabella hash valida e inizializzata.

 Post-condizioni:
    - Tutte le operazioni effettuate possono aggiornare file e strutture dati.
    - Termina solo su esplicita richiesta dell’utente (scelta 0).

 Ritorna:
    Nessun valore di ritorno (void).

 Side-effect:
    - Input/output su console.
    - Lettura e scrittura su file.
    - Modifica delle strutture di prenotazione e storico noleggi.
*/
void avvia_menu_principale(ptr_utente utente, ptr_hash_veicoli hash_veicoli);


/*
 Funzione: menu_prenotazione
 ---------------------------

 Gestisce il menu interattivo di prenotazione veicolo per l'utente.

 Parametri:
    hash_veicoli - puntatore alla tabella hash contenente i veicoli disponibili
    nome_utente  - stringa contenente il nome dell'utente che effettua la prenotazione

 Pre-condizioni:
    hash_veicoli valido e inizializzato
    nome_utente valido (non NULL)

 Post-condizioni:
    Se l'utente conferma la prenotazione:
        - aggiorna le prenotazioni del veicolo
        - aggiorna i file relativi alle prenotazioni e allo storico
    Se l'utente annulla:
        - nessuna modifica persistente viene effettuata

 Ritorna:
    ptr_veicolo - puntatore al veicolo prenotato se la prenotazione ha successo,
                  NULL se l'utente annulla o se la prenotazione fallisce

 Side-effect:
    - Modifica lo stato delle prenotazioni del veicolo selezionato
    - Scrive su file per aggiornare prenotazioni e storico noleggi
    - Input/output su console
*/
ptr_veicolo menu_prenotazione(ptr_hash_veicoli hash_veicoli, char *nome_utente);

/*
 Funzione: gestione_storico_prenotazioni
 ---------------------------------------

 Permette all'utente di visualizzare e gestire lo storico delle prenotazioni effettuate.
 Consente anche di eliminare una prenotazione precedente, aggiornando sia lo storico che
 lo stato di prenotazione del veicolo corrispondente.

 Parametri:
    nome_utente   - puntatore a stringa contenente il nome utente (identifica il file dello storico)
    hash_veicoli  - puntatore alla tabella hash contenente tutti i veicoli

 Pre-condizioni:
    - nome_utente deve essere un puntatore valido e non NULL
    - hash_veicoli deve essere una struttura hash valida e inizializzata

 Post-condizioni:
    - Se effettuata l’eliminazione, i dati vengono aggiornati su file e in memoria
    - Se nessuna eliminazione, nessuna modifica persistente avviene

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    - Input/output su console
    - Modifica file su disco per storico noleggi e prenotazioni veicoli
    - Modifica la struttura di prenotazioni in memoria per i veicoli

*/
void gestione_storico_prenotazioni(char *nome_utente, ptr_hash_veicoli hash_veicoli);

#endif
