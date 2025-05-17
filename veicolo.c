#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "lista_veicoli.h"

struct veicolo{
    char marca[30];
    char modello[40];
    char targa[8];
    char posizione[60];
    char stato[20];

   // DAFARE inserire variabile puntatore per prenotazioni
};

/*
 Crea e inizializza un nuovo veicolo con i dati forniti.
 Utilizzata per costruire un oggetto veicolo e aggiungerlo alla lista.

 Parametri:
   marca_veicolo: stringa con la marca del veicolo
   modello_veicolo: stringa con il modello del veicolo
   targa_veicolo: stringa con la targa del veicolo
   posizione_veicolo: stringa con la posizione attuale del veicolo

 Ritorna:
   Un puntatore al nuovo veicolo allocato, oppure NULL in caso di errore.
*/
ptr_veicolo inizia_veicolo(const char *marca_veicolo, const char *modello_veicolo, const char *targa_veicolo, const char *posizione_veicolo)
{
    ptr_veicolo nuovo_veicolo = malloc(sizeof(struct veicolo));
    if(nuovo_veicolo){
        strncpy(nuovo_veicolo->marca, marca_veicolo, sizeof(nuovo_veicolo->marca) - 1);
        nuovo_veicolo->marca[sizeof(nuovo_veicolo->marca) - 1] = '\0';

        strncpy(nuovo_veicolo->modello, modello_veicolo, sizeof(nuovo_veicolo->modello) - 1);
        nuovo_veicolo->modello[sizeof(nuovo_veicolo->modello) - 1] = '\0';

        strncpy(nuovo_veicolo->targa, targa_veicolo, sizeof(nuovo_veicolo->targa) - 1);
        nuovo_veicolo->targa[sizeof(nuovo_veicolo->targa) - 1] = '\0';

        strncpy(nuovo_veicolo->posizione, posizione_veicolo, sizeof(nuovo_veicolo->posizione) - 1);
        nuovo_veicolo->posizione[sizeof(nuovo_veicolo->posizione) - 1] = '\0';

        /*
            Per il parametro 'stato' che indica se un veicolo è disponibile o meno serve una funzione che va a vedere se 
            il veicolo è prenotato, in tempo reale
        */
    } 
    return nuovo_veicolo;
}

/*
 Restituisce la marca del veicolo.

 Parametri:
   ve: puntatore al veicolo

 Ritorna:
   Una stringa con la marca, oppure NULL se il puntatore è invalido.
*/
char *prendi_marca(ptr_veicolo ve)
{
    // Restituisce la marca se il veicolo è valido, altrimenti NULL
    return ve ? ve->marca : NULL;
}


/*
 Restituisce il modello del veicolo.

 Parametri:
   ve: puntatore al veicolo

 Ritorna:
   Una stringa con il modello, oppure NULL se il puntatore è invalido.
*/
char *prendi_modello(ptr_veicolo ve)
{
    // Restituisce il modello se il veicolo è valido, altrimenti NULL
    return ve ? ve->modello : NULL;
}

/*
 Restituisce la targa del veicolo.

 Parametri:
   ve: puntatore al veicolo

 Ritorna:
   Una stringa con la targa, oppure NULL se il puntatore è invalido.
*/
char *prendi_targa(ptr_veicolo ve)
{
    // Restituisce la targa se il veicolo è valido, altrimenti NULL
    return ve ? ve->targa : NULL;
}


/*
 Restituisce la posizione del veicolo.

 Parametri:
   ve: puntatore al veicolo

 Ritorna:
   Una stringa con la posizione, oppure NULL se il puntatore è invalido.
*/
char *prendi_posizione(ptr_veicolo ve)
{
    // Restituisce la posizione se il veicolo è valido, altrimenti NULL
    return ve ? ve->posizione : NULL;
}


/*
 Restituisce lo stato del veicolo (es. disponibile, occupato).

 Parametri:
   ve: puntatore al veicolo

 Ritorna:
   Una stringa con lo stato, oppure NULL se il puntatore è invalido.
*/
char *prendi_stato(ptr_veicolo ve)
{
    // Restituisce lo stato se il veicolo è valido, altrimenti NULL
    return ve ? ve->stato : NULL;
}


/*
 Stampa a video le informazioni del veicolo in formato leggibile.

 Parametri:
   ve: puntatore al veicolo da stampare

 Effetti:
   Stampa le principali informazioni del veicolo su standard output.
*/
void stampa_veicolo(ptr_veicolo ve)
{
    if(ve){
        printf(" %s  %s [%s] \n\tposizione: %s\t\t(%s)", ve->marca, ve->modello, ve->targa, ve->posizione, ve->stato);
    }
}


/*
 Carica i veicoli da un file e li inserisce in una lista.

 Parametri:
   nome_file: stringa con il nome del file da leggere
   l: puntatore alla lista di veicoli dove inserire i dati

 Effetti:
   Legge i dati da file e li aggiunge alla lista.
   Se il file non è accessibile, il programma termina con errore.
*/
void carica_veicoli_da_file(const char *nome_file, ptr_lista l)
{
    FILE *file = fopen(nome_file, "r");
    if(!file){
        printf("!!!VEICOLI NON DISPONIBILI!!!");
        exit(1);
    }

    char marca[30], modello[40], targa[8], posizione[60];
    while(fscanf(file, "%30s %40s %8s %60s", marca, modello, targa, posizione) == 4){
        inserisci_veicolo_lista(l, inizia_veicolo(marca, modello, targa, posizione));
    }
}


/*
 Libera la memoria occupata da un veicolo, comprese le sue prenotazioni.

 Parametri:
   ve: puntatore al veicolo da liberare

 Effetti:
   Dealloca la memoria associata al veicolo.
*/
void libera_veicolo(ptr_veicolo ve)
{
    if(ve){
        free(ve);
    }
}