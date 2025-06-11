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



#define LUNGHEZZA_RIGA 600
#define CONTENITORE 1024
#define NUMERO_UTENTI 5
#define NUMERO_VEICOLI 5
#define SCARTO 0.01 //Errore del costo



int prendi_veicolo_da_file(FILE *fp, ptr_hash_veicoli utente);
int prendi_utenti_da_file(FILE *fp, ptr_hash_utenti utente);
int test_funzione1(void);
int test_funzione2(ptr_hash_veicoli);
int test_funzione3(ptr_hash_utenti,ptr_hash_veicoli);
int confronta_file(const char *file1, const char *file2);


int main(int argc, char **argv) {
    if(argc < 4){
        printf("Assicurati di mettere tutti i parametri!\n");
        return -1;
    }

    char *test_suite = argv[1];
    char *file_utente = argv[2];
    char *file_veicolo= argv[3];

    FILE *ts = fopen ("test_suite.txt", "r");
    FILE *file_utenti = fopen ("utenti.txt", "r");
    FILE *file_veicoli = fopen ("veicoli.txt", "r");
    FILE *file_result = fopen("risultato.txt", "w");

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
        errore_allocazione();
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        fclose(file_result);
        return -1;
    }
    if(carica_utenti_da_file(file_utenti, hash_utenti, NULL) < 0){
        printf("Errore caricamento utenti!\n(Controlla il formato nome email)");
        distruggi_hash_utenti(hash_utenti);
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        return -1;
    }

    ptr_hash_veicoli hash_veicoli = crea_hash_veicoli(NUMERO_VEICOLI);
    if (!hash_veicoli) {
        errore_allocazione();
        distruggi_hash_utenti(hash_utenti);
        fclose(ts);
        fclose(file_utenti);
        fclose(file_veicoli);
        fclose(file_result);
        return -1;
    }
    if(carica_veicoli_da_file(file_veicoli, hash_veicoli, NULL) == 0){
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
            if(test_funzione2(hash_veicoli) < 0){
                printf("Errore TC2\n");
                continue;
            }
        }
        if(strcmp(tc_generale, "TC3") == 0){
            if(test_funzione3(hash_utenti, hash_veicoli) < 0){
                printf("Errore TC3\n");
                continue;
            }
        }

        char file_oracle[CONTENITORE] = {0};
        snprintf(file_oracle, CONTENITORE, "%s/oracle.txt", tc_generale);

        char file_output[CONTENITORE] = {0};
        snprintf(file_output, CONTENITORE, "%s/output.txt", tc_generale);


        FILE *oracle_file = fopen(file_oracle, "r");
        FILE *output_file = fopen(file_output, "r");

        if((oracle_file == NULL) || (output_file == NULL)){
            printf("Errore apertura file oracle o output\n");
            return -1;
        }
        int risultato = confronta_file(oracle_file, output_file);
        fprintf(file_result, "%s: %sTest superato\n", tc_generale, risultato ? "NON " : "");
        fclose(oracle_file);
        fclose(output_file);
    }
    
    distruggi_hash_utenti(hash_utenti);
    distruggi_hash_veicoli(hash_veicoli);
    fclose(ts);
    fclose(file_veicoli);
    fclose(file_utenti);
    fclose(file_result);

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
    FILE *in = fopen("TC1/input", "r");
    FILE *oracle = fopen("TC1/oracle", "r");
    FILE *out = fopen("TC1/output", "w");
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




int test_funzione2(ptr_hash_veicoli veicolo) {
    FILE *in = fopen("TC2/input.txt", "r");
    FILE *oracle = fopen("TC2/oracle.txt", "r");
    FILE *out = fopen("TC2/output.txt", "w");
    if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per TC2\n");
        return -1;
    }

    char riga[LUNGHEZZA_RIGA];
    while (fgets(riga, sizeof(riga), in)) {
        riga[strcspn(riga, "\n")] = 0;

       
        char *targa = strtok (riga, " ");
        char *cella_inizio = strtok (NULL, " ");
        char *cella_fine = strtok (NULL, " ");

        ptr_veicolo ve = cerca_veicolo_in_hash(veicolo, targa);
        if(ve == NULL){
            fclose(in);
            fclose(oracle);
            fclose(out);
        }

        //Creo una prenotazione
        ptr_prenotazione pren = prendi_prenotazioni(ve);
        prenota_intervallo(pren, cella_inizio, cella_fine);


    



    }   
    

    
    // Creiamo la struttura prenotazioni per il test
    ptr_prenotazione p = inizializza_prenotazioni();
    if (!p) {
        fprintf(stderr, "Errore allocazione struttura prenotazioni\n");
        return -1;
    }

    int inizio, fine, atteso;
    int test_num = 1, errori = 0;

    while (fscanf(in, "%d %d", &inizio, &fine) == 2) {
        if (fscanf(oracle, "%d", &atteso) != 1) {
            printf("Errore: file oracle più corto rispetto all'input.\n");
            break;
        }
    
        int ottenuto = prenota_intervallo(p, inizio, fine);
        fprintf(out, "Test %d: atteso %d, ottenuto %d\n", test_num, atteso, ottenuto);

        if (ottenuto != atteso) {
            printf("[Funzione2] Test %d FALLITO: atteso %d, ottenuto %d\n", test_num, atteso, ottenuto);
            errori++;
        }
    test_num++;
    }
}





int test_funzione3(ptr_hash_veicoli hash_veicoli, ptr_hash_utenti hash_utenti) 
{
    int test1, test2;
    FILE *fout = fopen("TC£/output.txt", "w");
    if(!fout){
        printf("\nErrore apertura file output TC3");
        return 1;
    }
    
    int stdout_backup = dup(fileno(stdout)); //Salva fd stdout originale

    //reindirizza stduot su file
    dup2(fileno(fout), fileno(stdout));
    fclose(fout);

    //chiama la funzione da testare
    stampa_veicoli_disponibili(hash_veicoli);

    //ripristino di stdout
    fflush(stdout);
    dup2(stdout_backup, fileno(stdout));
    close(stdout_backup);

    //confronto output con oracolo
    if(confronta_file("TC3/output.txt", "TC3/oracle.txt")) {
        test1 = 1;
    } else {
        test1 = 0;
    }






    /*
    FILE *input = fopen(input_file, "r");
    FILE *oracle = fopen(oracle_file, "r");
    FILE *output = fopen(output_file, "w");
    if (!input || !oracle || !output) {
        fprintf(stderr, "Errore apertura file per funzione 3\n");
        if (input) fclose(input);
        if (oracle) fclose(oracle);
        if (output) fclose(output);
        return -1;
    }

    int giorno, mese, anno, ora_inizio, minuto_inizio;
    int test_num = 1;
    int errori = 0;

    while (fscanf(input, "%d %d %d %d %d", &giorno, &mese, &anno, &ora_inizio, &minuto_inizio) == 5) {
        int expected;
        if (fscanf(oracle, "%d", &expected) != 1) {
            fprintf(stderr, "Riga oracolo mancante per test %d\n", test_num);
            errori++;
            break;
        }

        // Creo la struttura storico_noleggio con valori fittizi per campi mancanti,
        // ad esempio tipo_veicolo, targa, nome utente, costo e orari di inizio/fine.
        // Puoi adattare i valori secondo i tuoi dati di test.

        ptr_storico s = inizia_storico_noleggio(
            giorno, mese, anno, ora_inizio, minuto_inizio,
            "TipoVeicolo",   // esempio stringa fittizia tipo veicolo
            "AB123CD",       // esempio targa
            "UtenteTest",    // esempio nome utente
            100.0f,          // costo fittizio
            ora_inizio, minuto_inizio,  // ora e minuto inizio
            ora_inizio + 1, 0            // ora e minuto fine (esempio)
        );

        if (!s) {
            fprintf(stderr, "Errore allocazione storico noleggio per test %d\n", test_num);
            errori++;
            break;
        }

        // Chiamo la funzione da testare
        bool risultato = vedi_se_noleggio_eliminabile(s);

        // Scrivo l'output su file
        fprintf(output, "Test %d: %s\n", test_num, risultato ? "true" : "false");

        // Confronto con l'oracolo
        if ((risultato ? 1 : 0) != expected) {
            printf("[Funzione3] Test %d FALLITO: atteso %s, ottenuto %s\n",
                   test_num,
                   expected ? "true" : "false",
                   risultato ? "true" : "false");
            errori++;
        }

        // Libero la memoria allocata per lo storico
        // (assumendo che esista una funzione per liberare ptr_storico, esempio: distruggi_storico_noleggio)
        distruggi_storico_noleggio(s);

        test_num++;
    }

    fclose(input);
    fclose(oracle);
    fclose(output);
    return errori;

*/
}

int confronta_file(const char *file1, const char *file2) {
    FILE* f1 = fopen(file1, "r");
    FILE* f2 = fopen(file2, "r");
    if (!f1 || !f2){
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 0;
    }

    int risultato = 1;
    int c1, c2;
    do{
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        if (c1 != c2) {
            risultato = 0;
            break;
        }
    } while (c1 != EOF && c2 != EOF);

    if (c1 != c2) risultato = 0;

    fclose(f1);
    fclose(f2);


    return risultato;
}
    