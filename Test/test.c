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
#include <ctype.h>


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

    if (!ts || !file_utenti || !file_veicoli || !file_result) {
    if (!ts) printf("Errore apertura file %s\n", test_suite);
    if (!file_utenti) printf("Errore apertura file %s\n", file_utente);
    if (!file_veicoli) printf("Errore apertura file %s\n", file_veicolo);
    if (!file_result) printf("Errore apertura file result.txt\n");

    if (ts) fclose(ts);
    if (file_utenti) fclose(file_utenti);
    if (file_veicoli) fclose(file_veicoli);
    if (file_result) fclose(file_result);
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
    // Rimuove newline (\n), carriage return (\r), e spazi finali
    test_case[strcspn(test_case, "\r\n")] = 0;
    while (strlen(test_case) > 0 && isspace((unsigned char)test_case[strlen(test_case) - 1])) {
        test_case[strlen(test_case) - 1] = 0;
    }

    // Estrae il nome del test case in modo sicuro
    char tc_nome[CONTENITORE] = {0};
    sscanf(test_case, "%s", tc_nome); // estrae la prima parola ignorando spazi

    int risultato = -1;

    if (strcmp(tc_nome, "TC1") == 0) {
        risultato = test_funzione1();
        if (risultato < 0) {
            printf("Errore TC1\n");
            continue;
        }
    } else if (strcmp(tc_nome, "TC2") == 0) {
        risultato = test_funzione2(hash_veicoli, hash_utenti);
        if (risultato < 0) {
            printf("Errore TC2\n");
            continue;
        }
    } else if (strcmp(tc_nome, "TC3") == 0) {
        risultato = test_funzione3();
        if (risultato < 0) {
            printf("Errore TC3\n");
            continue;
        }
    } else {
        printf("Test case non riconosciuto: '%s'\n", tc_nome);
        continue;
    }

    // Costruzione path file
    char file_oracle[CONTENITORE];
    snprintf(file_oracle, CONTENITORE, "%s/oracle.txt", tc_nome);

    char file_output[CONTENITORE];
    snprintf(file_output, CONTENITORE, "%s/output.txt", tc_nome);

    FILE *oracle_file = fopen(file_oracle, "r");
    FILE *output_file = fopen(file_output, "r");

    if (!oracle_file) {
        printf("Errore apertura file %s\n", file_oracle);
    }
    if (!output_file) {
        printf("Errore apertura file %s\n", file_output);
    }

    if (!oracle_file || !output_file) {
        if (oracle_file) fclose(oracle_file);
        if (output_file) fclose(output_file);
        continue;
    }

    int confronto = confronta_file(oracle_file, output_file);

    fprintf(file_result, "%s: %s\n", tc_nome, confronto ? "PASS" : "FAIL");
    fflush(file_result); // Scrive immediatamente nel file

    fclose(oracle_file);
    fclose(output_file);
}


    
    distruggi_hash_utenti(hash_utenti);
    distruggi_hash_veicoli(hash_veicoli);
    fclose(ts);
    fclose(file_veicoli);
    fclose(file_utenti);
    fclose(file_result);


    printf("\n\nFino a qui arrivo--------------------");
    return 0;
}




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



int test_funzione1(void) {
    printf("\nFunzione 3 chiamata");
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




int test_funzione2(ptr_hash_veicoli hash_veicoli, ptr_hash_utenti hash_utenti) {
    printf("\nFunzione 2 chiamata");
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


int test_funzione3() // test dello storico del noleggio
{
      printf("\nFunzione 3 chiamata");
      FILE *in = fopen("TC3/input.txt", "r");
      FILE *oracle = fopen("TC3/oracle.txt", "r");
      FILE *out = fopen("TC3/output.txt", "w");
      if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per TC2\n");
        return -1;
    }

    ptr_lista_noleggi lista_noleggi = crea_lista_storico();
    
    int giorno, mese, anno, ora, minuto, ora_inizio, minuto_inizio, ora_fine, minuto_fine;
    float costo;
    char tipo_veicolo[50], targa_veicolo[8], nome_file_utente[50];
    int eliminabile;
     while (fscanf(in, "%d;%d;%d;%d;%d;%49[^;];%7[^;];%49[^;];%f;%d;%d;%d;%d;%d\n",
                  &giorno, &mese, &anno, &ora, &minuto,
                  tipo_veicolo, targa_veicolo, nome_file_utente,
                  &costo, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine, &eliminabile) == 14){

                ptr_storico pren = inizia_storico_noleggio(giorno, mese, anno, ora, minuto, tipo_veicolo, targa_veicolo, nome_file_utente, costo, ora_inizio, minuto_inizio, ora_fine, minuto_fine);
                if(pren){
                inserisci_nodo_storico_noleggio(lista_noleggi, pren, eliminabile);

                  }
                }
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
        // Rimuovi newline per confronto robusto
        linea_oracle[strcspn(linea_oracle, "\n")] = 0;
        linea_output[strcspn(linea_output, "\n")] = 0;

        if (strcmp(linea_oracle, linea_output) != 0) {
            fclose(oracle);
            fclose(out);
            return 0; // Test fallito
        }
    }
    printf("\nFunzione 3 test superato");
    fclose(oracle);
    fclose(out);
    return 1; // Test superato

    
}






// Rimuove newline e spazi finali
static void rstrip(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t')) {
        s[--n] = '\0';
    }
}

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



    