#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#define MASSIMO_NOME 50
#define MASSIMO_COGNOME 50
#define MASSIMO_EMAIL 254

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT PRENOTAZIONE
========================================================================

Specifica Sintattica

L’ADT PRENOTAZIONE è definito come un tipo che rappresenta i dati della prenotazioni,
Vengono definiti i seguenti tipi ed operatori:

-------------------------------------------------------------
Tipi: prenotazione
-------------------------------------------------------------
- prenotazione:
  Un record che rappresenta una prenotazione ed è definito come:
  - nome       -> una stringa contenente il nome dell'utente.
  - cognome    -> una stringa contente il cognome dell'utente.
  - email      -> una stringa contente l'email dell'utente.
  - data_inizi -> il timestamp che rappresenta l'inizio del noleggio.
  - data_fine  -> il timestamp che rappresenta la fine del noleggio.
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

1. time_t creazione_data( )
   • Descrizione: Fa inserire all'utente la data, segnando giorno, mese, anno, ora e minuti.
   • Specifica: Restituisce la data che il cliente ha inserito, questa viene calcolata prima in secondi
   dal 1970, poi la trasforma nella corrispettiva data.

2.  float costo_noleggio(int minuti, time_t inizio)
    • Descrizione: Calcola il costo del noleggio secondo le ore utilizzo tenendo conto delle tariffe variabili.
    • Specifica: Restituisce il costo, tenendo conto degli sconti.

3.  void preventivo ( )
    • Descrizione: Mostra all'utente il costo del servizio.
    • Specifica: Restituisce a video il costo calcolato secondo le ore di utilizzo.

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
    • Descrizione: Permette di visualizzare le varie tariffe e permette di proseguire con la prenotazione.
    • Specifica: Restituisce a schermo i diversi costi.

========================================================================
SPECIFICA SEMANTICA

-------------------------------------------------------------
Tipi: time_t, int, float, PRENOTAZIONE
-------------------------------------------------------------

Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:

1.  creazione_data(void) = data
            pre: Nessuna.
            post: Data deve essere valida.

2.  costo_noleggio(minuti, inizio) = prezzo
            pre: 
                -Minuti deve essere maggiore o uguale a 3600 (1 ora).
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

7.    informazioni_costo_noleggio(void) = void
            pre: Nessuna.
            post: Nessuna.
*/

typedef struct{
    char nome[MASSIMO_NOME + 1];
    char cognome[MASSIMO_COGNOME +1];
    char email[MASSIMO_EMAIL + 1];
    time_t inizio;
    time_t fine;
    float costo;
} prenotazione;

time_t creazione_data( );
float costo_noleggio(int minuti, time_t inizio);
void preventivo( );
void stampa_data (time_t data);
void controllo_prenotazione(prenotazione* richiesta);
prenotazione* creazione_prenotazione( );
void informazioni_costo_noleggio( );

#endif