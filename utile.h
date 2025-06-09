#ifndef UTILE_H
#define UTILE_H

#include <stdbool.h>

/*
 Funzione: ottieni_orario_corrente
 ---------------------------------
 Ottiene l'orario corrente del sistema e lo restituisce nei parametri forniti.

 Parametri:
   ora: puntatore a intero dove verrà salvata l'ora corrente (0-23).
   minuto: puntatore a intero dove verrà salvato il minuto corrente (0-59).

 Pre-condizione:
   I puntatori ora e minuto devono essere validi (non NULL).

 Post-condizione:
   I valori di ora e minuto vengono aggiornati con l'orario corrente.

 Ritorna:
   Nessun valore. I risultati sono passati per riferimento.
*/
void ottieni_orario_corrente(int *ora, int *minuto);


/*
 Funzione: data_attuale
 ----------------------
 Ottiene la data corrente del sistema e la restituisce nei parametri forniti.

 Parametri:
   giorno: puntatore a intero dove verrà salvato il giorno corrente.
   mese: puntatore a intero dove verrà salvato il mese corrente.
   anno: puntatore a intero dove verrà salvato l'anno corrente.

 Pre-condizione:
   I puntatori giorno, mese e anno devono essere validi (non NULL).

 Post-condizione:
   I valori vengono aggiornati con la data corrente.

 Ritorna:
   Nessun valore. I risultati sono passati per riferimento.
*/
void data_attuale(int *giorno, int *mese, int *anno);


/*
 Funzione: vedi_se_giorno_nuovo
 ------------------------------
 Verifica se è trascorso un nuovo giorno rispetto all'ultima verifica effettuata.

 Parametri:
   Nessuno.

 Pre-condizione:
   È richiesta una memorizzazione persistente della data precedente (tramite file o variabili statiche/globale).

 Post-condizione:
   Nessuna modifica visibile all'esterno, ma può aggiornare lo stato interno.

 Ritorna:
   true se è iniziato un nuovo giorno, false altrimenti.
*/
bool vedi_se_giorno_nuovo();


void converti_orario_in_celle(int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, int *cella_inizio, int *cella_fine);


void converti_celle_in_orario(int cella_inizio, int cella_fine, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine);



#endif
