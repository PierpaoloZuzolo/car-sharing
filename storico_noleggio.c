#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "storico_noleggio.h"
#include "utile.h"


struct storico_noleggio{
    int giorno,
        mese,
        anno,
        ora,
        minuto;
    char tipo_veicolo[50];
    char targa_veicolo[8];
    char nome_utente[50];
    float costo;
    int ora_inizio,
        minuto_inizio,
        ora_fine,
        minuto_fine;
};


ptr_storico inizia_storico_noleggio( int gg, int mm, int aa, int ora, int minuto ,char *tipo_v, char *targa_v, char *nome_ut, float costo, int inizio_ora, int inizio_minuto, int fine_ora, int fine_minuto)
{
     ptr_storico prenotazione = malloc(sizeof(struct storico_noleggio));
    if(prenotazione){
        strncpy(prenotazione->tipo_veicolo, tipo_v, sizeof(prenotazione->tipo_veicolo) - 1);
        prenotazione->tipo_veicolo[sizeof(prenotazione->tipo_veicolo) - 1] = '\0';

        strncpy(prenotazione->targa_veicolo, targa_v, sizeof(prenotazione->targa_veicolo) - 1);
        prenotazione->targa_veicolo[sizeof(prenotazione->targa_veicolo) - 1] = '\0';

        strncpy(prenotazione->nome_utente, nome_ut, sizeof(prenotazione->nome_utente) - 1);
        prenotazione->nome_utente[sizeof(prenotazione->nome_utente) - 1] = '\0';

        prenotazione->giorno = gg;
        prenotazione->mese = mm;
        prenotazione->anno = aa;
        prenotazione->ora = ora;
        prenotazione->minuto = minuto;

        prenotazione->costo = costo;

        prenotazione->ora_inizio = inizio_ora;
        prenotazione->minuto_inizio = inizio_minuto;
        prenotazione->ora_fine = fine_ora;
        prenotazione->minuto_fine = fine_minuto;


        return prenotazione;

    }

    return NULL;
}



int prendi_giorno_noleggiato(ptr_storico pr)
{
    return pr ? pr->giorno : -1;
}


int prendi_mese_noleggiato(ptr_storico pr)
{
    return pr ? pr->mese : -1;
}


int prendi_anno_noleggiato(ptr_storico pr)
{
    return pr ? pr->anno : -1;
}


int prendi_ora_noleggiato(ptr_storico pr)
{
    return pr ? pr->ora : -1;
}


int prendi_minuto_noleggiato(ptr_storico pr)
{
    return pr ? pr->minuto : -1;
}


int prendi_ora_inizio_noleggiato(ptr_storico pr)
{
    return pr ? pr->ora_inizio : -1;
}

int prendi_minuto_inizio_noleggiato(ptr_storico pr)
{
    return pr ? pr->minuto_inizio : -1;
}


int prendi_ora_fine_noleggiato(ptr_storico pr)
{
    return pr ? pr->ora_fine : -1;
}


int prendi_minuto_fine_noleggiato(ptr_storico pr)
{
    return pr ? pr->minuto_fine : -1;
}

float prendi_costo_noleggiato(ptr_storico pr)
{
    return pr ? pr->costo : -1.1;
}


char *prendi_targa_veicolo_noleggiato(ptr_storico pr)
{
    return pr ? pr->targa_veicolo : NULL;
}


char *prendi_tipo_veicolo_noleggiato(ptr_storico pr)
{
    return pr ? pr->tipo_veicolo : NULL;
}


char *prendi_utente_veicolo_noleggiato(ptr_storico pr)
{
    return pr ? pr->nome_utente : NULL;
}




void stampa_storico_noleggio(ptr_storico s)
{
    if (s == NULL) {
        printf("Prenotazione non valida.\n");
        return;
    }
    printf("-------------------------------\n");
    printf("Data: %02d/%02d/%04d\n", s->giorno, s->mese, s->anno);
    printf("Orario prenotazione: %02d:%02d\n", s->ora, s->minuto);
    printf("Orario utilizzo: %d:%d - %d:%d\n", s->ora_inizio, s->minuto_inizio, s->ora_fine, s->minuto_fine);
    printf("Tipo veicolo: %s\n", s->tipo_veicolo);
    printf("Targa veicolo: %s\n", s->targa_veicolo);
    printf("Nome utente: %s\n", s->nome_utente);
    printf("Costo: %.2f €\n", s->costo);
    printf("-------------------------------\n\n");
}


//da rivedere!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

bool vedi_se_noleggio_eliminabile(ptr_storico s) 
{
    if (!s) return false;

    int giorno_oggi, mese_oggi, anno_oggi;
    data_attuale(&giorno_oggi, &mese_oggi, &anno_oggi);

    if (prendi_giorno_noleggiato(s) != giorno_oggi ||
        prendi_mese_noleggiato(s) != mese_oggi ||
        prendi_anno_noleggiato(s) != anno_oggi) {
        return false;  // prenotazione non è di oggi
    }

    int ora_corrente, minuto_corrente;
    ottieni_orario_corrente(&ora_corrente, &minuto_corrente);

    int inizio = prendi_ora_inizio_noleggiato(s);
    int minuti_correnti = ora_corrente * 60 + minuto_corrente;
    int minuti_inizio = inizio * 60;

    if ((minuti_inizio - minuti_correnti) < 60) {
        return false;  // meno di un'ora alla prenotazione
    }

    return true;  // è oggi e c'è più di un'ora
}


void distruggi_storico_noleggio(ptr_storico s) 
{
    if (!s) return;
    // se i campi sono statici (char[]), non serve fare altro
    // se in futuro hai char* allocati, li liberi qui
    free(s); // finale: libera la struct
}

