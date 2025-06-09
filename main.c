#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utente.h"
#include "hash_utenti.h"
#include "veicolo.h"
#include "array_prenotazione.h"
#include "utile.h"
#include "utile_utente.h"
#include "utile_array_prenotazione.h"
#include "utile_veicolo.h"
#include "hash_veicoli.h"
#include "storico_noleggio.h"
#include "lista_storico_noleggio.h"
#include "utile_lista_storico_noleggio.h"

#define DIM_HASH_UTENTI 200
#define DIM_HASH_VEICOLI 150


ptr_utente gestione_utente(ptr_hash_utenti h);

ptr_veicolo menu_prenotazione(ptr_hash_veicoli hash_veicoli, const char *nome_utente);

void gestione_storico_prenotazioni(char *nome_utente, ptr_hash_veicoli hash_veicoli);


int main (){
    ptr_hash_utenti hash_ut = crea_hash_utenti(DIM_HASH_UTENTI);
       if (!hash_ut){
           printf("Errore risorse sistema.");
           exit(1);
       }


    ptr_hash_veicoli hash_veicoli = crea_hash_veicoli(DIM_HASH_VEICOLI);
    carica_veicoli_da_file("veicoli.txt", hash_veicoli);


/*
    ptr_lista lista = nuova_lista();
       if(!lista){
           printf("Errore risorse sistema.");
           distruggi_hash(hash);
           exit(1);
       }
*/
    ptr_utente utente = gestione_utente(hash_ut);
    if (!utente) {
        fprintf(stderr, "Errore durante la gestione dell'utente.\n");
        distruggi_hash_veicoli(hash_veicoli);
        distruggi_hash_utenti(hash_ut);
        return 1;
    }   

   int scelta;
    do {
        printf("\n====== MENU PRINCIPALE ======\n");
        printf("1. Prenota un veicolo\n");
        printf("2. Visualizza storico prenotazioni\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        if (scanf("%d", &scelta) != 1) {
            printf("Input non valido.\n");
            while (getchar() != '\n');
            scelta = -1;
            continue;
        }

        switch (scelta) {
            case 1: {
                ptr_veicolo veicolo_prenotato = menu_prenotazione(hash_veicoli, prendi_nome(utente));
                if (veicolo_prenotato) {
                    printf("Prenotazione completata con successo!\n");
                } else {
                    printf("Nessuna prenotazione effettuata.\n");
                }
                break;
            }
            case 2: {
                 gestione_storico_prenotazioni(prendi_nome(utente), hash_veicoli);
                break;
            }
            case 0:{
                printf("Uscita...\n");
                break;
            }
            default:
                printf("Scelta non valida.\n");
        }

    } while (scelta != 0);


   // distruggi_lista(lista);
    distruggi_hash_utenti(hash_ut);
    distruggi_hash_veicoli(hash_veicoli);

    return 0;
}









/*
 Funzione: gestione_utente
 -------------------------
 Gestisce il menu utente con possibilità di:
  - Registrazione
  - Login
  - Visualizzazione informazioni sul sito e sulle regole di prenotazione e sconto
  - Uscita dal programma

 Parametri:
   h: puntatore alla struttura hash contenente gli utenti

 Pre-condizione:
   h deve essere una hash valida e inizializzata

 Post-condizione:
   Può modificare la struttura hash inserendo nuovi utenti

 Valore di ritorno:
   Puntatore all'utente registrato o loggato con successo, NULL se esce dal programma
*/
ptr_utente gestione_utente(ptr_hash_utenti h)
{
    char nome[50], email[100];

    carica_utente_da_file("utenti.txt", h);

    int scelta;

    while(1){
        printf("\n==============================\n");
        printf("       💎Luxury Sharing💎     \n");
        printf("==============================\n");
        printf(" 1. Registrazione\n");
        printf(" 2. Login\n");
        printf(" 3. Informazioni\n");
        printf(" 0. Esci\n");
        printf("------------------------------\n");
        printf(" Scelta: ");

        if(scanf("%d", &scelta) != 1) {
            // input non valido, svuota buffer e ripeti
            printf("\n⚠️ Input non valido. Per favore inserisci un numero.\n");
            while(getchar() != '\n'); // pulisci buffer
            continue;
        }

        switch (scelta) {
            case 0:
                printf("\n👋 Hai scelto di uscire. Alla prossima!\n");
                exit(0);


            case 1: {
                printf("\n📝 Registrazione utente");
                printf("\nInserisci nome: ");
                scanf("%49s", nome);
                printf("Inserisci email: ");
                scanf("%99s", email);
           
           ptr_utente nuovo = inizia_utente(nome, email); //inizializzazione variabile utente
           if (!nuovo){
            printf("\n⚠️ Errore risorse sistema insufficienti.\n");
            exit(1);
           }

           if(inserisci_utente_in_hash(h, nuovo)){
            salva_utente_su_file("utenti.txt", nuovo);
            printf("\n✅ Registrazione completata!");
            printf("\nBenvenut* in Luxury Sharing, %s!\n", nome);
                printf("\n");
            return nuovo;
           } else {
                printf("\nNome utente non valido. Riprova con un altro nome.\n");
                libera_utente(nuovo);
           }
           break;
            }

            case 2: {
           printf("\nLogin utente");
           printf("\nInserisci nome: ");
           scanf("%49s", nome);
/*
           //Crea un utente temporaneo con solo il nome ed email vuota
           ptr_utente temp = inizia_utente(nome, "");
           if(!temp){
            printf("\n⚠️ Errore risorse sistema insufficienti.");
            exit(1);
           }
*/
            ptr_utente trovato = cerca_utente_in_hash(h, nome);
            //libera_utente(temp);

            if(trovato){
                printf("\n✅ Login effettuato!");
                printf("\nBentornat* ");
                stampa_utente(trovato);
                printf("\n");
                return trovato;
            } else {
            printf("\n⚠️ Utente non trovato. Riprova o registrati.\n");
            }
            break;
            }
            
            case 3: {
            printf("==============================\n");
            printf("\nINFORMAZIONI SUL SITO WEB\n");
            printf("==============================\n");
            printf("Questo sito web e stato creato come progetto\n");
            printf("nell'anno 2024-2025, durante la laurea triennale\n");
            printf("in informatica, per Programmazione e strutture dati PEU-Z,\n");
            printf("corso tenuto:\n");
            printf("-Dalla Docente Carmen Bisogni\n");
            printf("-Dalla Docente Gemma Catolino\n");
            printf("-Dal Docente Giammaria Giordano\n");

            printf("\n==============================\n");
            printf("DESCRIZIONE DELLE PRENOTAZIONI\n");
            printf("==============================\n");
            printf("Le prenotazioni possono essere effettuate solo in intervalli di tempo\n");
            printf("che iniziano e finiscono a orari precisi, ovvero solo alle .00 o alle .30 di ogni ora.\n");
            printf("Ad esempio, potrai prenotare un veicolo dalle 10:00 alle 11:30,\n");
            printf("ma non dalle 10:15 o 10:45.\n");

            printf("\nSCONTO\n");
            printf("Si ha diritto allo sconto ogni 5 prenotazioni.\n");
           


            int sottoScelta;
            printf("\n==============================\n");
            printf(" 1. Torna al menu principale\n");
            printf(" 0. Esci dal programma\n");
            printf("-------------------------------\n");
            printf(" Scelta: ");
            if (scanf("%d", &sottoScelta) != 1) {
             while(getchar() != '\n');
             printf("\n⚠️ Input non valido. Torno al menu principale.\n");
             break;
            }

            if (sottoScelta == 0) {
                printf("\n👋 Hai scelto di uscire. Alla prossima!\n");
                exit(0);
            }

            // Altrimenti torna automaticamente al menu principale
            break;
            }
        }
    }
}


/*
 Funzione: menu_prenotazione
 ---------------------------
 
*/
ptr_veicolo menu_prenotazione(ptr_hash_veicoli hash_veicoli, const char *nome_utente){
    //carica_veicoli_da_file("veicoli.txt", hash_veicoli);

    if(vedi_se_giorno_nuovo()){
        int giorno, mese, anno;
        data_attuale(&giorno, &mese, &anno);
    
        FILE *f = fopen("ultimo_avvio.txt", "w");
        if (f) {
         fprintf(f, "%d %d %d", giorno, mese, anno);
         fclose(f);
         
        }
    }

    ptr_veicolo ve = NULL;

    while (1) {

        //stampa_hash_veicoli(hash_veicoli); // TODO


        printf("\nDigitare la targa del veicolo da prenotare: ");
        
        char targa[8];
        scanf("%7s", targa);
        ve = cerca_veicolo_in_hash(hash_veicoli, targa);
        if(!ve){
            printf("\nVeicolo non trovato.\n");
            continue;
        }


        while (1) {
            int inizio = leggi_cella_da_orario("Inserisci orario di inizio");
            int fine = leggi_cella_da_orario("Inserisci orario di fine");

            if (inizio >= fine) {
                printf("L'orario di fine deve essere successivo a quello di inizio.\n");
                continue;
            }

            if (prenota_intervallo(prendi_prenotazioni(ve), inizio, fine)) {
            salva_prenotazioni_su_file(prendi_prenotazioni(ve), prendi_targa(ve));

            aggiorna_stato_veicolo(ve);



            printf("Prenotazione per veicolo [%s] completata!\n", prendi_targa(ve));

            int sconto = 0; //DA FARE


            float costo = costo_noleggio(inizio, fine, sconto); // stampa e restituisce il costo


            int ora_inizio, minuto_inizio, ora_fine, minuto_fine;
            converti_celle_in_orario(inizio, fine, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine);

            aggiungi_prenotazione_storico_su_file(prendi_targa(ve), prendi_marca(ve), nome_utente, ora_inizio, minuto_inizio, ora_fine, minuto_fine, costo);

            return ve;
            } else {
                printf("Intervallo non disponibile.\n");

                int scelta;
                printf("\nVuoi:\n");
                printf("1. Riprovare la prenotazione per questo veicolo\n");
                printf("2. Tornare alla lista veicoli\n");
                printf("0. Annullare e tornare al menu principale\n");
                printf("Scelta: ");

                if (scanf("%d", &scelta) != 1) {
                    printf("Input non valido.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (scelta == 1) {
                    continue; // riprova la prenotazione sullo stesso veicolo
                } else if (scelta == 2) {
                    break; // torna alla scelta veicolo
                } else {
                    printf("Operazione annullata.\n");
                    return NULL;
                }
            }
        }   
    }
}




void gestione_storico_prenotazioni(char *nome_utente, ptr_hash_veicoli hash_veicoli)
{

    ptr_lista_noleggi lista_noleggi = crea_lista_storico();

    carica_lista_storico_noleggio_da_file(lista_noleggi, nome_utente);



    int lunghezza_lista = stampa_lista_noleggi(lista_noleggi);

    if(0 == lunghezza_lista) return;

    printf("\n\n1. Elimina prenotazione\n0. Indietro\n\n");
    int scelta;
    scanf("%d", &scelta);
    if(scelta == 1){
        char targa_veicolo_eliminato[8];
        int ora_inizio, minuto_inizio, ora_fine, minuto_fine, cella_inizio, cella_fine;
        if (elimina_nodo_storico_noleggio(lista_noleggi, targa_veicolo_eliminato, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine)){

        ptr_veicolo ve = cerca_veicolo_in_hash(hash_veicoli, targa_veicolo_eliminato);

        converti_orario_in_celle(ora_inizio, minuto_inizio, ora_fine, minuto_fine, &cella_inizio, &cella_fine);

        libera_intervallo(prendi_prenotazioni(ve), cella_inizio, cella_fine);

        salva_prenotazioni_su_file(prendi_prenotazioni(ve), targa_veicolo_eliminato);

        salva_lista_storico_noleggio_su_file(lista_noleggi, nome_utente);

        stampa_lista_noleggi(lista_noleggi); //debug

        printf("Funziono");
        }
        distruggi_lista_storico_noleggio(lista_noleggi);
    } else {
        distruggi_lista_storico_noleggio(lista_noleggi);

        return;
    }
}
