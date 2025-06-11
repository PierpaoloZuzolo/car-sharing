/*
Autore: Pierpaolo Zuzolo
Data: 13/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "ADT_array/array_prenotazione.h"
#include "utile.h"
#include "utile_array_prenotazione.h"



/*
  Funzione: carica_prenotazioni_da_file
  -------------------------------------

  Carica le prenotazioni associate a una determinata targa da un file di testo.

  Implementazione:
     Costruisce il nome del file a partire dal nome della targa e, se fornito, dal percorso.
     Se il file non esiste, inizializza la struttura di prenotazioni a 0 e crea un nuovo file.
     Se il file esiste, legge i valori interi e li assegna alle celle della struttura prenotazioni.

  Parametri:
     p: puntatore alla struttura delle prenotazioni da inizializzare
     targa: stringa che identifica la targa dell'auto
     percorso_file: stringa opzionale contenente il percorso del file

  Pre-condizioni:
     p != NULL
     targa != NULL e non vuota

  Post-condizioni:
     se il file non esiste, la struttura prenotazioni è azzerata e viene creato un nuovo file vuoto;
     se il file esiste e la lettura va a buon fine, le prenotazioni vengono caricate correttamente;
     in caso di errori di lettura, le celle rimanenti vengono azzerate.

  Ritorna:
     1 in caso di successo (anche se il file non esiste e viene creato);
     non gestisce casi di errore con valori di ritorno diversi da 1.

  Side-effect:
     può creare un nuovo file se quello specificato non esiste;
     può modificare il contenuto della struttura `p`;
     può leggere da file e allocare risorse temporanee per il nome del file.
 */

int carica_prenotazioni_da_file(ptr_prenotazione p, const char *targa, const char *percorso_file)
{
    int dimensione_array = prendi_grandezza_array_prenotazioni();
    char nome_file[256];

    if (percorso_file && percorso_file[0] != '\0') {
        snprintf(nome_file, sizeof(nome_file), "%s/%s.txt", percorso_file, targa);
    } else {
        snprintf(nome_file, sizeof(nome_file), "%s.txt", targa);
    }


    FILE *f = fopen(nome_file, "r");

    // Se il file non esiste, inizializza la struttura e salva
    if (!f) {
        azzera_celle(p); 
        salva_prenotazione_su_file(p, targa, percorso_file);   // DA RIVEDERE SE FUNZIONA !!!!!!!!!!!!!!!!!!!!!1

        return 1;
    }

    for (int i = 0; i < dimensione_array; i++) {
        int valore;
        if (fscanf(f, "%d", &valore) == 1) {
            imposta_cella(p, i, valore);
        } else {
            // In caso di errore di lettura, azzera il resto
            for (; i < dimensione_array; i++)
                imposta_cella(p, i, 0);
            break;
        }
    }
    fclose(f);

    return 1;
}


/*
  Funzione: salva_prenotazione_su_file
  ------------------------------------

  Salva su file le prenotazioni contenute nella struttura specificata.

  Implementazione:
     Costruisce il nome del file a partire dalla targa e, se fornito, dal percorso.
     Apre il file in modalità scrittura ("w").
     Scrive su file i valori interi contenuti nella struttura di prenotazioni, uno per riga.

  Parametri:
     p: puntatore alla struttura delle prenotazioni da salvare
     targa: stringa che identifica la targa dell'auto
     percorso_file: stringa opzionale contenente il percorso della directory

  Pre-condizioni:
     p != NULL
     targa != NULL e non vuota (strlen(targa) > 0)

  Post-condizioni:
     se il file può essere aperto correttamente, i dati della struttura `p` sono scritti su file;
     se il file non può essere aperto, nessuna operazione viene effettuata.

  Ritorna:
     Nessun valore di ritorno (funzione `void`)

  Side-effect:
     crea o sovrascrive un file nella directory specificata;
     scrive su disco i dati della struttura `p`.
 */

void salva_prenotazione_su_file(ptr_prenotazione p, const char *targa, const char *percorso_file) 
{
    if (!p || !targa || strlen(targa) == 0) return;
    char nome_file[256];
    if (percorso_file && percorso_file[0] != '\0') {
        snprintf(nome_file, sizeof(nome_file), "%s/%s.txt", percorso_file, targa);
    } else {
        snprintf(nome_file, sizeof(nome_file), "%s.txt", targa);
    }

    FILE *f = fopen(nome_file, "w");
    if (!f) return;
    int dimensione_array = prendi_grandezza_array_prenotazioni();
    for (int i = 0; i < dimensione_array; i++)
        fprintf(f, "%d\n", ottiene_cella(p, i));

    fclose(f);
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
            printf("Input non valido. Inserisci due numeri interi.\n");   // DA SPOSTARE IN UTILI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

    int dimensione_array = prendi_grandezza_array_prenotazioni();

    for (int i = 0; i < dimensione_array; i++) {
        int valore = ottiene_cella(p, i);  
        
        if (valore == 0) return true;
    }
    return false;
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
    int inizio = 0, dimensione_array;
    dimensione_array = prendi_grandezza_array_prenotazioni();

    for (int i = 0; i <= dimensione_array; i++) {
        if (i < dimensione_array && ottiene_cella(p, i) == 0) {
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