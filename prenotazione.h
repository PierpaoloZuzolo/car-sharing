#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#define MASSIMO_NOME 50
#define MASSIMO_COGNOME 50
#define MASSIMO_EMAIL 254

typedef struct prenotazione* ptrprenotazione;

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT PRENOTAZIONE
========================================================================

Specifica Sintattica

L’ADT PRENOTAZIONE è definito come un tipo opaco che rappresenta i dati della prenotazioni,
Vengono definiti i seguenti tipi ed operatori:

-------------------------------------------------------------
Tipi: prenotazione, ptrprenotazione
-------------------------------------------------------------
- prenotazione:
  Un record che rappresenta una prenotazione ed è definito come:
  - nome       -> una stringa contenente il nome dell'utente.
  - cognome    -> una stringa contente il cognome dell'utente.
  - email      -> una stringa contente l'email dell'utente.
  - inizio     -> il marcatore temporale che rappresenta l'inizio del noleggio.
  - fine       -> il marcatore temporale che rappresenta la fine del noleggio.
  - costo      -> il costo associato alla prenotazione.

-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- creazione_data              : ( ) → TIME_T
- costo_noleggio              : (INT, TIME_T) → FLOAT
- preventivo                  : ( ) →  VOID
- stampa_data                 : (TIME_T) → VOID
- controllo_prenotazione      : (PRENOTAZIONE) → VOID
- creazione_prenotazione      : (   ) → PRENOTAZIONE
- informazioni_costo_noleggio : (INT, TIME_T) → VOID

1. time_t creazione_data ( )
   • Descrizione: Fa inserire all'utente la data, segnando giorno, mese e anno.
   • Specifica: Restituisce la data che il cliente ha inserito, questa viene calcolata prima in secondi
    dal 1900, poi la trasforma nella corrispettiva data.

2.  float costo_noleggio (int giorno, time_t inizio)
    • Descrizione: Calcola il costo del noleggio secondo i giorni tenendo conto delle tariffe variabili.
    • Specifica: Restituisce il costo, tenendo conto dei prezzi.

3.  void preventivo ( )
    • Descrizione: Mostra all'utente il costo del servizio.
    • Specifica: Restituisce a video il costo calcolato secondo i giorni di utilizzo.

4.  void stampa_data (time_t data)
    • Descrizione: Mostra a schermo la data passata in input, seguendo il formato (gg/mese/anno h:min).
    • Specifica: Restituisce a schermo la data.

5.  void controllo_prenotazione (prenotazione* richiesta) 
    • Descrizione: Mostra a schermo i dati inseriti per compilare la prenotazione.
    • Specifica: Restituisce a schermo i dati della prenotazione, affichè l'utente possa visionarli.

6.  prenotazione* creazione_prenotazione ( ) 
    • Descrizione: Chiede all'utente i dati da inserire per completare la prenotazione.
    • Specifica: Restituisce una prenotazione con i campi compilati dall'utente.

7.  void informazioni_costo_noleggio( ) 
    • Descrizione: Permette di visualizzare le varie tariffe.
    • Specifica: Restituisce a schermo i diversi costi.

========================================================================
SPECIFICA SEMANTICA

-------------------------------------------------------------
Tipi: TIME_T, INT, FLOAT, PRENOTAZIONE
-------------------------------------------------------------

Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:

1.  creazione_data(void) = data
            pre: Nessuna.
            post: Data deve essere valida.

2.  costo_noleggio(giorno, inizio) = prezzo
            pre: 
                -Giorno deve essere maggiore o uguale a 86400 secondi (1 giorno).
                -Inizio deve essere una data valida.
            post: Nessuna.

3.  preventivo (void) = void
            pre: Nessuna.
            post: Nessuna.

4.  stampa_data (data) = void
            pre: Data deve essere valida.
            post: Nessuna.

5.  controllo_prenotazione (richiesta) = void
            pre: Richiesta deve essere valida.
            post: Nessuna.

6.  creazione_prenotazione ( ) = nuova_prenotazione
            pre: Nessuna.
            post: Nuova_prenotazione deve essere valida.

7.  informazioni_costo_noleggio(void) = void
            pre: Nessuna.
            post: Nessuna.
*/

time_t creazione_data( );
float costo_noleggio(int minuti, time_t inizio);
void stampa_data(time_t data);
void controllo_prenotazione(ptrprenotazione richiesta);
void informazioni_costo_noleggio( );
void preventivo( );
ptrprenotazione creazione_prenotazione( );
time_t prendi_data_inizio(ptrprenotazione richiesta);

#endif