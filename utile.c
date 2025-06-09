#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "utile.h"


/*
 Funzione: ottieni_orario_corrente
 ---------------------------------
 Recupera l'orario corrente del sistema.

 Parametri:
   ora: puntatore a intero dove viene salvata l'ora corrente (0-23).
   minuto: puntatore a intero dove viene salvato il minuto corrente (0-59).

 Pre-condizione:
   I puntatori ora e minuto devono essere validi (non NULL).

 Post-condizione:
   I valori puntati vengono aggiornati con l'orario corrente.

 Effetti:
   Nessun effetto collaterale oltre all'aggiornamento dei valori.
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
 Recupera la data corrente del sistema.

 Parametri:
   giorno: puntatore a intero dove salvare il giorno corrente.
   mese: puntatore a intero dove salvare il mese corrente.
   anno: puntatore a intero dove salvare l'anno corrente.

 Pre-condizione:
   I puntatori devono essere validi (non NULL).

 Post-condizione:
   I valori vengono aggiornati con la data attuale (gg/mm/aaaa).

 Effetti:
   Nessun effetto collaterale oltre all'aggiornamento dei parametri.
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
 Verifica se è iniziato un nuovo giorno rispetto all'ultimo avvio.

 Parametri:
   Nessuno.

 Pre-condizione:
   Deve esistere (o essere creato) un file "ultimo_avvio.txt" per il salvataggio persistente.

 Post-condizione:
   Confronta la data attuale con quella salvata precedentemente.
   Se è un giorno nuovo, restituisce true. Altrimenti false.

 Ritorna:
   true se la data è diversa da quella precedentemente salvata,
   false se è la stessa.

 Effetti:
   Nessun salvataggio automatico. Solo lettura da file.
   Il salvataggio della nuova data dovrebbe essere gestito separatamente.
*/
bool vedi_se_giorno_nuovo() 
{
    int giorno, mese, anno;

    data_attuale(&giorno, &mese, &anno);
    

    // Carica ultima data salvata
    FILE *f = fopen("ultimo_avvio.txt", "r");
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


void converti_orario_in_celle(int ora_inizio, int minuto_inizio, int ora_fine, int minuto_fine, int *cella_inizio, int *cella_fine)
{
    *cella_inizio = ora_inizio * 2 + (minuto_inizio >= 30 ? 1 : 0);
    *cella_fine = ora_fine * 2 + (minuto_fine > 0 ? (minuto_fine <= 30 ? 1 : 2) : 0);
}



void converti_celle_in_orario(int cella_inizio, int cella_fine, int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine) 
{
    *ora_inizio = cella_inizio / 2;
    *minuto_inizio = (cella_inizio % 2) * 30;

    *ora_fine = cella_fine / 2;
    *minuto_fine = (cella_fine % 2) * 30;
}


