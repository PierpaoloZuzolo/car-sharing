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


#include "ADT_array/array_prenotazione.h"
#include "utili/utile_array_prenotazione.h"
#include "utili/utile.h"
#include "Modello_veicolo/veicolo.h"
#include "utili/utile_veicolo.h"
#include "Modello_storico_noleggio/storico_noleggio.h"
#include "ADT_array/array.h"
#include "ADT_hash/hash_veicoli.h"
#include "ADT_hash/tab_hash.h"

#define SCARTO 0.01 //Errore del costo

int test_funzione1();
//int test_funzione2();
//int test_funzione3(const char *input_file, const char *oracle_file, const char *output_file);


int main() {
    FILE *suite = fopen("test_suite.txt", "r");
    FILE *result = fopen("result.txt", "w");
    if (!suite || !result) {
        fprintf(stderr, "Errore apertura file test_suite.txt o result.txt\n");
        return 1;
    }

    char test_case[100];
    while (fgets(test_case, sizeof(test_case), suite)) {
        test_case[strcspn(test_case, "\r\n")] = 0;


       
        int es1 = test_funzione1();
        
//printf("Input: %s\nOracle: %s\nOutput: %s\n", input_file, oracle_file, output_file);

        
        int es2 = test_funzione2();

        
//printf("Input: %s\nOracle: %s\nOutput: %s\n", input_file, oracle_file, output_file);

        if (es1 == 0 /*&& es2 == 0*/) {
            fprintf(result, "%s PASS\n", test_case);
        } else {
            fprintf(result, "%s FAIL\n", test_case);
        }
    }

    fclose(suite);
    fclose(result);

    printf("Test eseguiti. Vedi result.txt\n");
    return 0;
}



int test_funzione1() {
    FILE *in = fopen("TC1/input.txt", "r");
    FILE *oracle = fopen("TC1/oracle.txt", "r");
    FILE *out = fopen("TC1/output.txt", "w");
    if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per TC1\n");
        return -1;
    }

    int inizio, fine, sconto;
    float atteso, ottenuto;
    int test_num = 1, errori = 0;

    while (fscanf(in, "%d %d %d", &inizio, &fine, &sconto) == 3 &&
           fscanf(oracle, "%f", &atteso) == 1) {
            
//printf("Apro %s, %s, %s\n", input_file, oracle_file, output_file);

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
// Funzione di test per prenotazione e aggiornamento disponibilità
int test_funzione2(void) {
    FILE *input = fopen("TC2/input.txt", "r");
    FILE *oracle = fopen("TC2/oracle.txt", "r");
    FILE *output = fopen("TC2/output.txt", "w");

    if (!input || !oracle || !output) {
        fprintf(stderr, "Errore apertura file in TC2\n");
        return 1;
    }

    // Inizializza un veicolo fittizio
    ptr_veicolo ve = inizia_veicolo("Fiat", "Panda", "AA000BB", "Roma");
    ptr_prenotazione p = prendi_prenotazioni(ve);

    int inizio, fine;
    char stato_atteso[20];

    int test_num = 1;
    int errori = 0;

    while (fscanf(input, "%d %d", &inizio, &fine) == 2 && fscanf(oracle, "%s", stato_atteso) == 1) {
        
//printf("Apro %s, %s, %s\n", input_file, oracle_file, output_file);

        int esito = prenota_intervallo(p, inizio, fine);

        // Aggiorna lo stato del veicolo (senza bloccare celle passate)
        aggiorna_stato_veicolo(ve);

        const char *stato_ottenuto = prendi_stato(ve);

        fprintf(output, "Prenotazione %d: %s (atteso: %s, ottenuto: %s)\n",
                test_num,
                strcmp(stato_atteso, stato_ottenuto) == 0 ? "PASS" : "FAIL",
                stato_atteso,
                stato_ottenuto);

        if (strcmp(stato_atteso, stato_ottenuto) != 0) {
            errori++;
        }

        test_num++;
    }

    fclose(input);
    fclose(oracle);
    fclose(output);
    distruggi_array_prenotazioni(p);
    libera_veicolo(ve);

    return errori == 0 ? 0 : 1;
}
*/




/*
int test_funzione3(const char *input_file, const char *oracle_file, const char *output_file) {
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
}

*/