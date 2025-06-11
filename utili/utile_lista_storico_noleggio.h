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
 Funzione: inserisci_nodo_storico_noleggio
 -----------------------------------------

 Inserisce un nuovo nodo nella lista dello storico noleggi rispettando la
 distinzione tra nodi eliminabili e non eliminabili.

 Parametri:
    lista: puntatore alla lista dei noleggi
    prenotazione: puntatore allo storico noleggio da inserire nella lista

 Pre-condizioni:
    `lista` e `prenotazione` devono essere puntatori validi e non NULL.

 Post-condizioni:
    Il nodo viene inserito nella lista in posizione corretta,
    la coda viene aggiornata se necessario.

 Ritorna:
    void

 Side-effect:
    Modifica la lista collegata e può aggiornare la coda.
 */
void inserisci_nodo_storico_noleggio(ptr_lista_noleggi lista, ptr_storico prenotazione);

/*
 Funzione: elimina_nodo_storico_noleggio
 ---------------------------------------

 Permette di eliminare un nodo dalla lista dei noleggi storici, scegliendo tra
 i nodi eliminabili (tutti se la coda è NULL, oppure solo quelli successivi alla coda).

 Parametri:
    lista                  : puntatore alla lista dei noleggi storici
    targa_veicolo_eliminato: array di char dove verrà copiata la targa del veicolo eliminato (dimensione minima 8)
    ora_inizio             : puntatore a int per memorizzare l’ora di inizio del noleggio eliminato
    minuto_inizio          : puntatore a int per memorizzare il minuto di inizio
    ora_fine               : puntatore a int per memorizzare l’ora di fine
    minuto_fine            : puntatore a int per memorizzare il minuto di fine

 Pre-condizioni:
    lista deve essere valida e non vuota
    puntatori per copia dati devono essere validi

 Post-condizioni:
    nodo scelto viene eliminato dalla lista e memoria liberata
    dati della prenotazione eliminata copiati nei parametri passati

 Ritorna:
    1 se l’eliminazione è avvenuta con successo
    0 in caso di errore, input non valido o annullamento

 Side-effect:
    stampa messaggi su stdout
    modifica la lista e libera la memoria del nodo eliminato
*/
int elimina_nodo_storico_noleggio(ptr_lista_noleggi lista, char *targa_veicolo_eliminato, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine);


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