/*
Autore: Pierpaolo Zuzolo
Data: 10/06/2025
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>      // Per fabs
#include <unistd.h>    // Per dup, dup2, close
#include <stdbool.h>   // Per bool


#include "utili/utile_veicolo.h"
#include "ADT_array/array_prenotazione.h"
#include "utili/utile_array_prenotazione.h"
#include "utili/utile.h"
#include "Modello_storico_noleggio/storico_noleggio.h"
#include "ADT_hash/hash_utenti.h"
#include "Modello_veicolo/veicolo.h"
#include "ADT_hash/hash_veicoli.h"
#include "Modello_utente/utente.h"
#include "ADT_array/array.h"
#include "ADT_hash/tab_hash.h"
#include "utili/utile_utente.h"
#include "ADT_lista/lista_storico_noleggio.h"
#include "utili/utile_lista_storico_noleggio.h"



#define LUNGHEZZA_RIGA 600
#define CONTENITORE 1024
#define NUMERO_UTENTI 5
#define NUMERO_VEICOLI 5
#define SCARTO 0.01 //Errore del costo
#define MAX_LINE 1024 //da eliminare


int prendi_veicolo_da_file(FILE *fp, ptr_hash_veicoli utente);
int prendi_utenti_da_file(FILE *fp, ptr_hash_utenti utente);
int test_funzione1(void);
int test_funzione2(ptr_hash_veicoli veicolo, ptr_hash_utenti ut);
int test_funzione3();
int confronta_file(FILE*, FILE*);


/*
 Funzione: main
 --------------

 Funzione principale del programma di test. Carica i dati da file, esegue i test specificati
 e scrive i risultati in un file di output.

 Implementazione:
    - Verifica la presenza dei parametri da linea di comando.
    - Apre i file specificati per leggere i dati e scrivere i risultati.
    - Crea e popola le tabelle hash per utenti e veicoli.
    - Legge ed esegue i test indicati nella suite.
    - Confronta gli output con i file oracle e scrive il risultato.
    - Libera la memoria allocata e chiude tutti i file.

 Parametri:
    argc: numero di argomenti passati da linea di comando
    argv: array di stringhe contenente i nomi dei file richiesti:
          - argv[1]: file della suite di test
          - argv[2]: file contenente i dati utenti
          - argv[3]: file contenente i dati veicoli

 Pre-condizioni:
    - Devono essere forniti almeno 3 file corretti da linea di comando.
    - I file devono essere presenti e leggibili.

 Post-condizioni:
    - Viene creato/aggiornato il file result.txt con i risultati dei test eseguiti.

 Ritorna:
    0  se tutti i test sono eseguiti correttamente;
    -1 in caso di errore (file mancanti, errori di caricamento, errori nei test).

 Side-effect:
    - Stampa messaggi di errore su standard output.
    - Alloca e libera memoria dinamica.
    - Scrive su file result.txt.
 */
int main(int argc, char **argv) {
    if(argc < 4){
        printf("Assicurati di mettere tutti i parametri!\n");
        printf("Per runnare scrivere: ./test.exe test_suite.txt utenti.txt veicoli.txt\n");
        return -1;
    }

    char *test_suite = argv[1];
    char *file_utente = argv[2];
    char *file_veicolo= argv[3];

    FILE *ts = fopen (test_suite, "r");
    FILE *file_utenti = fopen (file_utente, "r");
    FILE *file_veicoli = fopen (file_veicolo, "r");
    FILE *file_result = fopen("result.txt", "w");

    if(!(ts && file_utenti && file_veicoli && file_result)){
        printf("Errore apertura file utenti!\n");
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        fclose(file_result);
        return -1;
    }

    ptr_hash_utenti hash_utenti = crea_hash_utenti(NUMERO_UTENTI);
    if (!hash_utenti) {
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        fclose(file_result);
        return -1;
    }
    if(carica_utenti_da_file(file_utente, hash_utenti, NULL) < 0){
        printf("Errore caricamento utenti!\n(Controlla il formato nome email)");
        distruggi_hash_utenti(hash_utenti);
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        return -1;
    }

    ptr_hash_veicoli hash_veicoli = crea_hash_veicoli(NUMERO_VEICOLI);
    if (!hash_veicoli) {
        distruggi_hash_utenti(hash_utenti);
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        fclose(file_result);
        return -1;
    }
    if(carica_veicoli_da_file(file_veicolo, hash_veicoli, NULL) == 0){
        printf("Errore caricamento veicoli!\n(Controlla il formato marca modello targa posizione)");
        distruggi_hash_utenti(hash_utenti);
        distruggi_hash_veicoli(hash_veicoli);
        fclose(file_utenti);
        fclose(ts);
        fclose(file_veicoli);
        return -1;
    }


    char test_case[LUNGHEZZA_RIGA];
    while (fgets(test_case, sizeof(test_case), ts)) {
        test_case[strcspn(test_case, "\n")] = 0; // rimuove newline

        char *tc_generale = strtok(test_case, " ");
        if(strcmp(tc_generale, "TC1") == 0){
            if(test_funzione1() < 0){
                printf("Errore TC1\n");
                continue;
            }
        }

        if(strcmp(tc_generale, "TC2") == 0){
            if(test_funzione2(hash_veicoli, hash_utenti) < 0){
                printf("Errore TC2\n");
                continue;
            }
        }
        if(strcmp(tc_generale, "TC3") == 0){
            if(test_funzione3() < 0){
                printf("Errore TC3\n");
                continue;
            }
        }

        char file_oracle[CONTENITORE] = {0};
        snprintf(file_oracle, CONTENITORE, "%s/oracle.txt", tc_generale);

        char file_output[CONTENITORE] = {0};
        snprintf(file_output, CONTENITORE, "%s/output.txt", tc_generale);

        //Apertura file
        FILE *oracle_file = fopen(file_oracle, "r");
        FILE *output_file = fopen(file_output, "r");

        if (!oracle_file) {
            printf("Errore apertura file %s\n", file_oracle);
            fflush(stdout);
        }
        if (!output_file) {
            printf("Errore apertura file %s\n", file_output);
            fflush(stdout);
        }
    
        if (!oracle_file || !output_file) {
            if (oracle_file) fclose(oracle_file);
            if (output_file) fclose(output_file);
            return -1;
        }

        int risultato = confronta_file(oracle_file, output_file);
        //Scrittura PASS/FAIL in 'result.txt' es. TC1:PASS
        fprintf(file_result, "%s: %s\n", tc_generale, risultato ? "PASS" : "FAIL");
        fflush(file_result);

        fclose(oracle_file);
        fclose(output_file);
    }
    
    distruggi_hash_utenti(hash_utenti);
    distruggi_hash_veicoli(hash_veicoli);
    fclose(ts);
    fclose(file_veicoli);
    fclose(file_utenti);
    fclose(file_result);


    printf("\n\nRisultati stampati consulta result.txt\n");
    return 0;
}



/*
 Funzione: prendi_utenti_da_file
 --------------------------------

 Legge i dati degli utenti da un file e li inserisce nella tabella hash utenti.

 Implementazione:
    - Legge ogni riga del file specificato.
    - Divide la riga in due token: nome ed email.
    - Per ogni riga valida, crea un nuovo utente e lo inserisce nella hash.
    - In caso di righe non valide o errori d’inserimento, restituisce errore.

 Parametri:
    fp: puntatore al file da cui leggere i dati degli utenti.
    utente: puntatore alla tabella hash in cui inserire gli utenti.

 Pre-condizioni:
    - Il file deve essere già aperto in lettura.
    - La tabella hash deve essere già allocata e inizializzata.
    - Ogni riga del file deve essere nel formato: "<nome> <email>".

 Post-condizioni:
    - La tabella hash contiene tutti gli utenti caricati correttamente dal file.

 Ritorna:
    0  se tutti gli utenti sono caricati correttamente.
    -1 in caso di errore (riga malformata o inserimento fallito).

 Side-effect:
    - Alloca memoria per i nuovi utenti inseriti nella tabella hash.
 */
int prendi_utenti_da_file(FILE *fp, ptr_hash_utenti utente) {
    char riga[LUNGHEZZA_RIGA];  

    while (fgets(riga, sizeof(riga), fp)) {
        // rimuovi newline finale
        riga[strcspn(riga, "\n")] = 0;

        char *nome = strtok(riga, " ");
        char *email = strtok(NULL, " ");

        if (nome && email) {
            ptr_utente ut = inizia_utente(nome, email);
            if(!inserisci_utente_in_hash(utente, ut)) 
            return -1;
        } else 
            return -1;
        
    }

    return 0;
}


/*
 Funzione: prendi_veicolo_da_file
 ---------------------------------

 Legge i dati dei veicoli da un file e li inserisce nella tabella hash veicoli.

 Implementazione:
    - Legge ogni riga del file specificato.
    - Divide la riga in quattro token: marca, modello, targa e posizione.
    - Per ogni riga valida, crea un nuovo veicolo e lo inserisce nella hash.
    - In caso di righe non valide o errori d’inserimento, restituisce errore.

 Parametri:
    fp: puntatore al file da cui leggere i dati dei veicoli.
    veicolo: puntatore alla tabella hash in cui inserire i veicoli.

 Pre-condizioni:
    - Il file deve essere già aperto in lettura.
    - La tabella hash deve essere già allocata e inizializzata.
    - Ogni riga del file deve essere nel formato: "<marca> <modello> <targa> <posizione>".

 Post-condizioni:
    - La tabella hash contiene tutti i veicoli caricati correttamente dal file.

 Ritorna:
    0  se tutti i veicoli sono caricati correttamente.
    -1 in caso di errore (riga malformata o inserimento fallito).

 Side-effect:
    - Alloca memoria per i nuovi veicoli inseriti nella tabella hash.
 */
int prendi_veicolo_da_file(FILE *fp, ptr_hash_veicoli veicolo) {
    char riga[LUNGHEZZA_RIGA];  

    while (fgets(riga, sizeof(riga), fp)) {
        // rimuovi newline finale
        riga[strcspn(riga, "\n")] = 0;

        char *marca = strtok(riga, " ");
        char *modello = strtok(NULL, " ");
        char *targa = strtok(NULL, " ");
        char *posizione = strtok(NULL, " ");

        if (marca && modello && targa && posizione) {
            ptr_veicolo ve = inizia_veicolo(marca, modello, targa, posizione);
            if(!inserisci_veicolo_in_hash(veicolo, ve)) 
            return -1;
        } else 
            return -1;
        
    }

    return 0;
}


/*
 Funzione: test_funzione1
 -------------------------

 Esegue i test per la funzione calcola_costo_noleggio leggendo i dati di input,
 confrontando i risultati ottenuti con i valori attesi (oracle), e scrivendo l'output.

 Implementazione:
    - Apre i file di input, oracle e output.
    - Legge i valori di input (inizio, fine, sconto) e il risultato atteso (oracle).
    - Calcola il costo utilizzando calcola_costo_noleggio.
    - Scrive l’output ottenuto su file.
    - Confronta il risultato ottenuto con quello atteso, tenendo conto dello scarto ammesso.
    - Conta il numero di test falliti.
    - Chiude i file aperti.

 Parametri:
    nessuno

 Pre-condizioni:
    - Devono essere presenti i file: "TC1/input.txt", "TC1/oracle.txt".
    - I file devono essere ben formattati: ogni riga di input deve contenere 3 interi (inizio, fine, sconto), 
      e ogni riga dell’oracle deve contenere un float (valore atteso).

 Post-condizioni:
    - Viene generato il file "TC1/output.txt" contenente i risultati dei test eseguiti.

 Ritorna:
    numero di test falliti (0 se tutti i test sono superati);
    -1 in caso di errore nell'apertura dei file.

 Side-effect:
    - Stampa su standard output eventuali errori di confronto.
    - Scrive il file "TC1/output.txt".
 */
int test_funzione1(void) {
    FILE *in = fopen("TC1/input.txt", "r");
    FILE *oracle = fopen("TC1/oracle.txt", "r");
    FILE *out = fopen("TC1/output.txt", "w");
    if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per funzione 1\n");
        return -1;
    }

    int inizio, fine, sconto;
    float atteso, ottenuto;
    int test_num = 1, errori = 0;

    while (fscanf(in, "%d %d %d", &inizio, &fine, &sconto) == 3 &&
           fscanf(oracle, "%f", &atteso) == 1) {
        ottenuto = calcola_costo_noleggio(inizio, fine, sconto);
        fprintf(out, "%.2f\n", ottenuto);

        if (fabs(atteso - ottenuto) > SCARTO) {
            printf("[Funzione1] Test %d FALLITO: atteso %.2f, ottenuto %.2f\n", test_num, atteso, ottenuto);
            errori++;
        }
        test_num++;
    }
    fclose(in);
    fclose(oracle);
    fclose(out);
    return errori;
}



/*
 Funzione: test_funzione2
 -------------------------

 Esegue i test relativi alle funzioni di prenotazione e verifica disponibilità veicoli.
Legge i dati di input dal file di test, effettua le operazioni richieste, scrive i risultati su file,
e confronta l'output ottenuto con l'oracle.

 Implementazione:
    - Apre i file "TC2/input.txt", "TC2/oracle.txt", "TC2/output.txt".
    - Per ogni riga di input, legge la targa, l'intervallo di prenotazione (inizio, fine).
    - Recupera il veicolo corrispondente dalla hash.
    - Prenota l'intervallo specificato e verifica la disponibilità attuale del veicolo.
    - Scrive l'esito della prenotazione e della disponibilità su "output.txt".
    - Dopo aver terminato l'elaborazione, confronta l'output generato con l'oracle.
    - Restituisce l'esito del test.

 Parametri:
    hash_veicoli: puntatore alla tabella hash contenente i veicoli.
    hash_utenti:  puntatore alla tabella hash contenente gli utenti (non utilizzato in questa funzione ma mantenuto per coerenza con il prototipo generale dei test).

 Pre-condizioni:
    - I file di test "TC2/input.txt" e "TC2/oracle.txt" devono esistere e rispettare il formato:
        input.txt: <targa> <cella_inizio> <cella_fine>
        oracle.txt: due stringhe TRUE/FALSE separate da spazio su ogni riga.
    - Le tabelle hash devono essere già caricate e inizializzate.

 Post-condizioni:
    - Viene generato il file "TC2/output.txt" contenente i risultati dei test.

 Ritorna:
    1  se tutti i test sono superati (output coincide con oracle).
    0  se almeno un test fallisce.
    -1 in caso di errore nell’apertura dei file o mancata corrispondenza di targa.

 Side-effect:
    - Scrive su "TC2/output.txt" i risultati ottenuti.
    - Eventuali messaggi di errore vengono stampati su stderr.
 */
int test_funzione2(ptr_hash_veicoli hash_veicoli, ptr_hash_utenti hash_utenti) {
    //Apre gli opportuni file nella cartella TC2
    FILE *in = fopen("TC2/input.txt", "r");
    FILE *oracle = fopen("TC2/oracle.txt", "r");
    FILE *out = fopen("TC2/output.txt", "w");
    if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per TC2\n");
        return -1;
    }

    char riga[LUNGHEZZA_RIGA];
    //Itera fino alla fine del file 'input.txt'e legge una riga alla volta
    while (fgets(riga, sizeof(riga), in)) {
        riga[strcspn(riga, "\n")] = 0;

       /*Legge dal file 'input.txt' la frase scritta nel formato targa cella_inizio cella_fine,
        ad ogni spazio si ferma e salva nella corrispettiva variabile*/
        char *targa = strtok (riga, " ");
        char *cella_inizio = strtok (NULL, " ");
        char *cella_fine = strtok (NULL, " ");
        

        //Conversione da chat a intero
        int inizio = atoi(cella_inizio);
        int fine = atoi (cella_fine);

        ptr_veicolo ve = cerca_veicolo_in_hash(hash_veicoli, targa);
        if(ve == NULL){
            fclose(in);
            fclose(oracle);
            fclose(out);
            return -1;
        }

        //Crea una prenotazione
        ptr_prenotazione pren = prendi_prenotazioni(ve);

        //Prenota le celle di un veicolo e vede e se è disponibile o no nella giornata di oggi
        int risultato_prenotazione = prenota_intervallo(pren, inizio, fine);
        bool disponibile = veicolo_disponibile_oggi(pren);
       


        /*Scrive nel file 'output.txt' TRUE/FALSE se la prenotazione va a buon fine 
        e dopo scrive TRUE/FALSE se il veicolo ha almeno una cella disponbile*/
        fprintf(out, "%s %s\n", risultato_prenotazione ? "TRUE" : "FALSE", disponibile ? "TRUE" : "FALSE");

    }

    fclose(in);
    fclose(out);

    // Ora confronto output.txt con oracle.txt
    out = fopen("TC2/output.txt", "r");
    if (!out) {
        fclose(oracle);
        return -1;
    }

    char linea_oracle[10], linea_output[10];
    while (fgets(linea_oracle, sizeof(linea_oracle), oracle) &&
           fgets(linea_output, sizeof(linea_output), out)) {
        // Rimuovi newline per confronto robusto
        linea_oracle[strcspn(linea_oracle, "\n")] = 0;
        linea_output[strcspn(linea_output, "\n")] = 0;

        if (strcmp(linea_oracle, linea_output) != 0) {
            fclose(oracle);
            fclose(out);
            return 0; // Test fallito
        }
    }

    fclose(oracle);
    fclose(out);
    return 1; // Test superato
}


/*
 Funzione: test_funzione3
 -------------------------

 Esegue i test relativi alla gestione dello storico dei noleggi.
Carica i dati di input, popola la lista dei noleggi, salva su file di output, e confronta il risultato con l'oracle.

 Implementazione:
    - Apre i file "TC3/input.txt", "TC3/oracle.txt", "TC3/output.txt".
    - Legge riga per riga i dati di input relativi ai noleggi.
    - Per ogni riga:
        - Effettua il parsing dei dati separati da punto e virgola.
        - Crea un nodo storico di noleggio.
        - Inserisce il nodo nella lista storica.
    - Salva l'intera lista su file di output.
    - Dopo aver scritto il file, confronta l'output generato con il file oracle.
    - Restituisce l'esito del test.

 Parametri:
    nessuno

 Pre-condizioni:
    - Devono essere presenti i file "TC3/input.txt" e "TC3/oracle.txt".
    - Il file "input.txt" deve rispettare il seguente formato per ogni riga (campi separati da `;`):
        giorno;mese;anno;ora;minuto;tipo_veicolo;targa_veicolo;nome_file_utente;
        costo;ora_inizio;minuto_inizio;ora_fine;minuto_fine;eliminabile

 Post-condizioni:
    - Viene generato il file "TC3/output.txt" contenente la lista dei noleggi salvata.

 Ritorna:
    1  se tutti i test sono superati (output coincide con oracle).
    0  se almeno un test fallisce.
    -1 in caso di errore nell’apertura dei file.

 Side-effect:
    - Crea il file "TC3/output.txt".
    - Eventuali messaggi di errore vengono stampati su stderr.
 */
int test_funzione3() // test dello storico del noleggio
{
    FILE *in = fopen("TC3/input.txt", "r");
    FILE *oracle = fopen("TC3/oracle.txt", "r");
    FILE *out = fopen("TC3/output.txt", "w");
    if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per TC3\n");
        if(in) fclose(in);
        if(oracle) fclose(oracle);
        if(out) fclose(out);
        return -1;
    }

    ptr_lista_noleggi lista_noleggi = crea_lista_storico();

    char riga[LUNGHEZZA_RIGA];
    while (fgets(riga, sizeof(riga), in)) {
        riga[strcspn(riga, "\n")] = 0;  // rimuove il newline

        // Parsing con strtok
        char *token = strtok(riga, ";");
        if (!token) continue;  // riga vuota o malformata

        int giorno = atoi(token);
        int mese = atoi(strtok(NULL, ";"));
        int anno = atoi(strtok(NULL, ";"));
        int ora = atoi(strtok(NULL, ";"));
        int minuto = atoi(strtok(NULL, ";"));
        char tipo_veicolo[50];
        strcpy(tipo_veicolo, strtok(NULL, ";"));
        char targa_veicolo[8];
        strcpy(targa_veicolo, strtok(NULL, ";"));
        char nome_file_utente[50];
        strcpy(nome_file_utente, strtok(NULL, ";"));
        float costo = atof(strtok(NULL, ";"));
        int ora_inizio = atoi(strtok(NULL, ";"));
        int minuto_inizio = atoi(strtok(NULL, ";"));
        int ora_fine = atoi(strtok(NULL, ";"));
        int minuto_fine = atoi(strtok(NULL, ";"));
        int eliminabile = atoi(strtok(NULL, ";"));

        // Creazione nodo
        ptr_storico pren = inizia_storico_noleggio(
            giorno, mese, anno, ora, minuto, tipo_veicolo, targa_veicolo,
            nome_file_utente, costo, ora_inizio, minuto_inizio, ora_fine, minuto_fine
        );
        if (pren) {
            inserisci_nodo_storico_noleggio(lista_noleggi, pren, eliminabile);
        }
    }

    // Salvataggio della lista su file
    salva_lista_storico_noleggio_su_file(lista_noleggi, "output", "TC3");

    fclose(in);
    fclose(out);

    // Ora confronto output.txt con oracle.txt
    out = fopen("TC3/output.txt", "r");
    if (!out) {
        fclose(oracle);
        return -1;
    }

    char linea_oracle[500], linea_output[500];
    while (fgets(linea_oracle, sizeof(linea_oracle), oracle) &&
           fgets(linea_output, sizeof(linea_output), out)) {
        linea_oracle[strcspn(linea_oracle, "\n")] = 0;
        linea_output[strcspn(linea_output, "\n")] = 0;

        if (strcmp(linea_oracle, linea_output) != 0) {
            fclose(oracle);
            fclose(out);
            return 0; // Test fallito
        }
    }

    fclose(oracle);
    fclose(out);
    return 1; // Test superato
}




/*
 Funzione: rstrip
 -----------------

 Rimuove i caratteri finali indesiderati da una stringa, quali newline ('\n'), ritorno carrello ('\r'),
 spazi (' ') e tabulazioni ('\t').

 Implementazione:
    - Calcola la lunghezza della stringa.
    - Scorre all’indietro la stringa finché trova uno dei caratteri da rimuovere.
    - Ad ogni carattere da rimuovere, decrementa l’indice e termina la stringa con '\0'.

 Parametri:
    s: puntatore alla stringa da elaborare (char *).

 Pre-condizioni:
    - Il puntatore `s` deve essere valido e puntare a una stringa terminata da '\0'.

 Post-condizioni:
    - La stringa `s` viene modificata in-place, rimuovendo i caratteri finali specificati.

 Ritorna:
    - Nessun valore di ritorno (void).

 Side-effect:
    - Modifica il contenuto della stringa passata come parametro.
 */
static void rstrip(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t')) {
        s[--n] = '\0';
    }
}


/*
 Funzione: confronta_file
 -------------------------

 Confronta riga per riga due file di testo per verificarne l'uguaglianza.

 Implementazione:
    - Legge riga per riga da entrambi i file simultaneamente.
    - Rimuove eventuali caratteri di fine riga o spazi finali tramite `rstrip`.
    - Confronta le righe, se diverse stampa un messaggio di errore con la riga e termina.
    - Se uno dei file termina prima dell'altro, segnala differenza di lunghezza.
    - Se tutti i confronti vanno a buon fine, restituisce 1.

 Parametri:
    a: puntatore al primo file aperto in lettura.
    b: puntatore al secondo file aperto in lettura.

 Pre-condizioni:
    - I puntatori `a` e `b` devono essere validi e puntare a file aperti in modalità lettura.

 Post-condizioni:
    - Nessuna modifica ai file.

 Ritorna:
    - 1 se i file sono uguali riga per riga (ignorando spazi finali e newline).
    - 0 se i file differiscono in contenuto o lunghezza.

 Side-effect:
    - Stampa su stderr il motivo della differenza (riga e contenuto).
 */
int confronta_file(FILE *a, FILE *b) {
    char linea_a[MAX_LINE];
    char linea_b[MAX_LINE];
    int line_num = 1;

    while (true) {
        char *pa = fgets(linea_a, sizeof(linea_a), a);
        char *pb = fgets(linea_b, sizeof(linea_b), b);

        if (!pa || !pb) {
            // Se uno finisce prima, i file differiscono
            if (pa != pb) {
                fprintf(stderr, "I file hanno lunghezze diverse (riga %d)\n", line_num);
                return 0;
            }
            break;
        }

        rstrip(linea_a);
        rstrip(linea_b);

        if (strcmp(linea_a, linea_b) != 0) {
            fprintf(stderr, "Differenza alla riga %d:\n  A: \"%s\"\n  B: \"%s\"\n",
                    line_num, linea_a, linea_b);
            return 0; // Test non superato
        }
        line_num++;
    }

    return 1; // Test superato
}



    