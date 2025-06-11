/*
Autore: Roberto Saporoso
Data: 16/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "utile.h"


/*
 Funzione: ottieni_orario_corrente
 ---------------------------------

 Recupera l'orario corrente locale (ora e minuto).

 Implementazione:
    Utilizza le funzioni della libreria time.h per ottenere
    l'orario locale corrente e assegna i valori di ora e minuto
    ai parametri puntatori passati.

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
void ottieni_orario_corrente(int *ora, int *minuto) 
{
    time_t adesso = time(NULL);
    struct tm *tm_info = localtime(&adesso);
    *ora = tm_info->tm_hour;
    *minuto = tm_info->tm_min;
}


/*
 Funzione: data_attuale
 ----------------------

 Recupera la data attuale del sistema (giorno, mese e anno).

 Implementazione:
    Utilizza la libreria time.h per ottenere la data corrente locale
    e assegna i valori di giorno, mese e anno ai rispettivi puntatori.

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
void data_attuale(int *giorno, int *mese, int *anno)
{
    time_t adesso = time(NULL);
    struct tm *oggi = localtime(&adesso);

    *giorno = oggi->tm_mday;
    *mese = oggi->tm_mon + 1;
    *anno = oggi->tm_year + 1900;
}


/*
 Funzione: vedi_se_giorno_nuovo
 ------------------------------

 Verifica se la data corrente del sistema è diversa dall'ultima data salvata
 in precedenza. Utile per rilevare un nuovo giorno di esecuzione del programma.

 Implementazione:
    Ottiene la data corrente del sistema tramite `data_attuale`.
    Legge l'ultima data salvata da un file ("ultimo_avvio.txt").
    Confronta la data corrente con quella salvata:
    se è diversa, restituisce true indicando che è un nuovo giorno.

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
bool vedi_se_giorno_nuovo() 
{
    int giorno, mese, anno;

    data_attuale(&giorno, &mese, &anno);
    

    // Carica ultima data salvata
    FILE *f = fopen("txt/ultimo_avvio.txt", "r");
    int ultimo_giorno = -1, ultimo_mese = -1, ultimo_anno = -1;
    if (f) {
        fscanf(f, "%d %d %d", &ultimo_giorno, &ultimo_mese, &ultimo_anno);
        fclose(f);
    }

    // Se la data è cambiata, azzera le prenotazioni
    if (giorno != ultimo_giorno || mese != ultimo_mese || anno != ultimo_anno) {
   
    return true;
    }

    return false;

}


/*
 Funzione: converti_orario_in_celle
 ----------------------------------

 Converte un intervallo orario in unità discrete ("celle") di mezz'ora
 all'interno di una giornata, dove ogni ora è suddivisa in due celle.

 Implementazione:
    Calcola la cella iniziale sommando il doppio delle ore all'offset dei minuti (0 o 1).
    Calcola la cella finale considerando se i minuti superano o meno i 30.
    Le celle sono numerate da 0 a 47 (per una giornata di 24 ore, divisa in 48 intervalli da 30 minuti).

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
void converti_orario_in_celle(int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, int *cella_inizio, int *cella_fine)
{
    *cella_inizio = ora_inizio * 2 + (minuto_inizio >= 30 ? 1 : 0);
    *cella_fine = ora_fine * 2 + (minuto_fine > 0 ? (minuto_fine <= 30 ? 1 : 2) : 0);
}


/*
 Funzione: converti_celle_in_orario
 ----------------------------------

 Converte un intervallo espresso in celle di mezz'ora nel formato orario
 classico (ore e minuti), determinando l'orario di inizio e di fine.

 Implementazione:
    Ogni cella rappresenta un intervallo di 30 minuti. 
    Divide l'indice della cella per 2 per ottenere l'ora,
    e usa il modulo per calcolare i minuti (0 o 30).

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
void converti_celle_in_orario(int cella_inizio, int cella_fine, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine) 
{
    *ora_inizio = cella_inizio / 2;
    *minuto_inizio = (cella_inizio % 2) * 30;

    *ora_fine = cella_fine / 2;
    *minuto_fine = (cella_fine % 2) * 30;
}


/*
 Funzione: calcola_costo_noleggio
 --------------------------------

 Calcola il costo totale del noleggio in base all'intervallo di tempo specificato (espresso in celle orarie) 
 e applica eventualmente uno sconto.

 Implementazione:
    - Per ogni cella da inizio a fine (esclusa la fine), somma il costo:
        - Se la cella è compresa tra le 01:00 e le 06:00 (celle 2–11), applica una tariffa ridotta (40.5).
        - In tutti gli altri casi, applica la tariffa normale (65.8).
        - Se viene specificato uno sconto maggiore o uguale a 10, ignora i costi per fascia oraria
          e applica una tariffa scontata fissa (38) per ogni cella del periodo.

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

float calcola_costo_noleggio(int inizio_cella, int fine_cella, int sconto)
{
    float costo = 0.0;
    if(inizio_cella < 0 || fine_cella > 48){
      return 0.00;
    }
    
    for (int i = inizio_cella; i < fine_cella; i++) {
        // Fascia oraria 01:00–06:00 (celle 2–11)
        if (i >= 2 && i < 12) {
            costo += 40.5;
        } else {
            costo += 65.8;
        }
    }

    // Se sconto è maggiore o uguale a 10, applica una tariffa scontata fissa per ogni cella
    if (sconto >= 10) {
        costo = (fine_cella - inizio_cella) * 38;
    }

   
    return costo;
}

/*
 Funzione: inserisci_scelta
 --------------------------

 Richiede all'utente l'inserimento di un numero intero e
 continua a chiedere finché non viene fornito un input valido.

 Implementazione:
    Usa scanf per leggere un intero dalla tastiera.
    Verifica che l'input sia corretto.
    In caso di errore, stampa un messaggio e svuota il buffer di input.
    Ripete la richiesta finché l'utente non inserisce un intero valido.

 Parametri:
    Nessuno

 Pre-condizioni:
    Nessuna

 Post-condizioni:
    L'utente avrà inserito correttamente un intero da tastiera.

 Ritorna:
    L'intero digitato dall'utente

 Side-effect:
    Legge da input standard e stampa eventuali messaggi d’errore
*/
int inserisci_scelta() 
{
    int numero;
    char ch;

    while (1) {
        printf("Scelta: ");
        if (scanf("%d", &numero) == 1) {
            // Controlla che non ci siano caratteri extra dopo il numero
            while ((ch = getchar()) != '\n' && ch != EOF); // pulisce il buffer
            return numero;
        } else {
            // Input non valido
            printf("Input non valido. Riprova.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); // pulisce il buffer
        }
    }
}