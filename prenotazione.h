#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

/*SPECIFICA SINTATTICA

TIPI: PRENOTAZIONE,TIME_T

OPERATORI:

- creazione_data              : ( ) → time_t
- giorni_festivi              : (struct tm*) → int
- orario_sconto               : (struct tm*) → int
- costo_noleggio              : (int, time_t) → float
- informazioni_costo_noleggio : (int, time_t) → void
- stampa_data                 : (time_t) → void
- controllo_prenotazione      : (PRENOTAZIONE) → void

creazione_data:
• Sintassi: creazione_data : ( ) → time_t
• Descrizione: Chiede la data da inserire all'utente. Se l'utente non inserisce una data valida, il comportamento può generare un errore

giorni_festivi:
• Sintassi: giorni_festivi : (struct tm*) → int
• Descrizione: Confornta la data data in input con un elenco di giorni festivi italiani prestabilito

orario_sconto:
• Sintassi: orario_sconto : (struct tm*) → int
• Descrizione: Confronta l' orario dato in input con un elenco di orari in cui c'è lo sconto

costo_noleggio:
• Sintassi: costo_noleggio : (int, time_t) → float
• Descrizione: Restituisce il costo del noleggio, calcolato in base alle ore di utilizzo e considerando eventuali sconti per festività 
o orari particolari. 
Il prezzo può variare a seconda dell'auto, avendo così dei moltiplicatore a seconda della fascia attribuita dall'admin.

informazioni_costo_noleggio:
• Sintassi: informazioni_costo_noleggio : (int, time_t) → void
• Descrizione: Illustra i costi che possono variare a seconda di giorni festivi e orari particolari. Il cliente può decidere 
se procedere con la prenotazione in base a queste informazioni.

stampa_data :
• Sintassi: stampa_data : (time_t) → void
• Descrizione: Stampa la data passata in input 

controllo_prenotazione:
• Sintassi: controllo_prenotazione : (PRENOTAZIONE) → void
• Descrizione: Stampa i dettagli della prenotazione, consentendo all'utente di verificare se i dati sono stati correttamente inseriti. 
Se la prenotazione è corretta, può proseguire con la prenotazione del veicolo.



SPECIFICA SEMANTICA

TIPI:

PRENOTAZIONE = {prenotazione}
prenotazione è una struttura con i seguenti campi:
    - nome: una stringa contenente il nome dell'utente
    - cognome: una stringa contente il cognome dell'utente
    - email: una stringa contente l'email dell'utente
    - data_inizio: il timestamp che rappresenta l'inizio del noleggio
    - data_fine: il timestamp che rappresenta la fine del noleggio
    - costo: il costo associato alla prenotazione


time_t = tipo per rappresentare il tempo

OPERATORI:

creazione_data( ) = time_t
    pre: nessuna
    post: restituisce un valore di tipo time_t che rappresenta la data di inizio e fine del noleggio.


giorni_festivi(tm_attuale) = R
    pre: tm_attuale deve essere una struttura tm valida
    post: se la data fornita coincide con un giorno festivo italiano, il valore restituito R è 1 (vero), altrimenti 0 (falso).


orario_sconto(tm_attuale) = R
    -pre: tm_attuale deve essere una struttura tm valida
    -post: se la data e l'orario forniti rientrano in un intervallo di orario sconto predefinito, restituito R è 1 (vero), altrimenti 0 (falso).

costo_noleggio(ora_utilizzo, inizio) = float
    -pre:
    -ora_utilizzo: l'ora inserita deve essere maggiore o uguale a 1 e deve essere un numero intero.
    -inizio: è il timestamp che rappresenta l'inizio del noleggio.
    -post: nessuna


informazioni_costo_noleggio(ora_utilizzo, inizio) = void
    -pre:
    -ora_utilizzo: l'ora inserita deve essere maggiore o uguale a 1 e deve essere un numero intero.
    -inizio: è il timestamp che rappresenta l'inizio del noleggio.
    -post: nessuna

    -stampa_data(inizio_fine) = void
    pre: inizio_fine deve essere una data valida
    post: nessuna

controllo_prenotazione(PRENOTAZIONE) = void
    -pre: La prenotazione deve essere valida e non vuota
    -post: nessuna


*/

typedef struct prenotazione* PRENOTAZIONE;

float costo_noleggio(int ora_utilizzo, time_t inizio);
time_t creazione_data();
int giorni_festivi(struct tm* tm_attuale);
int orario_sconto(struct tm* tm_attuale);
void informazioni_costo_noleggio(int ora_utilizzo, time_t inizio);
void stampa_data (time_t inizio_fine);
void controllo_prenotazione(PRENOTAZIONE richiesta);

#endif