/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

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

 Carica le prenotazioni giornaliere da file per un dato veicolo identificato dalla targa,
 aggiorna la struttura in memoria, e gestisce il reset e il blocco delle celle temporali
 in base alla data corrente.

 Implementazione:
    Costruisce il nome del file a partire dalla targa con estensione ".txt".
    Controlla se è un nuovo giorno:
       - se sì, azzera tutte le celle, blocca quelle passate e salva la struttura su file,
         quindi ritorna 0.
    Tenta di aprire il file in lettura:
       - se il file non esiste, azzera le celle, blocca quelle passate e salva,
         quindi ritorna 0.
    Legge da file i valori delle celle (numeri interi) fino a un massimo di CELLE_GIORNALIERE.
       - se incontra un errore di lettura, azzera le celle rimanenti.
    Chiude il file.
    Blocca le celle del tempo passato in base all'ora corrente e salva nuovamente su file.
    Ritorna 1 se il caricamento è avvenuto da file, 0 in caso di nuovo giorno o file mancante.

 Parametri:
    p     : puntatore alla struttura prenotazione da aggiornare
    targa : stringa identificativa del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido a una struttura prenotazione
    targa deve essere una stringa valida e non NULL
    Le funzioni vedi_se_giorno_nuovo, azzera_celle, blocca_celle_passate,
    salva_prenotazioni_su_file e imposta_cella devono essere definite e funzionanti

 Post-condizioni:
    La struttura prenotazione è aggiornata con i dati caricati dal file o inizializzata se necessario.
    Il file storico delle prenotazioni viene aggiornato in base allo stato attuale.

 Ritorna:
    1 se la struttura è stata caricata da file con successo
    0 se è stato un nuovo giorno o il file non esisteva (dunque struttura inizializzata)

 Side-effect:
    Modifica la struttura prenotazione in memoria
    Effettua letture e scritture su file corrispondente alla targa
    Effettua stampe di errore su stdout se presenti (non implementato esplicitamente)
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

 Salva su file lo stato corrente delle prenotazioni giornaliere relative a un veicolo
 identificato tramite la sua targa.

 Implementazione:
    Controlla che il puntatore alla struttura prenotazione e la targa siano validi.
    Costruisce il nome del file aggiungendo ".txt" alla targa.
    Apre il file in modalità scrittura (sovrascrive il contenuto precedente).
    Scrive riga per riga i valori delle celle delle prenotazioni (interi).
    Chiude il file.

 Parametri:
    p     : puntatore alla struttura contenente le prenotazioni
    targa : stringa identificativa del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido
    targa deve essere una stringa valida e non vuota
    La funzione ottiene_cella deve restituire il valore corretto della cella di prenotazione

 Post-condizioni:
    Il file associato alla targa è aggiornato con lo stato corrente delle prenotazioni.

 Ritorna:
    void

 Side-effect:
    Effettua scrittura su file
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



//DA FINIREEE
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

 Legge da input un orario nel formato "HH MM" (ore minuti) e lo converte nell'indice
 di una cella oraria, considerando che ogni ora è divisa in due celle (00 e 30 minuti).

 Implementazione:
    - Richiede all'utente di inserire un orario nel formato HH MM.
    - Controlla che l'input sia valido (due numeri interi).
    - Verifica che l'ora sia tra 0 e 24 e che i minuti siano solo 0 o 30.
    - In caso di errore, mostra un messaggio e ripete la richiesta.
    - Se valido, calcola e restituisce l'indice della cella corrispondente:
      ogni ora corrisponde a 2 celle, 0 minuti → cella pari, 30 minuti → cella dispari.

 Parametri:
    messaggio : stringa da mostrare come prompt all'utente per la lettura dell'orario

 Pre-condizioni:
    messaggio deve essere una stringa valida non nulla

 Post-condizioni:
    Nessuna modifica a variabili esterne

 Ritorna:
    L'indice intero della cella oraria corrispondente all'orario inserito (da 0 a 48)

 Side-effect:
    Stampa messaggi su stdout e legge da stdin
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

 Verifica se un veicolo ha almeno una cella oraria libera (non prenotata) nell'arco
 della giornata corrente.

 Implementazione:
    Controlla che il puntatore alla struttura prenotazione sia valido.
    Scorre tutte le celle giornaliere della prenotazione.
    Se trova almeno una cella con valore 0 (libera), restituisce true.
    Altrimenti restituisce false.

 Parametri:
    p: puntatore alla struttura prenotazione del veicolo

 Pre-condizioni:
    p deve essere un puntatore valido a una struttura prenotazione

 Post-condizioni:
    Nessuna modifica ai dati puntati da p

 Ritorna:
    true se esiste almeno una cella libera (valore 0) nella giornata
    false se tutte le celle sono occupate o p è NULL

 Side-effect:
    Nessuno
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

 Libera la memoria allocata per la struttura prenotazione puntata da p.

 Implementazione:
    Verifica che il puntatore p non sia NULL.
    Se valido, esegue la deallocazione della memoria tramite free().

 Parametri:
    p: puntatore alla struttura prenotazione da liberare

 Pre-condizioni:
    p deve essere un puntatore valido ottenuto da malloc o simile,
    oppure NULL (in questo caso la funzione non fa nulla).

 Post-condizioni:
    La memoria puntata da p viene liberata.

 Ritorna:
    void

 Side-effect:
    Libera memoria allocata dinamicamente.
*/
void libera_prenotazioni(ptr_prenotazione p) 
{
    if (p) free(p);
}


/*
 Funzione: mostra_orari_disponibili
 ----------------------------------

 Stampa a video gli intervalli orari disponibili (liberi) rappresentati
 dalla struttura delle prenotazioni.

 Implementazione:
    Controlla la validità del puntatore alla struttura prenotazioni.
    Scorre tutte le celle giornaliere, identificando gli intervalli di celle libere (valore 0).
    Per ogni intervallo continuo di celle libere stampa l’orario di inizio e fine, in formato HH:MM.

 Parametri:
    p: puntatore alla struttura prenotazione

 Pre-condizioni:
    p deve essere un puntatore valido.

 Post-condizioni:
    Vengono stampati su stdout gli intervalli orari liberi presenti nella prenotazione.

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout.
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
 ------------------------------

 Blocca (imposta a 1) tutte le celle corrispondenti agli intervalli orari
 già trascorsi rispetto all’orario corrente, rendendoli indisponibili per prenotazioni.

 Implementazione:
    Ottiene l’orario corrente (ora e minuto).
    Calcola la prima cella ancora prenotabile approssimando in avanti (se minuto > 0).
    Imposta tutte le celle fino a quella calcolata a 1 (bloccate).
    Non modifica le celle successive.

 Parametri:
    p: puntatore alla struttura prenotazione da aggiornare.

 Pre-condizioni:
    p deve essere un puntatore valido.

 Post-condizioni:
    Le celle degli orari già trascorsi sono impostate a 1 (non prenotabili).

 Ritorna:
    void

 Side-effect:
    Modifica lo stato delle celle nella struttura prenotazione.
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