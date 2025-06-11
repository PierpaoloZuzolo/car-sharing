#include <stdio.h>
#include <stdlib.h>

#include "interfaccia_utente.h"
#include "Modello_utente/utente.h"
#include "ADT_hash/hash_utenti.h"
#include "Modello_veicolo/veicolo.h"
#include "ADT_array/array_prenotazione.h"
#include "utili/utile.h"
#include "utili/utile_utente.h"
#include "utili/utile_array_prenotazione.h"
#include "utili/utile_veicolo.h"
#include "ADT_hash/hash_veicoli.h"
#include "Modello_storico_noleggio/storico_noleggio.h"
#include "ADT_lista/lista_storico_noleggio.h"
#include "utili/utile_lista_storico_noleggio.h"

ptr_utente gestione_utente(ptr_hash_utenti h) {
    char nome[50], email[100];

    carica_utente_da_file("txt/Utenti/utenti.txt", h);

    int scelta;

    while(1){
        printf("\n==============================\n");
        printf("       Luxury Sharing     \n");
        printf("==============================\n");
        printf(" 1. Registrazione\n");
        printf(" 2. Login\n");
        printf(" 0. Esci\n");
        printf("------------------------------\n");
        printf(" Scelta: ");

        if(scanf("%d", &scelta) != 1) {
            printf("\nInput non valido. Per favore inserisci un numero.\n");
            while(getchar() != '\n');
            continue;
        }

        switch (scelta) {
            case 0:
                printf("\nHai scelto di uscire. Alla prossima!\n");
                exit(0);

            case 1: {
                printf("\nRegistrazione utente");
                printf("\nInserisci nome: ");
                scanf("%49s", nome);
                printf("Inserisci email: ");
                scanf("%99s", email);

                ptr_utente nuovo = inizia_utente(nome, email);
                if (!nuovo){
                    printf("\nErrore risorse sistema insufficienti.\n");
                    exit(1);
                }

                if(inserisci_utente_in_hash(h, nuovo)){
                    salva_utente_su_file("txt/Utenti/utenti.txt", nuovo);
                    printf("\nRegistrazione completata!");
                    printf("\nBenvenut* in Luxury Sharing, %s!\n\n", nome);
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

                ptr_utente trovato = cerca_utente_in_hash(h, nome);

                if(trovato){
                    printf("\nLogin effettuato!");
                    printf("\nBentornat* ");
                    stampa_utente(trovato);
                    printf("\n");
                    return trovato;
                } else {
                    printf("\nUtente non trovato. Riprova o registrati.\n");
                }
                break;
            }
        }
    }
}

void avvia_menu_principale(ptr_utente utente, ptr_hash_veicoli hash_veicoli) {
    int scelta;

    do {
        printf("\n====== MENU PRINCIPALE ======\n");
        printf("1. Visualizza veicoli disponibili\n");
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
                if (veicolo_prenotato)
                    printf("Prenotazione completata con successo!\n");
                else
                    printf("Nessuna prenotazione effettuata.\n");
                break;
            }
            case 2:
                gestione_storico_prenotazioni(prendi_nome(utente), hash_veicoli);
                break;

            case 0:
                printf("Uscita...\n");
                break;

            default:
                printf("Scelta non valida.\n");
        }
    } while (scelta != 0);
}

ptr_veicolo menu_prenotazione(ptr_hash_veicoli hash_veicoli, char *nome_utente){
    ptr_veicolo ve = NULL;

    printf("\n\n===== VEICOLI DISPONIBILI =====\n\n");
    aggiorna_prenotazioni_veicoli(hash_veicoli);
    aggiorna_file_prenotazione_veicoli(hash_veicoli);
    stampa_veicoli_disponibili(hash_veicoli);

    printf("\n1. Prenota un veicolo\n");
    printf("\n0. Indietro\n");
    int scelta;
    while(1){
        scelta = inserisci_scelta();
        if (scelta == 1 || scelta == 0) break;
        printf("\nScelta non valida. Digitare 0 o 1.\n");
    }

    if(scelta == 0) return NULL;

    while (1) {
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

            ptr_lista_noleggi lista_noleggi = crea_lista_storico();
            carica_lista_storico_noleggio_da_file(lista_noleggi, nome_utente);
            int sconto = conta_fino_a_coda(lista_noleggi);
            distruggi_lista_storico_noleggio(lista_noleggi);

            float costo = calcola_costo_noleggio(inizio, fine, sconto);

            if(sconto >= 10){
                printf("\nIl costo per il noleggio del veicolo è di %.2f euro,\nsul quale è stato applicato lo sconto per frequenza d'uso.\n\n", costo);
            } else {
                printf("\nIl costo del veicolo e' di %.2f euro.\n\n", costo);
            }

            printf("\nConfermare prenotazione");
            printf("\n1. Conferma prenotazione");
            printf("\n0. Annulla prenotazione\n");
            int scelta;
            while(1){
                scelta = inserisci_scelta();
                if (scelta == 1 || scelta == 0) break;
                printf("\nScelta non valida. Digitare 0 o 1.\n");
            }
            if (scelta == 0) return NULL;

            if (prenota_intervallo(prendi_prenotazioni(ve), inizio, fine)) {
                aggiorna_prenotazione_veicolo(ve);

                printf("Prenotazione per veicolo [%s] completata!\n", prendi_targa(ve));

                int ora_inizio, minuto_inizio, ora_fine, minuto_fine;
                converti_celle_in_orario(inizio, fine, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine);

                aggiungi_prenotazione_storico_su_file(prendi_targa(ve), prendi_marca(ve), nome_utente,
                                                     ora_inizio, minuto_inizio, ora_fine, minuto_fine, costo);

                return ve;
            } else {
                printf("Intervallo non disponibile.\n");

                printf("\nVuoi:\n");
                printf("1. Riprovare la prenotazione per questo veicolo\n");
                printf("2. Tornare alla lista veicoli\n");
                printf("0. Annullare e tornare al menu principale\n");
                printf("Scelta: ");

                while(1){
                    scelta = inserisci_scelta();
                    if (scelta == 0 || scelta == 1 || scelta == 2) break;
                    printf("\nDigitare 0, 1 o 2.\n");
                }

                if (scelta == 1) {
                    continue;
                } else if (scelta == 2) {
                    break;
                } else {
                    printf("Operazione annullata.\n");
                    return NULL;
                }
            }
        }
    }
    return NULL;
}

void gestione_storico_prenotazioni(char *nome_utente, ptr_hash_veicoli hash_veicoli) {
    ptr_lista_noleggi lista_noleggi = crea_lista_storico();
    carica_lista_storico_noleggio_da_file(lista_noleggi, nome_utente);

    printf("\n===== STORICO NOLEGGI =====\n\n");
    int lunghezza_lista = stampa_lista_noleggi(lista_noleggi);
    if (lunghezza_lista == 0) {
        printf("Nessuna prenotazione trovata.\n");
        distruggi_lista_storico_noleggio(lista_noleggi);
        return;
    }

    printf("\n\n1. Elimina prenotazione\n0. Indietro\n\n");
    int scelta;
    while (1) {
        scelta = inserisci_scelta();
        if (scelta == 0 || scelta == 1) break;
        printf("\nInserire 1 per eliminare o 0 per tornare indietro.\n");
    }

    if (scelta == 1) {
        printf("\n=== PRENOTAZIONI CHE PUOI ELIMINARE ===\n\n");
        char targa_veicolo_eliminato[8];
        int ora_inizio, minuto_inizio, ora_fine, minuto_fine;
        int cella_inizio, cella_fine;

        if (elimina_nodo_storico_noleggio(lista_noleggi, targa_veicolo_eliminato, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine)) {
            ptr_veicolo ve = cerca_veicolo_in_hash(hash_veicoli, targa_veicolo_eliminato);
            if (ve != NULL) {
                converti_orario_in_celle(ora_inizio, minuto_inizio, ora_fine, minuto_fine, &cella_inizio, &cella_fine);
                libera_intervallo(prendi_prenotazioni(ve), cella_inizio, cella_fine);
                salva_prenotazioni_su_file(prendi_prenotazioni(ve), targa_veicolo_eliminato);
                salva_lista_storico_noleggio_su_file(lista_noleggi, nome_utente);
                printf("Prenotazione eliminata con successo.\n");
            } else {
                printf("Errore: veicolo non trovato nell'hash.\n");
            }
        } else {
            printf("Nessuna prenotazione eliminata.\n");
        }
    }

    distruggi_lista_storico_noleggio(lista_noleggi);
}

