#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "veicolo.h"
#include "prenotazione.h"
#include "utile_veicolo.h"
#include "utile_prenotazione.h"
#include "hash_veicoli.h"


/*
 Funzione: stampa_veicolo
 ------------------------
 Stampa a video le informazioni del veicolo in formato leggibile.

 Parametri:
   ve: puntatore al veicolo da stampare

  Pre-condizione:
   Il puntatore ve deve essere valido (non NULL)

 Post-condizione:
   Nessuna modifica alla struttura veicolo

 Effetti:
   Stampa le principali informazioni del veicolo su standard output.
*/
void stampa_veicolo(ptr_veicolo ve)
{
    if(ve){
        printf(" %s  %s [%s] \n\tposizione: %s\n", prendi_marca(ve), prendi_modello(ve),
                                                         prendi_targa(ve), prendi_posizione(ve));
        printf("\n\tOrari disponibili:\n");

        mostra_orari_disponibili(prendi_prenotazioni(ve));
        printf("\n");
    }
}


/*
Funzione: carica_veicoli_da_file
 -------------------------------
 Carica i veicoli da un file e li inserisce in una lista.

 Parametri:
   nome_file: stringa con il nome del file da leggere
   l: puntatore alla lista di veicoli dove inserire i dati

  Pre-condizione:
   Il file deve essere formattato correttamente con righe contenenti marca, modello, targa e posizione

 Post-condizione:
   Tutti i veicoli letti dal file vengono inseriti nella lista l

 Effetti:
   Legge i dati da file e li aggiunge alla lista.
   Se il file non è accessibile, il programma termina con errore.
*/
void carica_veicoli_da_file(const char *nome_file, ptr_hash_veicoli h)
{
    FILE *file = fopen(nome_file, "r");
    if(!file){
        printf("!!!VEICOLI NON DISPONIBILI!!!");
        exit(1);
    }

    char marca[30], modello[40], targa[8], posizione[60];
    while(fscanf(file, "%30s %40s %8s %60s", marca, modello, targa, posizione) == 4){
        inserisci_veicolo_in_hash(h, inizia_veicolo(marca, modello, targa, posizione));
    }
}


/*
 Funzione: libera_veicolo
 ------------------------
 Libera la memoria occupata da un veicolo, comprese le sue prenotazioni.

 Parametri:
   ve: puntatore al veicolo da liberare

 Pre-condizione:
   ve deve essere un puntatore valido a una struttura veicolo allocata dinamicamente

 Post-condizione:
   La memoria occupata dal veicolo e dalle sue prenotazioni viene liberata

 Effetti:
   Dealloca la memoria associata al veicolo e alle sue prenotazioni.
*/
void libera_veicolo(ptr_veicolo ve)
{
    if(ve){
        libera_prenotazioni(prendi_prenotazioni(ve));
        free(ve);
    }
}



/*
 Funzione: aggiorna_stato_veicolo
 --------------------------------
 Aggiorna lo stato di disponibilità di un veicolo in base alle prenotazioni.

 Parametri:
   ve: puntatore al veicolo di cui aggiornare lo stato

  Pre-condizione:
   ve deve essere un puntatore valido a una struttura veicolo

 Post-condizione:
   Il campo 'stato' del veicolo viene aggiornato a "disponibile" se il veicolo è disponibile oggi,
   altrimenti a "non disponibile".

 Effetti:
   Aggiorna il campo 'stato' del veicolo a "disponibile" o "non disponibile"
   in base alla disponibilità odierna. Restituisce true se il veicolo
   non è disponibile, false altrimenti.
*/
bool aggiorna_stato_veicolo(ptr_veicolo ve) 
{
    if (!ve) return false;

    if (veicolo_disponibile_oggi(prendi_prenotazioni(ve))) {
        imposta_stato_veicolo(ve, "disponibile");
        return false;
    } else {
        imposta_stato_veicolo(ve, "NON disponibile");
        return true;
    }
}


bool veicolo_disponibile(ptr_veicolo ve)
{
  if(!ve) return false;

  if(strcmp(prendi_stato(ve), "disponibile") == 0){
    return true;
  }

  return false;
}
