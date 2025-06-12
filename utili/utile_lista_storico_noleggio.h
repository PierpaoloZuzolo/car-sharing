/*
Autore: Carmine Saporoso, Pierpaolo Zuzolo
Data: 07/06/2025
*/

#ifndef UTILE_LISTA_STORICO_PRENOTAZIONI_H
#define UTILE_LISTA_STORICO_PRENOTAZIONI_H

#include <stdbool.h>

#include "Modello_storico_noleggio/storico_noleggio.h"
#include "ADT_lista/lista_storico_noleggio.h"
#include "ADT_lista/lista.h"


/*
  Funzione: vedi_se_noleggio_eliminabile
  --------------------------------------

  Verifica se una prenotazione (noleggio) è eliminabile in base alla data e all'orario attuale.

  Parametri:
     s: puntatore a una struttura ptr_storico contenente i dati della prenotazione

  Pre-condizioni:
     s può essere NULL

  Post-condizioni:
     Se s è NULL o la prenotazione inizia tra meno di 60 minuti, viene restituito 0;
     altrimenti viene restituito 1.

  Ritorna:
     1 se la prenotazione è eliminabile (è oggi e mancano almeno 60 minuti all'inizio)
     0 se la prenotazione non è eliminabile (non è oggi o mancano meno di 60 minuti)

  Side-effect:
     Nessuno
 */
int vedi_se_noleggio_eliminabile(ptr_storico s);


/*
 Funzione: dimensione_lista
 --------------------------

 Calcola il numero totale di nodi presenti nella lista dei noleggi.

 Parametri:
    l: puntatore alla lista dei noleggi

 Pre-condizioni:
    `l` deve essere un puntatore valido a una struttura lista.
    Tuttavia, la funzione gestisce anche il caso in cui `l` sia NULL o vuota.

 Post-condizioni:
    Nessuna modifica alla lista.

 Ritorna:
    Un intero rappresentante il numero di nodi presenti nella lista.
    Restituisce 0 se la lista è NULL o se non ha nodi.

 Side-effect:
    Nessuno.
 */

int dimensione_lista(ptr_lista_noleggi l);

/*
  Funzione: inserisci_nodo_storico_noleggio
  -----------------------------------------

  Inserisce una nuova prenotazione nella lista dei noleggi storici, tenendo conto 
  del flag `eliminabile` per gestire correttamente la posizione del nodo e il 
  puntatore alla "coda" (ultimo nodo non eliminabile).

  Parametri:
     lista: puntatore alla lista dei noleggi storici
     prenotazione: puntatore alla struttura ptr_storico che rappresenta la prenotazione da inserire
     eliminabile: intero (booleano) che indica se la prenotazione può essere eliminata (1 = sì, 0 = no)

  Pre-condizioni:
     - `lista` deve essere un puntatore valido a una lista inizializzata (non NULL)
     - `prenotazione` deve essere un puntatore valido a una struttura `ptr_storico`
     - `eliminabile` deve essere 0 o 1

  Post-condizioni:
     - La prenotazione viene inserita nella lista secondo le regole di priorità dei nodi non eliminabili
     - Se la prenotazione non è eliminabile, viene mantenuta una traccia (aggiornando il puntatore alla coda)

  Ritorna:
     Nessun valore (funzione `void`)

  Side-effect:
     - Modifica la struttura della lista dei noleggi storici
     - Può aggiornare il puntatore alla "coda" della lista
     - Alloca memoria dinamica per un nuovo nodo
 */
void inserisci_nodo_storico_noleggio(ptr_lista_noleggi lista, ptr_storico prenotazione, int eliminabile);

/*
 Funzione: elimina_nodo_storico_noleggio
 ---------------------------------------

 Elimina un nodo specifico dalla lista dello storico noleggi, identificato
 tramite una scelta numerica (1-based), e restituisce i dettagli del noleggio
 eliminato attraverso parametri di output.

 Parametri:
    lista: puntatore alla lista dei noleggi
    targa_veicolo_eliminato: stringa dove viene salvata la targa del veicolo eliminato (lunghezza minima 8)
    ora_inizio, minuto_inizio: puntatori per salvare l'orario di inizio del noleggio eliminato
    ora_fine, minuto_fine: puntatori per salvare l'orario di fine del noleggio eliminato
    scelta: posizione (1-based) del nodo da eliminare

 Pre-condizioni:
    - `lista` deve essere un puntatore valido e inizializzato.
    - `targa_veicolo_eliminato`, `ora_inizio`, `minuto_inizio`, `ora_fine`, `minuto_fine` devono essere puntatori validi.
    - `scelta` deve essere maggiore di 0 e non superiore alla dimensione della lista nella parte eliminabile.

 Post-condizioni:
    - Il nodo selezionato viene rimosso dalla lista.
    - I dati della prenotazione eliminata vengono copiati nei parametri di output.

 Ritorna:
    1 se la rimozione è avvenuta con successo,
    0 in caso di errore (lista vuota, indice non valido o nodo non trovato).

 Side-effect:
    Modifica la lista dei noleggi, deallocando la memoria del nodo rimosso.
 */

int elimina_nodo_storico_noleggio(ptr_lista_noleggi lista, char *targa_veicolo_eliminato, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine, int scelta);


/*
  Funzione: salva_lista_storico_noleggio_su_file
  ----------------------------------------------

  Salva su file lo storico dei noleggi associato a un determinato utente.

  Parametri:
     lista: puntatore alla lista contenente i record dello storico noleggi
     nome_utente: stringa identificativa dell'utente
     percorso_cartella: stringa opzionale contenente il percorso in cui salvare il file

  Pre-condizioni:
     lista != NULL
     nome_utente != NULL e non vuota (strlen(nome_utente) > 0)

  Post-condizioni:
     se il file può essere aperto, il contenuto della lista viene salvato nel file specificato;
     ogni elemento della lista viene scritto su una riga in formato CSV;
     se il file non può essere aperto, viene stampato un messaggio di errore e non viene scritto nulla.

  Ritorna:
     Nessun valore di ritorno (funzione `void`)

  Side-effect:
     crea o sovrascrive un file con nome basato sull’utente;
     scrive su file i dati della lista di noleggi;
     stampa messaggi di errore in caso di parametri invalidi o problemi di apertura file.
 */
void salva_lista_storico_noleggio_su_file(ptr_lista_noleggi lista, const char *nome_utente, const char *percorso_cartella);

/*
  Funzione: carica_lista_storico_noleggio_da_file
  -----------------------------------------------

  Carica da file lo storico dei noleggi relativi a un determinato utente e li inserisce nella lista fornita.

  Parametri:
     lista: puntatore alla lista in cui caricare gli elementi dello storico
     nome_utente: stringa che identifica l'utente
     percorso_file: stringa opzionale che specifica il percorso della cartella dei file

  Pre-condizioni:
     lista != NULL
     nome_utente != NULL

  Post-condizioni:
     se il file esiste ed è valido, gli elementi vengono letti e inseriti nella lista;
     se il file non esiste, la lista rimane invariata;
     eventuali righe non leggibili o incomplete vengono ignorate.

  Ritorna:
     1 se la lettura ha avuto successo e almeno una riga è stata gestita correttamente;
     2 se il file non esiste (non è considerato un errore critico);
     0 in caso di parametri non validi (lista o nome utente NULL)

  Side-effect:
     apre e legge da un file su disco;
     può modificare il contenuto della lista passata come parametro;
     alloca memoria dinamica per ogni record storico inserito nella lista.
 */
int carica_lista_storico_noleggio_da_file(ptr_lista_noleggi lista, char *nome_utente, const char *percorso_file);


/*
  Funzione: aggiungi_prenotazione_storico_su_file
  -----------------------------------------------

  Aggiunge una nuova voce di prenotazione allo storico dei noleggi dell’utente, salvandola su file in formato CSV.

  Parametri:
     targa: stringa contenente la targa del veicolo noleggiato
     tipo_veicolo: stringa che identifica la tipologia del veicolo
     nome_utente: stringa che rappresenta l'utente che ha effettuato il noleggio
     ora_inizio: ora di inizio del noleggio
     minuto_inizio: minuti di inizio del noleggio
     ora_fine: ora di fine del noleggio
     minuto_fine: minuti di fine del noleggio
     costo: costo del noleggio (valore float con 2 decimali)
     percorso_file: percorso opzionale della cartella dove salvare il file

  Pre-condizioni:
     targa, tipo_veicolo e nome_utente devono essere stringhe non NULL

  Post-condizioni:
     se il file è accessibile, una nuova riga con i dati della prenotazione viene aggiunta al file;
     altrimenti, nessun dato viene scritto e viene restituito 0.

  Ritorna:
     1 se l’operazione è andata a buon fine;
     0 se si è verificato un errore (es. parametri non validi o apertura file fallita)

  Side-effect:
     apre e scrive su un file su disco in modalità append;
     ottiene la data e ora correnti tramite funzioni di sistema.
 */
void aggiungi_prenotazione_storico_su_file(const char *targa, const char *tipo_veicolo, const char *nome_utente, int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, float costo, const char *percorso_file);

/*
 Funzione: stampa_lista_noleggi
 ------------------------------

 Stampa a video l'intero contenuto della lista dei noleggi storici.

 Parametri:
    l: puntatore alla lista dei noleggi storici da stampare

 Pre-condizioni:
    l deve essere un puntatore valido o NULL.
    La lista deve contenere nodi validi.

 Post-condizioni:
    Viene stampata la lista dei noleggi a video.

 Ritorna:
    Il numero di elementi stampati più 1 (indice di fine lista),
    oppure 0 se la lista è vuota o nulla.

 Side-effect:
    Effettua stampe su stdout.
 */
int stampa_lista_noleggi(ptr_lista_noleggi l);

/*
 Funzione: stampa_dopo_coda
 --------------------------

 Stampa a video gli elementi della lista dei noleggi storici a partire dal nodo successivo
 al nodo puntato come "coda".

 Parametri:
    l: puntatore alla lista dei noleggi storici

 Pre-condizioni:
    l deve essere un puntatore valido.
    La lista deve avere un puntatore coda valido.

 Post-condizioni:
    Viene stampata la porzione di lista che segue la coda.

 Ritorna:
    Il numero di elementi stampati più 1 (indice di fine lista),
    oppure 0 se non ci sono nodi dopo la coda o se input non valido.

 Side-effect:
    Effettua stampe su stdout.
 */
int stampa_dopo_coda(ptr_lista_noleggi l);


/*
 Funzione: conta_fino_a_coda
 ---------------------------

 Conta il numero di elementi nella lista dei noleggi, partendo dalla testa fino ad arrivare alla coda inclusa.


 Parametri:
    l: puntatore a una lista di noleggi (ptr_lista_noleggi)

 Pre-condizioni:
    l deve essere un puntatore valido a una lista non vuota, con testa e coda correttamente impostate.

 Post-condizioni:
    Nessuna modifica alla lista originale.

 Ritorna:
    Un intero che rappresenta il numero di elementi dalla testa alla coda inclusa.
    Se la coda non è raggiungibile dalla testa, restituisce 0.

 Side-effect:
    Nessuno.
*/

int conta_fino_a_coda(ptr_lista_noleggi l);





#endif