#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "ADT_array/array_prenotazione.h"
#include "utili/utile_array_prenotazione.h"
#include "utili/utile.h"

#define SCARTO 0.01 //Errore del costo

int test_funzione1(const char *input_file, const char *oracle_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *oracle = fopen(oracle_file, "r");
    FILE *out = fopen(output_file, "w");
    if (!in || !oracle || !out) {
        fprintf(stderr, "Errore apertura file per funzione 1\n");
        return -1;
    }
    int inizio, fine, sconto;
    float atteso, attuale;
    int test_num = 1, errori = 0;
    while (fscanf(in, "%d %d %d", &inizio, &fine, &sconto) == 3 &&
           fscanf(oracle, "%f", &atteso) == 1) {
        attuale = calcola_costo_noleggio(inizio, fine, sconto);
        fprintf(out, "%.2f\n", attuale);
        if (fabs(atteso - attuale) > SCARTO) {
            printf("[Funzione1] Test %d FALLITO: atteso %.2f, ottenuto %.2f\n", test_num, atteso, attuale);
            errori++;
        }
        test_num++;
    }
    fclose(in);
    fclose(oracle);
    fclose(out);
    return errori;
}


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

int test_funzione1(const char *input_file, const char *oracle_file, const char *output_file){

}


int main() {
    int err1 = test_funzione1("input1.txt", "oracle1.txt", "output1.txt");
    int err2 = test_funzione2("input2.txt", "oracle2.txt", "output2.txt");
    int err3 = test_funzione3("input3.txt", "oracle3.txt", "output3.txt");

    FILE *result = fopen("result.txt", "w");
    if (!result) {
        fprintf(stderr, "Errore apertura file result.txt\n");
        return 1;
    }

    fprintf(result, "TC1 %s\n", (err1 == 0) ? "PASS" : "FAIL");
    fprintf(result, "TC2 %s\n", (err2 == 0) ? "PASS" : "FAIL");
    fprintf(result, "TC3 %s\n", (err3 == 0) ? "PASS" : "FAIL");

    fclose(result);

    int errori_totali = 0;
    if (err1 >= 0) errori_totali += err1;
    if (err2 >= 0) errori_totali += err2;
    if (err3 >= 0) errori_totali += err3;

    if (errori_totali == 0) {
        printf("Tutti i test superati con successo.\n");
    } else {
        printf("Test falliti in totale: %d\n", errori_totali);
    }

    return 0;
}
