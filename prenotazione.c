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
 Funzione: inizializza_prenotazioni
 ----------------------------------
 Inizializza una nuova struttura per la gestione delle prenotazioni.

  Pre-condizione:
   Nessuna.

 Post-condizione:
   La struttura prenotazioni è allocata e tutte le celle sono azzerate (libere).

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
 Funzione: carica_prenotazioni_da_file
 ------------------------------------
 Carica le prenotazioni associate a una targa da file, oppure inizializza una nuova giornata.

 Parametri:
   p: puntatore alla struttura delle prenotazioni da aggiornare.
   targa: targa del veicolo, usata per determinare il nome del file.

  Pre-condizione:
   p deve essere un puntatore valido.
   targa deve essere una stringa valida.

 Post-condizione:
   La struttura prenotazioni è aggiornata con i dati letti dal file,
   oppure azzerata se il file non esiste o il giorno è cambiato.
   Le celle passate vengono bloccate.

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
        blocca_celle_passate(p);
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
 Funzione: salva_prenotazioni_su_file
 -----------------------------------
 Salva su file lo stato attuale delle prenotazioni di un veicolo.

 Parametri:
   p: puntatore alla struttura delle prenotazioni da salvare.
   targa: targa del veicolo, usata per costruire il nome del file.
 
  Pre-condizione:
   p deve essere un puntatore valido.
   targa deve essere una stringa valida.

 Post-condizione:
   Il file con le prenotazioni viene aggiornato.

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
 Funzione: leggi_cella_da_orario
 -------------------------------
 Legge un orario in formato HH MM e lo converte nella corrispondente cella oraria.

 Parametri:
   messaggio: messaggio da mostrare all’utente per l’inserimento dell’orario.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   Nessuna modifica.

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
 Funzione: prenota_intervallo
 ----------------------------
 Tenta di prenotare un intervallo di celle orarie consecutive.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.
   inizio_cella: indice della cella iniziale dell’intervallo.
   fine_cella: indice della cella finale (esclusiva) dell’intervallo.

  Pre-condizione:
   p deve essere un puntatore valido.
   inizio_cella e fine_cella devono essere indici validi e inizio_cella < fine_cella.

 Post-condizione:
   Se possibile, le celle nell’intervallo sono marcate come prenotate.

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
 Funzione: veicolo_disponibile_oggi
 ----------------------------------
 Verifica se il veicolo ha almeno una cella disponibile per oggi.

 Parametri:
   p: puntatore alla struttura delle prenotazioni del veicolo.

  Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Nessuna modifica.

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
 Funzione: libera_prenotazioni
 -----------------------------
 Libera la memoria associata alla struttura delle prenotazioni.

 Parametri:
   p: puntatore alla struttura di prenotazioni da deallocare.

  Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   La memoria della struttura è liberata.

 Effetti:
   Dealloca la memoria solo se il puntatore è valido.
*/
void libera_prenotazioni(ptr_prenotazione p) 
{
    if (p) free(p);
}


/*
 Funzione: blocca_celle_passate
 -----------------------------
 Blocca le celle temporali già trascorsi nella giornata corrente.

 Parametri:
   p: puntatore alla struttura delle prenotazioni da aggiornare.

  Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Tutti le celle antecedenti all’orario corrente sono marcate come occupate.
   
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


/*
 Funzione: costo_noleggio
 -------------------------
 Calcola il costo del noleggio di un veicolo in base all'intervallo orario 
 richiesto e ad un eventuale sconto.

 Parametri:
   inizio_cella: indice della cella di inizio noleggio (inclusiva, da 0 a 47)
   fine_cella: indice della cella di fine noleggio (esclusiva)
   sconto: valore numerico usato per determinare se applicare una tariffa scontata fissa

  Pre-condizione:
   inizio_cella e fine_cella devono essere compresi tra 0 e 48,
   con inizio_cella < fine_cella.
   Il valore di sconto deve essere >= 0.

 Post-condizione:
   Viene stampato il costo totale del noleggio.
   Il valore di ritorno rappresenta il costo calcolato.

 Valore di ritorno:
   Restituisce il costo totale del noleggio come valore float.

 Comportamento:
   - Calcola il costo sommando:
       • €3.50 per ogni cella tra le 01:00 e le 06:00 (celle 2–11 incluse)
       • €5.00 per ogni altra cella
   - Se il parametro 'sconto' è un multiplo di 5, ignora il calcolo precedente
     e applica una tariffa scontata di €2.25 per ogni cella utilizzata.
   - Il costo finale viene stampato a video e restituito.
*/
float costo_noleggio(int inizio_cella, int fine_cella, int sconto)
{
    float costo = 0.0;
    
    for (int i = inizio_cella; i < fine_cella; i++) {
        // Fascia oraria 01:00–06:00 (celle 2–11)
        if (i >= 2 && i < 12) {
            costo += 3.5;
        } else {
            costo += 5.0;
        }
    }

    // Se sconto è multiplo di 5, applica una tariffa scontata fissa per ogni cella
    if (sconto % 5 == 0) {
        costo = (fine_cella - inizio_cella) * 2.25;
    }

    printf("Il costo del veicolo: %.2f\n", costo);
    return costo;
}