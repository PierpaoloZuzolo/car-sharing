#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prenotazione.h" 

// Funzione che chiede all'utente di inserire una data (mese, giorno, anno, ora e minuto)
time_t creazione_data( ) {

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

    //trasforma i secondi in data
    return mktime(&tm_inizio);  
}

// Funzione che calcola il costo del noleggio secondo le ore di 
float costo_noleggio(int minuti, time_t inizio) {
    
    time_t tempo_corrente = inizio;

    float prezzo_noleggio = 0.0;

// Un ciclo che verifica il costo, ora per ora e giorno per giorno, tenendo conto degli sconti e delle festività italiane 
    for(int i = 0; i < minuti; i++){
        struct tm* tm_corrente= localtime(&tempo_corrente);

        int mese = tm_corrente->tm_mon, giorno = tm_corrente->tm_mday;

        // Prezzo secondo i giorni festivi
        if(((giorno == 1 || giorno == 6) && mese == 0) ||    //01/01 06/01
            (giorno == 25 && mese == 3) ||  //25/04
            (giorno == 1 && mese == 4) ||   //01/05
            (giorno == 2 && mese == 5) ||   //02/06
            (giorno == 15 && mese == 7) ||  //15/08
            (giorno == 1 && mese == 10) ||  //01/10
            ((giorno == 8 || giorno == 25 || giorno == 26 ) && mese == 11)){ //08/12 25/12 26/12
                prezzo_noleggio+=2;
            }

        int ora= tm_corrente->tm_hour;

        // Sconto orario
        if((ora >= 3 && ora <= 6) || 
           (ora >= 13 && ora <= 15) ){
            prezzo_noleggio+=0.19;
        }

        // Prezzo normale
        else{
            prezzo_noleggio+=0.98;
        }

        tempo_corrente += 60;
    }
    printf("[TOTALE] - prezzo noleggio = %.02f€", prezzo_noleggio);
    return prezzo_noleggio;
}

// Funzione che crea un preventivo del costo secondo le ore di utilizzo inserite da utente, tenendo conto degli sconti
void preventivo( ){

   printf("Inserisci la data di inizio: \n");
   time_t inizio=creazione_data();

   printf("Inserisci la data di fine:\n");
   time_t fine = creazione_data();
        
   int minuti = (int)((fine - inizio) % 3600) / 60;

   costo_noleggio(minuti, inizio);
}

// Funzione che stampa la data passata per input
void stampa_data (time_t data){
    struct tm* tm_inizio = localtime(&data);  
    
    printf("Data e ora: %02d/%02d/%04d %02d:%02d\n", tm_inizio->tm_mday, tm_inizio->tm_mon + 1, tm_inizio->tm_year + 1900, 
                                                     tm_inizio->tm_hour, tm_inizio->tm_min);

}

// Funzione che mostra i dati all'utente a schermo per controllare se inseriti correttamente
void controllo_prenotazione(prenotazione* richiesta){
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
    printf("-Mail:       %s\n", richiesta->email);
    printf("                  INIZIO               \n");
    stampa_data(richiesta->inizio);
    printf("                   FINE                \n");
    stampa_data(richiesta->fine);
    printf("---------------PREZZO------------------\n");
    printf("-Costo:      %.2f€\n", richiesta->costo);
    printf("=======================================\n");
    printf("PREGO, CONFERMARE I DATI (scrivi CONTINUA o INDIETRO)\n");

    scanf("%s", &accettazione);

    if(strcmp(accettazione, "CONTINUA") == 0 || strcmp(accettazione, "Continua") == 0 || strcmp(accettazione, "continua") == 0){
        printf("Prenotazione andata a buon fine.\n");
        printf("Prenda il veicolo nella seguente data:\t");
        stampa_data(richiesta->inizio);
    }

    else{
        free (richiesta);
        printf("Prenotazione annullata.\n");
    }
}

// Funzione per creare una nuova prenotazione e riempire tutti i campi attraverso l'inserimento da utente
prenotazione* creazione_prenotazione( ){
    prenotazione* nuova = malloc(sizeof(prenotazione));
    if(nuova == NULL){
        printf("Errore di allocazione di memoria!");
        exit(EXIT_FAILURE);
    }

    char nome[MASSIMO_NOME];
    printf("\nCompila la tua prenotazione!\n");
    printf("Inserisci il nome:\n");
    scanf("%s", nome);
    strncpy(nuova->nome, nome, MASSIMO_NOME);

    char cognome[MASSIMO_COGNOME];
    printf("Inserisci il cognome:\n");
    scanf("%s", cognome);
    strncpy(nuova->cognome, cognome, MASSIMO_COGNOME);
    
    char email[MASSIMO_EMAIL];
    printf("Inserisci l'email:\n");
    scanf("%s", email);
    strncpy(nuova->email, email, MASSIMO_EMAIL);

    printf("Inserisci la data di inizio:\n");
    nuova->inizio = creazione_data();

    printf("Inserisci la data di fine:\n");
    nuova->fine = creazione_data();

    // Calcolo della durata in minuti (differenza tra fine e inizio in secondi, convertita in minuti)
    int minuti = (int)((nuova->fine - nuova->inizio) / 60);     
    // Calcola il prezzo del noleggio, in base alla durata e secondo gli sconti
    nuova->costo = costo_noleggio(minuti, nuova->inizio);   

    return nuova;
}

// Funzione che mostra le informazioni riguardo il costo del noleggio, permettendo di creare un preventivo e una prenotazione
void informazioni_costo_noleggio( ){

    printf("\n");
    printf("NOTA BENE: i prezzi possono variare nel corso del tempo!\n");
    printf("In caso di mancato utilizzo del veicolo da parte dell'utente non è previsto alcun rimborso!\n");
    printf("\n");
    printf("=================== DESCRIZIONE PREZZI NOLEGGIO ===================\n");
    printf("\n");
    printf("1. Prezzo standard (0.98€/min):\n");
    printf("-In fasce di orari senza sconti e non festivi\n");

    printf("\n");
    printf("2. Prezzo scontato (0.19€/min):\n");
    printf("-tra le 3.00 e le 6.00 (fascia mattutina)\n");
    printf("-tra le 13.00 e le 15.00 (fascia pomeridiana)\n");

    printf("\n");
    printf("3. Prezzo festivo (2€/min):\n");
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

    char scelta[3];

    printf("Vuoi fare un preventivo? (SI/NO)\n");
    scanf("%s, scelta");

    if(strcmp(scelta,"SI") == 0 || strcmp(scelta,"Si") == 0 || strcmp(scelta,"si") == 0){

        //Crea il preventivo secondo i minuti di utilizzo.
        void preventivo( ); 
    
        printf("\n");
        printf("Vuoi proseguire con la prenotazione(SI/NO)?\n");
        scanf("%s, scelta");

        if(strcmp(scelta,"SI") == 0 || strcmp(scelta,"Si") == 0 || strcmp(scelta,"si") == 0){
            //crea la prenotazione con i dati inseriti dall'utente
            prenotazione* creazione_prenotazione( );
        }

        else{
            printf("Hai deciso di non continuare!\n");
        }
    }

    else{
        printf("Hai deciso di non continuare!\n");
    }

}