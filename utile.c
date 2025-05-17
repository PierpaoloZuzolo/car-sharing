#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "utile.h"



void ottieni_orario_corrente(int *ora, int *minuto) 
{
    time_t adesso = time(NULL);
    struct tm *tm_info = localtime(&adesso);
    *ora = tm_info->tm_hour;
    *minuto = tm_info->tm_min;
}


void data_attuale(int *giorno, int *mese, int *anno)
{
    time_t adesso = time(NULL);
    struct tm *oggi = localtime(&adesso);

    *giorno = oggi->tm_mday;
    *mese = oggi->tm_mon + 1;
    *anno = oggi->tm_year + 1900;
}

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