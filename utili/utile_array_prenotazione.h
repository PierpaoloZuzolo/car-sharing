/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

#ifndef UTILE_PRENOTAZIONE_H
#define UTILE_PRENOTAZIONE_H

#include "ADT_array/array_prenotazione.h"


/*
  Funzione: carica_prenotazioni_da_file
  -------------------------------------

  Carica le prenotazioni associate a una determinata targa da un file di testo.
  
  Parametri:
     p: puntatore alla struttura delle prenotazioni da inizializzare
     targa: stringa che identifica la targa dell'auto
     percorso_file: stringa opzionale contenente il percorso del file

  Pre-condizioni:
     p != NULL
     targa != NULL e non vuota

  Post-condizioni:
     se il file non esiste, la struttura prenotazioni è azzerata e viene creato un nuovo file vuoto;
     se il file esiste e la lettura va a buon fine, le prenotazioni vengono caricate correttamente;
     in caso di errori di lettura, le celle rimanenti vengono azzerate.

  Ritorna:
     1 in caso di successo (anche se il file non esiste e viene creato);
     non gestisce casi di errore con valori di ritorno diversi da 1.

  Side-effect:
     può creare un nuovo file se quello specificato non esiste;
     può modificare il contenuto della struttura `p`;
     può leggere da file e allocare risorse temporanee per il nome del file.
 */
int carica_prenotazioni_da_file(ptr_prenotazione p, const char *targa, const char *percorso_file);


/*
  Funzione: salva_prenotazione_su_file
  ------------------------------------

  Salva su file le prenotazioni contenute nella struttura specificata.

  Parametri:
     p: puntatore alla struttura delle prenotazioni da salvare
     targa: stringa che identifica la targa dell'auto
     percorso_file: stringa opzionale contenente il percorso della directory

  Pre-condizioni:
     p != NULL
     targa != NULL e non vuota (strlen(targa) > 0)

  Post-condizioni:
     se il file può essere aperto correttamente, i dati della struttura `p` sono scritti su file;
     se il file non può essere aperto, nessuna operazione viene effettuata.

  Ritorna:
     Nessun valore di ritorno (funzione `void`)

  Side-effect:
     crea o sovrascrive un file nella directory specificata;
     scrive su disco i dati della struttura `p`.
 */
void salva_prenotazione_su_file(ptr_prenotazione p, const char *targa, const char *percorso_file);



/*
 Funzione: veicolo_disponibile_oggi
 ----------------------------------

 Verifica se un veicolo ha almeno una cella oraria libera (non prenotata) nell'arco
 della giornata corrente.

 Parametri:
    p: puntatore alla struttura prenotazione del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido a una struttura prenotazione

 Post-condizioni:
    Nessuna modifica ai dati puntati da p

 Ritorna:
    true se esiste almeno una cella libera (valore 0) nella giornata
    false se tutte le celle sono occupate o p è NULL

 Side-effect:
    Nessuno
*/
bool veicolo_disponibile_oggi(ptr_prenotazione p);



/*
 Funzione: mostra_orari_disponibili
 ----------------------------------

 Stampa a video gli intervalli orari disponibili (liberi) rappresentati
 dalla struttura delle prenotazioni.

 Parametri:
    p: puntatore alla struttura prenotazione

 Pre-condizioni:
    p deve essere un puntatore valido.

 Post-condizioni:
    Vengono stampati su stdout gli intervalli orari liberi presenti nella prenotazione.

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout.
*/
void mostra_orari_disponibili(ptr_prenotazione p);


/*
 Funzione: blocca_celle_passate
 ------------------------------

 Blocca (imposta a 1) tutte le celle corrispondenti agli intervalli orari
 già trascorsi rispetto all’orario corrente, rendendoli indisponibili per prenotazioni.

 Parametri:
    p: puntatore alla struttura prenotazione da aggiornare.

 Pre-condizioni:
    p deve essere un puntatore valido.

 Post-condizioni:
    Le celle degli orari già trascorsi sono impostate a 1 (non prenotabili).

 Ritorna:
    void

 Side-effect:
    Modifica lo stato delle celle nella struttura prenotazione.
*/
void blocca_celle_passate(ptr_prenotazione p);


/*
 Funzione: prenota_intervallo
 ----------------------------

 Prenota un intervallo di celle nell'array prenotazioni.

 Parametri:
    p           - puntatore alla struttura prenotazioni
    inizio_cella- indice di inizio intervallo (inclusivo)
    fine_cella  - indice di fine intervallo (esclusivo)

 Pre-condizioni:
    p valido
    inizio_cella e fine_cella validi e inizio_cella < fine_cella

 Post-condizioni:
    Celle nell'intervallo prenotate

 Ritorna:
    1 se prenotazione riuscita, 0 altrimenti

 Side-effect:
    Modifica celle nell'array prenotazioni
*/
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

/*
 Funzione: libera_intervallo
 ---------------------------

 Libera un intervallo di celle nell'array prenotazioni.

 Parametri:
    p           - puntatore alla struttura prenotazioni
    inizio_cella- indice di inizio intervallo (inclusivo)
    fine_cella  - indice di fine intervallo (esclusivo)

 Pre-condizioni:
    p valido
    inizio_cella e fine_cella validi e inizio_cella < fine_cella

 Post-condizioni:
    Celle nell'intervallo liberate (impostate a NULL)

 Ritorna:
    1 se liberazione riuscita, 0 altrimenti

 Side-effect:
    Modifica celle nell'array prenotazioni
*/
int libera_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella);

#endif