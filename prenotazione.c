#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prenotazione.h" 

struct prenotazione{
    char nome[MASSIMO_NOME + 1];
    char cognome[MASSIMO_COGNOME +1];
    char email[MASSIMO_EMAIL + 1];
    time_t inizio;
    time_t fine;
    float costo;
};


// Funzione che chiede all'utente di inserire una data (mese, anno e giorno)
time_t creazione_data() {
    struct tm tm_inizio={0};
    int mese, giorno, anno, ora, minuto;

    while (1) {
        printf("Inserisci l'anno (es. 2025): \n");
        scanf("%d", &anno);
        if (anno <= 2024 || anno > 2100) {
            printf("Anno non valido. Riprova.\n");
            continue;
        }

        printf("Inserisci il mese (1-12): \n");
        scanf("%d", &mese);
        if (mese < 1 || mese > 12) {
            printf("Mese non valido. Riprova.\n");
            continue;
        }

        printf("Inserisci il giorno (1-31): \n");
        scanf("%d", &giorno);
        if (giorno < 1 || giorno > 31) {
            printf("Giorno non valido. Riprova.\n");
            continue;
        }

        // Assegna alla struttura tm (mesi vanno da 0 a 11 e gli anni vengono calcolati per differenza dal 1900 da cui conta)
        tm_inizio.tm_year = anno - 1900;
        tm_inizio.tm_mon = mese - 1;
        tm_inizio.tm_mday = giorno;
        tm_inizio.tm_hour = 8;
        tm_inizio.tm_min = 0;
        tm_inizio.tm_sec = 0;

        break;
    }
    //Trasforma i secondi in una data leggibile
    return mktime(&tm_inizio);
}

// Funzione che calcola il costo del noleggio minuto per minuto, dall'inizio alla fine, tenendo delle diverse tariffe 
float costo_noleggio(int giorno, time_t inizio) {
    
    time_t tempo_corrente = inizio;

    float prezzo_noleggio = 0.0;

// Un ciclo che verifica il costo, giorno per giorno, tenendo conto degli sconti e delle festività italiane 
    for(int i = 0; i < giorno; i++){
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

            prezzo_noleggio += 75.5;
        }else{                          //prezzo normale
            prezzo_noleggio += 55.9;
        }

        tempo_corrente += 86400;
    }
    printf("[TOTALE] - prezzo noleggio = %.2f€", prezzo_noleggio);
    return prezzo_noleggio;
}

// Funzione che stampa la data passata in  input
void stampa_data(time_t data){
    struct tm* tm_inizio = localtime(&data);  
    
    printf("Data e ora: %02d/%02d/%04d %02d:%02d\n", tm_inizio->tm_mday, tm_inizio->tm_mon + 1, tm_inizio->tm_year + 1900, 
                                                     tm_inizio->tm_hour, tm_inizio->tm_min);

}

// Funzione che crea un preventivo del costo secondo i giorni di utilizzo inserite da utente, tenendo delle diverse tariffe
void preventivo( ){

    printf("\n");
    printf("Attenzione\n");
    printf("Puoi prenotare solo per giorni interi che iniziano e finiscono alle 08:00 di mattina\n");
    printf("\n");
    
    printf("Inserisci la data di inizio: \n");
    time_t inizio = creazione_data();

    int giorni_noleggio;
    while(1){
        printf("Per quanti giorni vuoi noleggiare il veicolo (max 7)? ");
        scanf("%d", &giorni_noleggio);

        if (giorni_noleggio < 1 || giorni_noleggio > 7) {
            printf("Errore: puoi noleggiare un veicolo per un massimo di 7 giorni!\n");
            continue;
        }

        break;
    }

   costo_noleggio(giorni_noleggio, inizio);
}

// Funzione che mostra i dati all'utente a schermo per controllare se inseriti correttamente
void controllo_prenotazione(ptrprenotazione richiesta){
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
}

// Funzione per creare una nuova prenotazione, riempiendo tutti i campi attraverso l'inserimento da utente
ptrprenotazione creazione_prenotazione( ){
    ptrprenotazione nuova = malloc(sizeof(struct prenotazione));
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

    int giorni_noleggio;
    while(1){
        printf("Per quanti giorni vuoi noleggiare il veicolo (max 7)? ");
        scanf("%d", &giorni_noleggio);

        if (giorni_noleggio < 1 || giorni_noleggio > 7) {
            printf("Errore: puoi noleggiare un veicolo per un massimo di 7 giorni!\n");
            continue;
        }

        break;
    }

    nuova->fine = nuova->inizio + (giorni_noleggio * 86400);

    // Calcola il prezzo del noleggio, in base alla durata e secondo gli sconti
    nuova->costo = costo_noleggio(giorni_noleggio, nuova->inizio);   

    return nuova;
}

// Funzione che mostra le informazioni riguardo il costo del noleggio
void informazioni_costo_noleggio( ){

    printf("\n");
    printf("NOTA BENE: Puoi prenotare solo per giorni interi, per un massimo di una settimana!\n");
    printf("In caso di mancato utilizzo del veicolo da parte dell'utente non è previsto alcun rimborso!\n");
    printf("\n");
    printf("=================== DESCRIZIONE PREZZI NOLEGGIO ===================\n");
    printf("\n");
    printf("1. Prezzo standard (55.9€/gg):\n");
    printf("-In fasce di orari senza sconti e non festivi\n");

    printf("\n");
    printf("2. Prezzo festivo (75.5€/gg):\n");
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
}