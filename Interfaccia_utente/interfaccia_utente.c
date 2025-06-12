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

#define PERCORSO_STORICO_NOLEGGI "txt/Storico_noleggi"
#define PERCORSO_PRENOTAZIONI_VEICOLI "txt/Prenotazioni_veicoli"
#define PERCORSO_FILE_UTENTI "txt/Utenti"

#define MAX_TENTATIVI 5


/*
 Funzione: leggi_cella_da_orario
 -------------------------------

 Legge da input un orario nel formato "HH MM" (ore minuti) e lo converte nell'indice
 di una cella oraria, considerando che ogni ora è divisa in due celle (00 e 30 minuti).

 Implementazione:
    - Richiede all'utente di inserire un orario nel formato HH MM.
    - Controlla che l'input sia valido (due numeri interi).
    - Verifica che l'ora sia tra 0 e 24 e che i minuti siano solo 0 o 30.
    - In caso di errore, mostra un messaggio e ripete la richiesta.
    - Se valido, calcola e restituisce l'indice della cella corrispondente:
      ogni ora corrisponde a 2 celle, 0 minuti → cella pari, 30 minuti → cella dispari.

 Parametri:
    messaggio : stringa da mostrare come prompt all'utente per la lettura dell'orario

 Pre-condizioni:
    messaggio deve essere una stringa valida non nulla

 Post-condizioni:
    Nessuna modifica a variabili esterne

 Ritorna:
    L'indice intero della cella oraria corrispondente all'orario inserito (da 0 a 48)

 Side-effect:
    Stampa messaggi su stdout e legge da stdin
*/
int leggi_cella_da_orario(const char *messaggio)
{
    int ora, minuto;
    while (1) {
        printf("%s formato HH MM (ore - minuti): ", messaggio);
        int result = scanf("%d %d", &ora, &minuto);

        // Pulizia del buffer in caso di input errato
        if (result != 2) {
            printf("Input non valido. Inserisci due numeri interi.\n");   
            while (getchar() != '\n'); // scarta input residuo
            continue;
        }

        if (ora < 0 || ora > 24 || (minuto != 0 && minuto != 30)) {
            printf("Orario non valido. Usa solo minuti :00 o :30 e ore tra 0 e 24.\n");
            continue;
        }

        // Valido → restituisci indice della cella
        return ora * 2 + (minuto == 30 ? 1 : 0);
    }
}

/*
 Funzione: gestione_utente
 --------------------------

 Gestisce la logica di registrazione e login degli utenti.
 Carica gli utenti esistenti da file e permette la selezione tra:
    - Registrazione di un nuovo utente.
    - Login di un utente esistente.

 Implementazione:
    - Carica i dati da file all'inizio.
    - Cicla finché l’utente non effettua una registrazione/login valida oppure sceglie di uscire.
    - In caso di registrazione, salva il nuovo utente anche su file.

 Parametri:
    h - puntatore alla tabella hash contenente gli utenti (ptr_hash_utenti)

 Pre-condizioni:
    - h deve essere una struttura hash valida e inizializzata.
    - Deve esistere il file "txt/Utenti/utenti.txt" per la lettura/scrittura.

 Post-condizioni:
    - Restituisce un puntatore a un utente valido (registrato o loggato), oppure termina il programma in caso di uscita.

 Ritorna:
    - Puntatore a una struttura `ptr_utente` contenente l'utente loggato o registrato.

 Side-effect:
    - Input/output su console.
    - Lettura e scrittura su file per la persistenza degli utenti.
    - Possibile terminazione del programma con `exit()` in caso di uscita o errori gravi.
*/
ptr_utente gestione_utente(ptr_hash_utenti h) {
    char nome[50], email[100];
    int scelta;

    carica_utenti_da_file("utenti.txt", h, PERCORSO_FILE_UTENTI);

    while (1) {
        printf("\n==============================\n");
        printf("       Luxury Sharing     \n");
        printf("==============================\n");
        printf(" 1. Registrazione\n");
        printf(" 2. Login\n");
        printf(" 0. Esci\n");
        printf("------------------------------\n");
        printf(" Scelta: ");

        if (scanf("%d", &scelta) != 1) {
            printf("\nInput non valido. Per favore inserisci un numero.\n");
            pulisci_input_buffer();
            continue;
        }
        pulisci_input_buffer();

        switch (scelta) {
            case 0:
                printf("\nHai scelto di uscire. Alla prossima!\n");
                return NULL;

            case 1: {
                printf("\nRegistrazione utente\n");

                int tentativi_nome = 0;
                while (tentativi_nome < MAX_TENTATIVI) {
                    printf("Inserisci nome (solo lettere, numeri, underscore): ");
                    leggi_input(nome, sizeof(nome));

                    if (!valida_nome(nome)) {
                        printf("Nome non valido. Tentativi rimanenti: %d\n", MAX_TENTATIVI - tentativi_nome - 1);
                        tentativi_nome++;
                        continue;
                    }

                    if (cerca_utente_in_hash(h, nome)) {
                        printf("Nome già esistente. Scegli un altro nome.\n");
                        tentativi_nome++;
                        continue;
                    }

                    break;
                }
                if (tentativi_nome == MAX_TENTATIVI) {
                    printf("\nTroppe tentativi falliti. Operazione annullata.\n");
                    return NULL;
                }

                int tentativi_email = 0;
                while (tentativi_email < MAX_TENTATIVI) {
                    printf("Inserisci email (deve contenere '@' e '.'): ");
                    leggi_input(email, sizeof(email));

                    if (!valida_email(email)) {
                        printf("Email non valida. Tentativi rimanenti: %d\n", MAX_TENTATIVI - tentativi_email - 1);
                        tentativi_email++;
                        continue;
                    }
                    break;
                }
                if (tentativi_email == MAX_TENTATIVI) {
                    printf("\nTroppe tentativi falliti. Operazione annullata.\n");
                    return NULL;
                }

                ptr_utente nuovo = inizia_utente(nome, email);
                if (!nuovo) {
                    printf("\nErrore: risorse di sistema insufficienti.\n");
                    return NULL;
                }

                if (inserisci_utente_in_hash(h, nuovo)) {
                    salva_utente_su_file("utenti.txt", nuovo, PERCORSO_FILE_UTENTI);
                    printf("\nRegistrazione completata!");
                    printf("\nBenvenut* in Luxury Sharing, %s!\n\n", nome);
                    return nuovo;
                } else {
                    printf("\nErrore: nome utente non valido o duplicato.\n");
                    libera_utente(nuovo);
                }

                break;
            }

            case 2: {
                printf("\nLogin utente\n");
                printf("Inserisci nome: ");
                leggi_input(nome, sizeof(nome));

                ptr_utente trovato = cerca_utente_in_hash(h, nome);
                if (trovato) {
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

            default:
                printf("\nScelta non valida. Riprova.\n");
                break;
        }
    }
}


/*
 Funzione: menu_prenotazione
 ---------------------------

 Gestisce il menu interattivo di prenotazione veicolo per l'utente.

 Implementazione:
    - Visualizza i veicoli disponibili.
    - Permette all'utente di selezionare un veicolo e prenotare un intervallo di tempo.
    - Calcola il costo, applica eventuali sconti basati sullo storico dell'utente.
    - Registra la prenotazione e aggiorna lo storico.

 Parametri:
    hash_veicoli - puntatore alla tabella hash contenente i veicoli disponibili
    nome_utente  - stringa contenente il nome dell'utente che effettua la prenotazione

 Pre-condizioni:
    hash_veicoli valido e inizializzato
    nome_utente valido (non NULL)

 Post-condizioni:
    Se l'utente conferma la prenotazione:
        - aggiorna le prenotazioni del veicolo
        - aggiorna i file relativi alle prenotazioni e allo storico
    Se l'utente annulla:
        - nessuna modifica persistente viene effettuata

 Ritorna:
    ptr_veicolo - puntatore al veicolo prenotato se la prenotazione ha successo,
                  NULL se l'utente annulla o se la prenotazione fallisce

 Side-effect:
    - Modifica lo stato delle prenotazioni del veicolo selezionato
    - Scrive su file per aggiornare prenotazioni e storico noleggi
    - Input/output su console
*/
ptr_veicolo menu_prenotazione(ptr_hash_veicoli hash_veicoli, char *nome_utente){
    ptr_veicolo ve = NULL;

    printf("\n\n===== VEICOLI DISPONIBILI =====\n\n");
    aggiorna_prenotazioni_veicoli(hash_veicoli);
    aggiorna_file_prenotazione_veicoli(hash_veicoli, PERCORSO_PRENOTAZIONI_VEICOLI);
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
            if(carica_lista_storico_noleggio_da_file(lista_noleggi, nome_utente, PERCORSO_STORICO_NOLEGGI) == 0){
                printf("\n[ERRORE] caricamenti lista storico noleggio ha fallito.");
                exit(1);
            }
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
                aggiorna_stato_veicolo(ve);
                aggiorna_file_prenotazione_veicoli(hash_veicoli, PERCORSO_PRENOTAZIONI_VEICOLI);

                printf("Prenotazione per veicolo [%s] completata!\n", prendi_targa(ve));

                int ora_inizio, minuto_inizio, ora_fine, minuto_fine;
                converti_celle_in_orario(inizio, fine, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine);

                aggiungi_prenotazione_storico_su_file(prendi_targa(ve), prendi_marca(ve), nome_utente,
                                                     ora_inizio, minuto_inizio, ora_fine, minuto_fine, costo, PERCORSO_STORICO_NOLEGGI);

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

/*
 Funzione: gestione_storico_prenotazioni
 ---------------------------------------

 Permette all'utente di visualizzare e gestire lo storico delle prenotazioni effettuate.
 Consente anche di eliminare una prenotazione precedente, aggiornando sia lo storico che
 lo stato di prenotazione del veicolo corrispondente.

 Implementazione:
    - Carica dallo storico le prenotazioni dell'utente.
    - Stampa l'intero storico delle prenotazioni.
    - Permette all'utente, se desidera, di eliminare una prenotazione.
    - In caso di eliminazione:
        - Aggiorna la struttura di prenotazione del veicolo.
        - Aggiorna i file di storico e di prenotazione.

 Parametri:
    nome_utente   - puntatore a stringa contenente il nome utente (identifica il file dello storico)
    hash_veicoli  - puntatore alla tabella hash contenente tutti i veicoli

 Pre-condizioni:
    - nome_utente deve essere un puntatore valido e non NULL
    - hash_veicoli deve essere una struttura hash valida e inizializzata

 Post-condizioni:
    - Se effettuata l’eliminazione, i dati vengono aggiornati su file e in memoria
    - Se nessuna eliminazione, nessuna modifica persistente avviene

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    - Input/output su console
    - Modifica file su disco per storico noleggi e prenotazioni veicoli
    - Modifica la struttura di prenotazioni in memoria per i veicoli

*/
void gestione_storico_prenotazioni(char *nome_utente, ptr_hash_veicoli hash_veicoli) {
    ptr_lista_noleggi lista_noleggi = crea_lista_storico();
    if( carica_lista_storico_noleggio_da_file(lista_noleggi, nome_utente, PERCORSO_STORICO_NOLEGGI) == 0){
        printf("\n[ERRORE] caricamento dello storico noleggi ha fallito.");
        distruggi_lista_storico_noleggio(lista_noleggi);
        return;
    }

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
        int count, scelta;

        if (prendi_coda(lista_noleggi) == NULL) {
        // coda == NULL -> eliminiamo da testa in poi
        count = stampa_lista_noleggi(lista_noleggi);
    } else {
        // coda != NULL -> eliminiamo solo nodi dopo la coda
        count = stampa_dopo_coda(lista_noleggi);
        
    }

        if (count <= 0){
            printf("\nNon ci sono prenotazioni eliminabili.\n");
            distruggi_lista_storico_noleggio(lista_noleggi);
            return;
        }

        printf("Inserisci il numero della prenotazione da eliminare (0 per annullare): ");
        while(1){
            scelta = inserisci_scelta();
            if(scelta < 0 || scelta > count){
                printf("\nInserire un numero valido (tra 1 e %d)", count);
                continue;
            }else if (scelta == 0){
                     printf("\nOperazione annulata\nRitorno al menu,");
                    distruggi_lista_storico_noleggio(lista_noleggi);
                    return;
            } else break;
           
        }


        if (elimina_nodo_storico_noleggio(lista_noleggi, targa_veicolo_eliminato, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine, scelta)) {
            ptr_veicolo ve = cerca_veicolo_in_hash(hash_veicoli, targa_veicolo_eliminato);
            if (ve != NULL) {
                converti_orario_in_celle(ora_inizio, minuto_inizio, ora_fine, minuto_fine, &cella_inizio, &cella_fine);
                libera_intervallo(prendi_prenotazioni(ve), cella_inizio, cella_fine);
                salva_prenotazione_su_file(prendi_prenotazioni(ve), prendi_targa(ve), PERCORSO_PRENOTAZIONI_VEICOLI);
                
                
                salva_lista_storico_noleggio_su_file(lista_noleggi, nome_utente, PERCORSO_STORICO_NOLEGGI);
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

