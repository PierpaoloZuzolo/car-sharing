#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "prenotazione.h"
#include "utile.h"


#define CELLE_GIORNALIERE 48  // 48 mezz'ore in un giorno

struct prenotazioni {
    int cella[CELLE_GIORNALIERE];  // ogni cella vale 30 minuti
};


/*
 Inizializza una nuova struttura per la gestione delle prenotazioni.

 Ritorna:
   Un puntatore a una nuova struttura prenotazioni con tutte le celle impostate a NULL.
   Restituisce NULL in caso di fallimento nell'allocazione.
*/
ptr_prenotazione inizializza_prenotazioni() 
{
    ptr_prenotazione p = malloc(sizeof(struct prenotazioni));

    if (p) memset(p->cella, 0, sizeof(p->cella));
    return p;
}


/*
 Carica le prenotazioni associate a una targa da file, oppure inizializza una nuova giornata.

 Parametri:
   p: puntatore alla struttura delle prenotazioni da aggiornare.
   targa: targa del veicolo, usata per determinare il nome del file.

 Ritorna:
   1 se il caricamento da file è avvenuto con successo, 0 se è stata inizializzata una nuova giornata.
*/
int carica_prenotazioni_da_file(ptr_prenotazione p, const char *targa) 
{
    char nome_file[32];
    snprintf(nome_file, sizeof(nome_file), "%s.txt", targa);

    // Se è un nuovo giorno, azzera la struttura, blocca le celle passate e salva su file
    if(vedi_se_giorno_nuovo()){
        memset(p->cella, 0, sizeof(p->cella));  
        blocca_slot_passati(p);
        salva_prenotazioni_su_file(p, targa);

        return 0;
    }

    FILE *f = fopen(nome_file, "r");

    // Se il file non esiste, inizializza la struttura e salva
    if (!f) {
        memset(p->cella, 0, sizeof(p->cella)); 
        blocca_celle_passate(p);
        salva_prenotazioni_su_file(p, targa);

        return 0;
    }

    for (int i = 0; i < CELLE_GIORNALIERE; i++)
        fscanf(f, "%d", &p->cella[i]);

    fclose(f);

    // Blocca le celle del tempo passato e salva lo stato aggiornato
    blocca_celle_passate(p);
    salva_prenotazioni_su_file(p, targa);

    return 1;
}


/*
 Salva su file lo stato attuale delle prenotazioni di un veicolo.

 Parametri:
   p: puntatore alla struttura delle prenotazioni da salvare.
   targa: targa del veicolo, usata per costruire il nome del file.

 Effetti:
   Scrive il contenuto delle celle in un file chiamato "<targa>.txt".
*/
void salva_prenotazioni_su_file(ptr_prenotazione p, const char *targa) 
{
    char nome_file[32];
    snprintf(nome_file, sizeof(nome_file), "%s.txt", targa);

    FILE *f = fopen(nome_file, "w");
    if (!f) return;

    for (int i = 0; i < CELLE_GIORNALIERE; i++)
        fprintf(f, "%d\n", p->cella[i]);

    fclose(f);
}


/*
 Legge un orario in formato HH MM e lo converte nella corrispondente cella oraria.

 Parametri:
   messaggio: messaggio da mostrare all’utente per l’inserimento dell’orario.

 Valore di ritorno:
   Restituisce l’indice della cella (0–47) corrispondente all’orario,
   oppure -1 in caso di input non valido.
*/
int leggi_cella_da_orario(const char *messaggio)
{
    int ora, minuto;

    printf("%s formato HH MM (ore - minuti): ", messaggio);
    if (scanf("%d %d", &ora, &minuto) != 2 || ora < 0 || ora > 24 || (minuto != 0 && minuto != 30)) {
        printf("Orario non valido. Usa solo :00 o :30.\n");
        return -1;
    }

    // Calcola l’indice della cella (es. 9:30 → 19)
    return ora * 2 + (minuto == 30 ? 1 : 0);
}


/*
 Tenta di prenotare un intervallo di celle orarie consecutive.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.
   inizio_cella: indice della cella iniziale dell’intervallo.
   fine_cella: indice della cella finale (esclusiva) dell’intervallo.

 Valore di ritorno:
   Restituisce 1 se l’intervallo è stato prenotato con successo, 0 altrimenti.
   Fallisce se l’intervallo è invalido o se una cella dell’intervallo è già occupata.
*/
int prenota_intervallo(ptr_prenotazione p, int inizio_cella, int fine_cella) 
{
    if (!p) return 0;

    if (inizio_cella < 0 || fine_cella > CELLE_GIORNALIERE  || inizio_cella >= fine_cella) {
        printf(" Intervallo non valido: inizio=%d, fine=%d\n", inizio_cella, fine_cella);
        return 0;
    }

    // Verifica disponibilità in quell'orario
    for (int i = inizio_cella; i < fine_cella; i++) {
        if (p->cella[i]) {
            printf(" Intervallo occupato (slot %d gia prenotato).\n", i);
            return 0;
        }
    }

    // Prenota se è libero quell'orario
    for (int i = inizio_cella; i < fine_cella; i++) {
        p->cella[i] = 1;
    }

    return 1;
}


/*
 Verifica se il veicolo ha almeno una cella disponibile per oggi.

 Parametri:
   p: puntatore alla struttura delle prenotazioni del veicolo.

 Valore di ritorno:
   Restituisce true se almeno una cella è libera, false altrimenti.
   Termina il programma se il puntatore è NULL.
*/
bool veicolo_disponibile_oggi(ptr_prenotazione p) 
{
    if (!p) exit(1);

    for (int i = 0; i < CELLE_GIORNALIERE; i++) {
        if (p->cella[i] == 0) return true;
    }

    return false;
}


/*
 Libera la memoria associata alla struttura delle prenotazioni.

 Parametri:
   p: puntatore alla struttura di prenotazioni da deallocare.

 Effetti:
   Dealloca la memoria solo se il puntatore è valido.
*/
void libera_prenotazioni(ptr_prenotazione p) 
{
    if (p) free(p);
}


/*
 Blocca le celle temporali già trascorsi nella giornata corrente.

 Parametri:
   p: puntatore alla struttura delle prenotazioni da aggiornare.

 Effetti:
   Segna come occupate le celle corrispondenti a orari già passati rispetto all'orario attuale.
   L'approssimazione considera lo slot successivo anche se si è oltre :00 o :30.
*/
void blocca_celle_passate(ptr_prenotazione p) 
{
    if (!p) return;

    int ora, minuto;
    ottieni_orario_corrente(&ora, &minuto);

    // Calcola la prima cella prenotabile: approssimiamo sempre in avanti
    int prossima_cella = ora * 2 + (minuto > 0 ? (minuto <= 30 ? 1 : 2) : 0);

    if (prossima_cella > CELLE_GIORNALIERE) prossima_cella = CELLE_GIORNALIERE;

    // Blocca celle non più disponibili
    for (int i = 0; i < prossima_cella; i++) {
        p->cella[i] = 1; 
    }
}
