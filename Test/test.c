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
#include "Modello_storico_noleggio/storico_noleggio.h"

#define SCARTO 0.01 //Errore del costo


int test_funzione1(const char*, const char*, const char*);
int test_funzione2(const char*, const char*, const char*);
int test_funzione3(const char *input_file, const char *oracle_file, const char *output_file);

int main() {
    FILE *suite = fopen("test_suite.txt", "r");
    FILE *result = fopen("result.txt", "w");
    if (!suite || !result) {
        fprintf(stderr, "Errore apertura file test_suite.txt o result.txt\n");
        return 1;
    }

    char test_case[100];
    while (fgets(test_case, sizeof(test_case), suite)) {
        test_case[strcspn(test_case, "\n")] = 0; // rimuove newline

        // Prepara i nomi file
        char input_file[150], oracle_file[150], output_file[150];
        snprintf(input_file, sizeof(input_file), "%s/input.txt", test_case);
        snprintf(oracle_file, sizeof(oracle_file), "%s/oracle.txt", test_case);

        // Chiamo tutte le tre funzioni di test
        // Per output nomi distinti (così non si sovrascrivono)
        snprintf(output_file, sizeof(output_file), "%s/output.txt", test_case);
        int es1 = test_funzione1(input_file, oracle_file, output_file);
/*
        snprintf(output_file, sizeof(output_file), "%s/output.txt", test_case);
        int es2 = test_funzione2(input_file, oracle_file, output_file);

        snprintf(output_file, sizeof(output_file), "%s/output.txt", test_case);
        int es3 = test_funzione3(input_file, oracle_file, output_file);

        if (es1 == 0 && es2 == 0 && es3 == 0) {
            fprintf(result, "%s PASS\n", test_case);
        } else {
            fprintf(result, "%s FAIL\n", test_case);
        }*/
       if(es1 == 0){
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




int test_funzione1(const char *input_file, const char *oracle_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *oracle = fopen(oracle_file, "r");
    FILE *out = fopen(output_file, "w");
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
int test_funzione2(const char *file_input, const char *file_oracolo, const char *file_output) {
    FILE *input = fopen(file_input, "r");
    FILE *oracolo = fopen(file_oracolo, "r");
    FILE *output = fopen(file_output, "w");
    if (!input || !oracolo || !output) {
        fprintf(stderr, "Errore apertura file per funzione 2\n");
        return -1;
    }

    ptr_prenotazione prenotazioni = inizializza_prenotazioni();
    if (!prenotazioni) {
        fprintf(stderr, "Errore allocazione struttura prenotazioni\n");
        fclose(input); fclose(oracolo); fclose(output);
        return -1;
    }

    int inizio_slot, fine_slot;
    int numero_test = 1, numero_errori = 0;
    char riga_attesa[1024], riga_ottenuta[1024];

    while (fscanf(input, "%d %d", &inizio_slot, &fine_slot) == 2) {
        int risultato = prenota_intervallo(prenotazioni, inizio_slot, fine_slot);
        fprintf(output, "Prenotazione %d: %s\n", numero_test, risultato ? "OK" : "FALLITA");

        // Redirigi stdout su file temporaneo
        FILE *file_temporaneo = tmpfile();
        if (!file_temporaneo) {
            fprintf(stderr, "Errore nella creazione del file temporaneo\n");
            break;
        }

        // Salvataggio stdout corrente
        int stdout_backup = dup(fileno(stdout));
        fflush(stdout);
        dup2(fileno(file_temporaneo), fileno(stdout));

        // Chiama la funzione che stampa la disponibilità
        mostra_orari_disponibili(prenotazioni);

        // Ripristina stdout
        fflush(stdout);
        dup2(stdout_backup, fileno(stdout));
        close(stdout_backup);

        // Legge l'output generato
        rewind(file_temporaneo);
        riga_ottenuta[0] = '\0';
        while (fgets(riga_ottenuta + strlen(riga_ottenuta), sizeof(riga_ottenuta) - strlen(riga_ottenuta), file_temporaneo));

        // Legge la riga attesa dall'oracolo
        if (!fgets(riga_attesa, sizeof(riga_attesa), oracolo)) {
            printf("[Funzione2] Test %d FALLITO: riga oracolo mancante\n", numero_test);
            numero_errori++;
        } else if (strcmp(riga_ottenuta, riga_attesa) != 0) {
            printf("[Funzione2] Test %d FALLITO\nOutput ottenuto:\n%sOutput atteso:\n%s\n", numero_test, riga_ottenuta, riga_attesa);
            numero_errori++;
        }

        fclose(file_temporaneo);
        numero_test++;
    }

    fclose(input);
    fclose(oracolo);
    fclose(output);
    free(prenotazioni);
    return numero_errori;
}

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