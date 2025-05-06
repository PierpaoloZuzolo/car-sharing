#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prenotazione.h"
#include "utente.h" 
#include "utile.h"


typedef struct prenotazione{
    char nome[MAX_NOME + 1];
    char cognome[MAX_COGNOME +1];
    char mail[MAIL + 1];
    time_t inizio;
    time_t fine;
    float costo;
    struct prenotazione* prossimo;

} prenotazione;

time_t creazione_data() {

    struct tm tm_inizio = {0};
    int mese, giorno, anno, ora, minuto;

    printf("Inserisci il mese (1-12): \n");
    scanf("%d", &mese);
    tm_inizio.tm_mon = mese - 1;
    
    printf("Inserisci il giorno (1-31): \n");
    scanf("%d", &giorno);
    tm_inizio.tm_mday = giorno;
    
    printf("Inserisci l'anno (es. 2025): \n");
    scanf("%d", &anno);
    tm_inizio.tm_year = anno - 1900; 
    
    printf("Inserisci l'ora (0-23): \n");
    scanf("%d", &ora);
    tm_inizio.tm_hour = ora;
    
    printf("Inserisci i minuti (0-59): \n");
    scanf("%d", &minuto);
    tm_inizio.tm_min = minuto;

    return mktime(&tm_inizio);
}

int giorni_festivi(struct tm* tm_attuale){
    int mese = tm_attuale->tm_mon, giorno = tm_attuale->tm_mday;

    if(((giorno == 1 || giorno == 6) && mese == 0) ||    //01/01 06/01
        (giorno == 25 && mese == 3) ||  //25/04
        (giorno == 1 && mese == 4) ||   //01/05
        (giorno == 2 && mese == 5) ||   //02/06
        (giorno == 15 && mese == 7) ||  //15/08
        (giorno == 1 && mese == 10) ||  //01/10
        ((giorno == 8 || giorno == 25 || giorno == 26 ) && mese == 11)) { //08-25-26/12
        return 1;
    }

    return 0;
}

int orario_sconto(struct tm* tm_attuale){   

    int ora= tm_attuale->tm_hour;
    
    if((ora >= 3 && ora <= 6) || 
       (ora >= 13 && ora <= 15) ){
        return 1;
    }

    return 0;
}

float costo_noleggio(int ora_utilizzo, time_t inizio) {
    
    time_t tempo_corrente = inizio;

    float prezzo_noleggio = 0.0;

    for(int i = 0; i < ora_utilizzo; i++){
        struct tm* tm_corrente= localtime(&tempo_corrente);

        if(giorni_festivi(tm_corrente)){
            prezzo_noleggio+=25;
        }

        else if(orario_sconto(tm_corrente)){
            prezzo_noleggio+=7.5;
        }

        else{
            prezzo_noleggio+=15;
        }

        tempo_corrente += 3600;
    }
    printf("[TOTALE] - prezzo noleggio = %.01f€", prezzo_noleggio);
    return prezzo_noleggio;
}

void informazioni_costo_noleggio(int ora_utilizzo, time_t inizio){

    printf("\n");
    printf("NOTA BENE: i prezzi possono variare nel corso del tempo!\n");
    printf("In caso di mancato utilizzo del veicolo da parte dell’utente, nonostante il pagamento già effettuato, non è previsto alcun rimborso!\n");
    printf("\n");
    printf("=================== DESCRIZIONE PREZZI NOLEGGIO ===================\n");
    printf("\n");
    printf("1. Prezzo standard (15€/h):\n");
    printf("-In fasce di orari senza sconti e non festivi\n");

    printf("\n");
    printf("2. Prezzo scontato (7.5€/h):\n");
    printf("-tra le 3.00 e le 6.00 (fascia mattutina)\n");
    printf("-tra le 13.00 e le 15.00 (fascia pomeridiana)\n");

    printf("\n");
    printf("3. Prezzo festivo (25€/h):\n");
    printf("- 01 Gennaio (Capodanno)\n");
    printf("- 06 Gennaio (Epifania)\n");
    printf("- 25 Aprile (Festa della Liberazione)\n");
    printf("- 01 Maggio (Festa del Lavoro)\n");
    printf("- 02 Giugno (Festa della Repubblica)\n");
    printf("- 15 Agosto (Ferragosto)\n");
    printf("- 01 Novembre (Tutti i Santi)\n");
    printf("- 08 Dicembre (Immacolata Concezione)\n");
    printf("- 25 Dicembre (Natale)\n");
    printf("- 26 Dicembre (Santo Stefano)\n");
    printf("\n");
    printf("========================================================================\n");
    printf("\n");

    char scelta[10];

    printf("Vuoi fare un preventivo? (SI/NO)\n");
    scanf("%s, scelta");

    if(strcmp(scelta,"SI") == 0 || strcmp(scelta,"Si") == 0 || strcmp(scelta,"si") == 0){
        time_t inzio;
        int ora_utilizzo;

        printf("Inserisci la data di inizio: \n");
        inzio=creazione_data();

        printf("Inserisci le ore di utilizzo: \n");
        scanf("%d", &ora_utilizzo);
        
        float prezzo_noleggio=costo_noleggio(ora_utilizzo, inizio);
        
        printf("\n");
        printf("Vuoi proseguire con la prenotazione?\n");
        scanf("%s, scelta");

        if(strcmp(scelta,"SI") == 0 || strcmp(scelta,"Si") == 0 || strcmp(scelta,"si") == 0){

        }

        else{
            printf("Hai deciso di non continuare!\n");
        }
    }

    else{
        printf("Hai deciso di non continuare!\n");
    }

}

void stampa_data (time_t inizio_fine){
    struct tm* tm_inizio = localtime(&inizio_fine);  
    
    printf("Data e ora: %02d/%02d/%04d %02d:%02d\n", tm_inizio->tm_mday, tm_inizio->tm_mon + 1, tm_inizio->tm_year + 1900, 
                                                     tm_inizio->tm_hour, tm_inizio->tm_min);

}

void controllo_prenotazione(PRENOTAZIONE richiesta){
    if(richiesta==NULL){
        printf("Non è stata inserita nessuna prenotazione!");
        exit(-1);
    }

    time_t adesso = time(NULL);
    struct tm* tm_inizio = localtime(&adesso);

    char accettazione[9];

    printf("\n");
    printf("=======================================\n");
    printf("           DETTAGLI PRENOTAZIONE       \n");
    printf("=======================================\n");
    printf("-Nome:       %s\n", richiesta->nome);
    printf("-Cognome:    %s\n", richiesta->cognome);
    printf("-Mail:       %s\n", richiesta->mail);
    printf("                  INIZIO               \n");
    stampa_data(richiesta->inizio);
    printf("                   FINE                \n");
    stampa_data(richiesta->fine);
    printf("---------------PREZZO------------------\n");
    printf("-Costo:      %.2f€\n", richiesta->costo);
    printf("=======================================\n");
    printf("PREGO, CONFERMARE I DATI (scrivi CONTINUA o INDIETRO)\n");

    scanf("%s", &accettazione);
    if(strcmp(accettazione, "INDIETRO") == 0 || strcmp(accettazione, "Indietro") == 0 || strcmp(accettazione, "indietro") == 0){
        free (richiesta);
        printf("Prenotazione annullata.\n");
    }

    if(strcmp(accettazione, "CONTINUA") == 0 || strcmp(accettazione, "Continua") == 0 || strcmp(accettazione, "continua") == 0){
        printf("Prenotazione andata a buon fine.\n");
    }
}