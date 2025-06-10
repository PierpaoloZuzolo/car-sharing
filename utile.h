/*
Autore: Roberto Saporoso
Data: 16/05/2025
*/

#ifndef UTILE_H
#define UTILE_H

#include <stdbool.h>


/*
 Funzione: ottieni_orario_corrente
 ---------------------------------

 Recupera l'orario corrente locale (ora e minuto).

 Parametri:
    ora: puntatore a intero dove verrà salvata l'ora corrente (0-23)
    minuto: puntatore a intero dove verrà salvato il minuto corrente (0-59)

 Pre-condizioni:
    I puntatori `ora` e `minuto` devono essere validi e non NULL.

 Post-condizioni:
    I valori puntati da `ora` e `minuto` sono aggiornati all'orario corrente.

 Ritorna:
    void

 Side-effect:
    Nessuno.
*/
void ottieni_orario_corrente(int *ora, int *minuto);


/*
 Funzione: data_attuale
 ----------------------

 Recupera la data attuale del sistema (giorno, mese e anno).

 Parametri:
    giorno: puntatore a intero dove verrà salvato il giorno del mese (1-31)
    mese: puntatore a intero dove verrà salvato il numero del mese (1-12)
    anno: puntatore a intero dove verrà salvato l'anno (es. 2025)

 Pre-condizioni:
    I puntatori `giorno`, `mese` e `anno` devono essere validi e non NULL.

 Post-condizioni:
    I valori puntati da `giorno`, `mese` e `anno` vengono aggiornati alla data corrente.

 Ritorna:
    void

 Side-effect:
    Nessuno.
*/
void data_attuale(int *giorno, int *mese, int *anno);


/*
 Funzione: vedi_se_giorno_nuovo
 ------------------------------

 Verifica se la data corrente del sistema è diversa dall'ultima data salvata
 in precedenza. Utile per rilevare un nuovo giorno di esecuzione del programma.

 Parametri:
    Nessuno.

 Pre-condizioni:
    Il file "ultimo_avvio.txt" (se esiste) deve contenere una riga con tre interi
    nel formato: giorno mese anno.

 Post-condizioni:
    Nessuna modifica viene effettuata nel file.

 Ritorna:
    true se la data attuale è diversa da quella salvata;
    false altrimenti.

 Side-effect:
    Legge da file "ultimo_avvio.txt".
*/
bool vedi_se_giorno_nuovo();

/*
 Funzione: converti_orario_in_celle
 ----------------------------------

 Converte un intervallo orario in unità discrete ("celle") di mezz'ora
 all'interno di una giornata, dove ogni ora è suddivisa in due celle.


 Parametri:
    ora_inizio: ora di inizio (intero da 0 a 23)
    minuto_inizio: minuti dell'ora di inizio (intero da 0 a 59)
    ora_fine: ora di fine (intero da 0 a 23)
    minuto_fine: minuti dell'ora di fine (intero da 0 a 59)
    cella_inizio: puntatore a intero dove verrà salvata la cella iniziale
    cella_fine: puntatore a intero dove verrà salvata la cella finale

 Pre-condizioni:
    Tutti i valori di ora devono essere nell'intervallo [0, 23]
    Tutti i valori di minuto devono essere nell'intervallo [0, 59]
    I puntatori cella_inizio e cella_fine devono essere validi (non NULL)

 Post-condizioni:
    Vengono scritti in `*cella_inizio` e `*cella_fine` gli indici delle celle corrispondenti
    all'inizio e alla fine dell'intervallo orario.

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Scrive nei puntatori forniti.
 */
void converti_orario_in_celle(int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, int *cella_inizio, int *cella_fine);


/*
 Funzione: converti_celle_in_orario
 ----------------------------------

 Converte un intervallo espresso in celle di mezz'ora nel formato orario
 classico (ore e minuti), determinando l'orario di inizio e di fine.

 Parametri:
    cella_inizio: intero rappresentante la cella di inizio (da 0 a 47)
    cella_fine: intero rappresentante la cella di fine (da 0 a 48)
    ora_inizio: puntatore a intero per salvare l'ora di inizio
    minuto_inizio: puntatore a intero per salvare i minuti di inizio
    ora_fine: puntatore a intero per salvare l'ora di fine
    minuto_fine: puntatore a intero per salvare i minuti di fine

 Pre-condizioni:
    I valori di cella_inizio e cella_fine devono essere nell'intervallo [0, 48]
    I puntatori ora_inizio, minuto_inizio, ora_fine e minuto_fine devono essere validi (non NULL)

 Post-condizioni:
    I valori delle ore e dei minuti corrispondenti vengono scritti nei puntatori forniti

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Scrive nei puntatori passati come argomenti.
 */
void converti_celle_in_orario(int cella_inizio, int cella_fine, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine);

/*
 Funzione: calcola_costo_noleggio
 --------------------------------

 Calcola il costo totale del noleggio in base all'intervallo di tempo specificato (espresso in celle orarie) 
 e applica eventualmente uno sconto.

 Parametri:
    inizio_cella: intero che rappresenta la cella oraria di inizio (inclusa).
    fine_cella: intero che rappresenta la cella oraria di fine (esclusa).
    sconto: intero che rappresenta una soglia per applicare una tariffa scontata.

 Pre-condizioni:
    - inizio_cella e fine_cella devono essere compresi nel range valido di celle (es. 0 <= inizio_cella < fine_cella <= CELLE_GIORNALIERE).
    - sconto deve essere >= 0.

 Post-condizioni:
    Nessuna modifica a strutture esterne o parametri.

 Ritorna:
    Un valore `float` che rappresenta il costo complessivo del noleggio, eventualmente scontato.

 Side-effect:
    Nessuno.
*/

float calcola_costo_noleggio(int inizio_cella, int fine_cella, int sconto);


#endif
