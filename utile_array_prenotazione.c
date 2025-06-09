#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "array_prenotazione.h"
#include "utile.h"
#include "utile_array_prenotazione.h"


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
        azzera_celle(p);  
        blocca_celle_passate(p);
        salva_prenotazioni_su_file(p, targa);

        return 0;
    }

    FILE *f = fopen(nome_file, "r");

    // Se il file non esiste, inizializza la struttura e salva
    if (!f) {
        azzera_celle(p); 
        blocca_celle_passate(p);
        salva_prenotazioni_su_file(p, targa);

        return 0;
    }

    for (int i = 0; i < CELLE_GIORNALIERE; i++) {
        int valore;
        if (fscanf(f, "%d", &valore) == 1) {
            imposta_cella(p, i, valore);
        } else {
            // In caso di errore di lettura, azzera il resto
            for (; i < CELLE_GIORNALIERE; i++)
                imposta_cella(p, i, 0);
            break;
        }
    }
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
    if (!p || !targa || strlen(targa) == 0) return;
    char nome_file[32];
    snprintf(nome_file, sizeof(nome_file), "%s.txt", targa);

    FILE *f = fopen(nome_file, "w");
    if (!f) return;

    for (int i = 0; i < CELLE_GIORNALIERE; i++)
        fprintf(f, "%d\n", ottiene_cella(p, i));

    fclose(f);
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
            costo += 40.5;
        } else {
            costo += 65.8;
        }
    }

    // Se sconto è multiplo di 5, applica una tariffa scontata fissa per ogni cella
    if (sconto % 5 == 0) {
        costo = (fine_cella - inizio_cella) * 38;
    }

    printf("Il costo del veicolo: %.2f\n", costo);
    return costo;
}


/*
 Funzione: leggi_cella_da_orario
 -------------------------------
 Legge un orario da tastiera nel formato "HH MM" (ore e minuti)
 e converte l'orario nell'indice corrispondente della cella.

 Parametri:
   messaggio: messaggio da mostrare all'utente per richiedere l'input.

 Pre-condizione:
   Nessuna.

 Post-condizione:
   Nessuna modifica a variabili esterne.

 Valore di ritorno:
   Restituisce l'indice della cella corrispondente all'orario inserito.
   Continua a richiedere l'input finché non viene inserito un orario valido
   con ore tra 0 e 24 e minuti solo 0 o 30.
*/
int leggi_cella_da_orario(const char *messaggio)
{
    int ora, minuto;
    while (1) {
        printf("%s formato HH MM (ore - minuti): ", messaggio);
        int result = scanf("%d %d", &ora, &minuto);

        // Pulizia del buffer in caso di input errato
        if (result != 2) {
            printf("Input non valido. Inserisci due numeri interi.\n");
            while (getchar() != '\n'); // scarta input residuo
            continue;
        }

        if (ora < 0 || ora > 24 || (minuto != 0 && minuto != 30)) {
            printf("Orario non valido. Usa solo minuti :00 o :30 e ore tra 0 e 24.\n");
            continue;
        }

        // Valido → restituisci indice della cella
        return ora * 2 + (minuto == 30 ? 1 : 0);
    }
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
    if (!p) return false;

    for (int i = 0; i < CELLE_GIORNALIERE; i++) {
        int valore = ottiene_cella(p, i);  
        
        if (valore == 0) return true;
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
 Funzione: mostra_orari_disponibili
 ----------------------------------
 Mostra tutti gli orari disponibili (liberi) per un veicolo in base alla struttura delle celle.

 Parametri:
   p: puntatore alla struttura delle prenotazioni.

 Pre-condizione:
   p deve essere un puntatore valido.

 Post-condizione:
   Gli intervalli orari disponibili (celle con valore 0) vengono stampati a video.

 Effetti:
   Nessuna modifica allo stato interno della struttura.
*/
void mostra_orari_disponibili(ptr_prenotazione p) {
    if (!p) {
        printf("Errore: struttura prenotazioni non valida.\n");
        return;
    }

    bool in_intervallo = false;
    int inizio = 0;

    for (int i = 0; i <= CELLE_GIORNALIERE; i++) {
        if (i < CELLE_GIORNALIERE && ottiene_cella(p, i) == 0) {
            if (!in_intervallo) {
                inizio = i;
                in_intervallo = true;
            }
        } else {
            if (in_intervallo) {
                // Fine dell'intervallo libero
                int ora_inizio = inizio / 2;
                int min_inizio = (inizio % 2) * 30;
                int ora_fine = i / 2;
                int min_fine = (i % 2) * 30;

                printf("-Disponibile: dalle %02d:%02d alle %02d:%02d\n", 
                        ora_inizio, min_inizio, ora_fine, min_fine);

                in_intervallo = false;
            }
        }
    }
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

    if (prossima_cella > prendi_grandezza_array_prenotazioni()) prossima_cella = prendi_grandezza_array_prenotazioni();

    // Blocca celle non più disponibili
    for (int i = 0; i < prossima_cella; i++) {
        imposta_cella(p, i, 1);
    }
}