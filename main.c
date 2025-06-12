#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#include "Interfaccia_utente/interfaccia_utente.h"

#define PERCORSO_FILE_VEICOLI "txt/Veicoli"
#define PERCORSO_PRENOTAZIONI_VEICOLI "txt/Prenotazioni_veicoli"


#define DIM_HASH_UTENTI 200
#define DIM_HASH_VEICOLI 150





/*
 Funzione: avvia_menu_principale
 --------------------------------

 Gestisce il menu principale dell'applicazione per un utente autenticato.
 Permette:
    - Prenotare veicoli.
    - Consultare ed eventualmente modificare lo storico delle prenotazioni.
    - Terminare il programma.

 Implementazione:
    - Cicla finché l’utente non decide di uscire.
    - Invoca le funzioni `menu_prenotazione` e `gestione_storico_prenotazioni` per le relative operazioni.

 Parametri:
    utente       - puntatore all'utente attualmente loggato
    hash_veicoli - puntatore alla tabella hash contenente tutti i veicoli

 Pre-condizioni:
    - utente deve essere un puntatore valido e non NULL.
    - hash_veicoli deve essere una tabella hash valida e inizializzata.

 Post-condizioni:
    - Tutte le operazioni effettuate possono aggiornare file e strutture dati.
    - Termina solo su esplicita richiesta dell’utente (scelta 0).

 Ritorna:
    Nessun valore di ritorno (void).

 Side-effect:
    - Input/output su console.
    - Lettura e scrittura su file.
    - Modifica delle strutture di prenotazione e storico noleggi.
*/
void avvia_menu_principale(ptr_utente utente, ptr_hash_veicoli hash_veicoli);


int main() {
    ptr_hash_utenti hash_ut = crea_hash_utenti(DIM_HASH_UTENTI);
    if (!hash_ut) {
        errore_allocazione();
        return 1;
    }

    ptr_hash_veicoli hash_veicoli = crea_hash_veicoli(DIM_HASH_VEICOLI);
    if (!hash_veicoli) {
        errore_allocazione();
        distruggi_hash_utenti(hash_ut);
        return 1;
    }

    if(carica_veicoli_da_file("veicoli.txt", hash_veicoli, PERCORSO_FILE_VEICOLI) == 0){
        fprintf(stderr, "[ERRORE] Impossibile aprire il file \"%s\"\n", PERCORSO_FILE_VEICOLI);
         distruggi_hash_utenti(hash_ut);
         distruggi_hash_veicoli(hash_veicoli);
        return 1;
    }

    if(carica_prenotazioni_veicoli_da_file(hash_veicoli, PERCORSO_PRENOTAZIONI_VEICOLI) == 0){
        printf("\n[ERRORE], caricamenti prenotazioni veicoli ha fallito.");
         distruggi_hash_utenti(hash_ut);
         distruggi_hash_veicoli(hash_veicoli);
        return 1;
    }
    if(aggiorna_prenotazioni_veicoli(hash_veicoli) == 0){
        printf("\n[ERRORE], aggiornamento prenotazioni veicoli ha fallito.");
         distruggi_hash_utenti(hash_ut);
         distruggi_hash_veicoli(hash_veicoli);
        return 1;
    }

    if(aggiorna_file_prenotazione_veicoli(hash_veicoli, PERCORSO_PRENOTAZIONI_VEICOLI) == 0){
        printf("\n[ERRORE], aggiornamento file prenotazioni veicoli ha fallito.");
         distruggi_hash_utenti(hash_ut);
         distruggi_hash_veicoli(hash_veicoli);
        return 1;
    }

    if (vedi_se_giorno_nuovo()) {
        int giorno, mese, anno;
        data_attuale(&giorno, &mese, &anno);
        FILE *f = fopen("txt/ultimo_avvio.txt", "w");
        if (f) {
            fprintf(f, "%d %d %d", giorno, mese, anno);
            fclose(f);
        }
    }

    ptr_utente utente = gestione_utente(hash_ut);
    if (!utente) {
        fprintf(stderr, "Errore durante la gestione dell'utente.\n");
        distruggi_hash_veicoli(hash_veicoli);
        distruggi_hash_utenti(hash_ut);
        return 1;
    }

    avvia_menu_principale(utente, hash_veicoli);

    distruggi_hash_utenti(hash_ut);
    distruggi_hash_veicoli(hash_veicoli);

    return 0;
}


void avvia_menu_principale(ptr_utente utente, ptr_hash_veicoli hash_veicoli)
{
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