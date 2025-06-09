#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "storico_noleggio.h"
#include "lista_storico_noleggio.h"
#include "lista.h"
#include "utile.h"



void inserisci_nodo_storico_noleggio(ptr_lista_noleggi lista, ptr_storico prenotazione) 
{
    if (!lista || !prenotazione) return;

    bool eliminabile = vedi_se_noleggio_eliminabile(prenotazione);

    if (lista_storico_vuota(lista)) {
        // Lista vuota
        metti_nodo_in_testa(lista, prenotazione);
        if (!eliminabile) {
            imposta_coda(lista, prendi_testa(lista));
        }
        return;
    }

    if (prendi_coda(lista) == NULL) {
        // Non ci sono nodi non eliminabili, quindi inserisco in testa sempre
        metti_nodo_in_testa(lista, prenotazione);
        if (!eliminabile) {
            imposta_coda(lista, prendi_testa(lista));  // il primo nodo non eliminabile diventa coda
        }
    } else {
        // Inserisco dopo il nodo puntato da coda
        ptr_lista prossimo_coda = prendi_prossimo(prendi_coda(lista));
        ptr_lista nuovo = metti_nodo(prenotazione, prossimo_coda);
        cambia_prossimo_nodo(prendi_coda(lista), nuovo);
        if (!eliminabile) {
            imposta_coda(lista, nuovo); // aggiorno coda solo se nodo non eliminabile
        }
    }
}



int stampa_lista_noleggi(ptr_lista_noleggi l)
{
    if (!l || lista_vuota(prendi_testa(l))) {
        printf("La lista dello storico è vuota.\n");
        return 0;
    }

    ptr_lista corrente = prendi_testa(l);

    int i = 1;
    while (corrente) {
        ptr_storico s = (ptr_storico) prendi_oggetto(corrente);
        printf("%d) ", i++);
        stampa_storico_noleggio(s);
        corrente = prendi_prossimo(corrente);
    }

    return i;
}


int stampa_dopo_coda(ptr_lista_noleggi l)
{
    if (!l || !prendi_coda(l)) {
        printf("Il puntatore coda è NULL.\n");
        return 0;
    }

    ptr_lista corrente = prendi_prossimo(prendi_coda(l));
    if (!corrente) {
        printf("Non ci sono nodi dopo la coda.\n");
        return 0;
    }
    int i = 1;
    while (corrente) {
       
        ptr_storico s = (ptr_storico) prendi_oggetto(corrente);
        printf("%d) ", i++);
        stampa_storico_noleggio(s);
        corrente = prendi_prossimo(corrente);
    }

    return i;
}






int elimina_nodo_storico_noleggio(ptr_lista_noleggi lista, char *targa_veicolo_eliminato,
                         int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine) {
    if (!lista || !prendi_testa(lista)) {
        printf("La lista è vuota.\n");
        return 0;
    }

    int count = 0;
    int scelta = 0;

    if (prendi_coda(lista) == NULL) {
        // coda == NULL -> eliminiamo da testa in poi
        count = stampa_lista_noleggi(lista);
    } else {
        // coda != NULL -> eliminiamo solo nodi dopo la coda
        count = stampa_dopo_coda(lista);
        if (count == 0) {
            printf("Non ci sono prenotazioni eliminabili dopo la coda.\n");
            return 0;
        }
    }

    if (count <= 0) {
        printf("Nessuna prenotazione da eliminare.\n");
        return 0;
    }

    printf("Inserisci il numero della prenotazione da eliminare (0 per annullare): ");
    if (scanf("%d", &scelta) != 1) {
        printf("Input non valido.\n");
        while (getchar() != '\n'); // pulizia buffer
        return 0;
    }

    if (scelta <= 0 || scelta > count) {
        printf("Eliminazione annullata.\n");
        return 0;
    }

    ptr_lista nodo_precedente = NULL;
    ptr_lista curr = NULL;
    int i = 1;

    if (prendi_coda(lista) == NULL) {
        // Naviga dalla testa per la scelta-esima prenotazione
        curr = prendi_testa(lista);
        while (curr && i < scelta) {
            nodo_precedente = curr;
            curr = prendi_prossimo(curr);
            i++;
        }
    } else {
        // Naviga solo nella parte dopo la coda
        nodo_precedente = prendi_coda(lista);
        curr = prendi_prossimo(nodo_precedente);
        while (curr && i < scelta) {
            nodo_precedente = curr;
            curr = prendi_prossimo(curr);
            i++;
        }
    }

    if (!curr) {
        printf("Errore: nodo da eliminare non trovato.\n");
        return 0;
    }

    ptr_storico dati = prendi_prenotazione_da_lista(curr);

    // Copia dati prima di liberare
    strncpy(targa_veicolo_eliminato, prendi_targa_veicolo_noleggiato(dati), 8);
    targa_veicolo_eliminato[7] = '\0';

    *ora_inizio = prendi_ora_inizio_noleggiato(dati);
    *minuto_inizio = prendi_minuto_inizio_noleggiato(dati);
    *ora_fine = prendi_ora_fine_noleggiato(dati);
    *minuto_fine = prendi_minuto_fine_noleggiato(dati);

    // Scollega il nodo dalla lista
    if (prendi_coda(lista) == NULL) {
        // Possiamo eliminare anche la testa
        if (nodo_precedente == NULL) {
            // curr è la testa, aggiorna testa
            imposta_testa(lista, prendi_prossimo(curr));
        } else {
            cambia_prossimo_nodo(nodo_precedente, prendi_prossimo(curr));
        }
    } else {
        // coda != NULL, eliminiamo solo dopo coda, nodo_precedente non può essere NULL
        cambia_prossimo_nodo(nodo_precedente, prendi_prossimo(curr));
        // NON modifichiamo coda qui
    }

    distruggi_nodo(curr, (void (*)(void *))distruggi_storico_noleggio);

    printf("Prenotazione eliminata con successo.\n");
    return 1;
}







void salva_lista_storico_noleggio_su_file(ptr_lista_noleggi lista, char *nome_utente)
{
    if (!lista || !nome_utente) {
        printf("Impossibile salvare: lista o nome utente non validi.\n");
        return;
    }

    char nome_file[100];
    snprintf(nome_file, sizeof(nome_file), "%s.txt", nome_utente);

    FILE *fp = fopen(nome_file, "w");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    ptr_lista corrente = prendi_testa(lista);
    while (corrente) {
        ptr_storico s = (ptr_storico) prendi_oggetto(corrente);
        if (s) {
            // Scrivi tutti i dati separati da ";"
            fprintf(fp, "%d;%d;%d;%d;%d;%s;%s;%s;%.2f;%d;%d;%d;%d\n",
                    prendi_giorno_noleggiato(s),
                    prendi_mese_noleggiato(s),
                    prendi_anno_noleggiato(s),
                    prendi_ora_fine_noleggiato(s),
                    prendi_minuto_fine_noleggiato(s),
                    prendi_tipo_veicolo_noleggiato(s),
                    prendi_targa_veicolo_noleggiato(s),
                    prendi_utente_veicolo_noleggiato(s),
                    prendi_costo_noleggiato(s),
                    prendi_ora_inizio_noleggiato(s),
                    prendi_minuto_inizio_noleggiato(s),
                    prendi_ora_fine_noleggiato(s),
                    prendi_minuto_fine_noleggiato(s));
        }
        corrente = prendi_prossimo(corrente);
    }

    fclose(fp);
}


void carica_lista_storico_noleggio_da_file(ptr_lista_noleggi lista, char *nome_utente)
{
    if (!lista || !nome_utente) {
        printf("Lista o nome utente non validi.\n");
        return;
    }

    char nome_file[100];
    snprintf(nome_file, sizeof(nome_file), "%s.txt", nome_utente);

    FILE *fp = fopen(nome_file, "r");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    // Buffer e variabili per i campi
    int giorno, mese, anno, ora, minuto, ora_inizio, minuto_inizio, ora_fine, minuto_fine;
    float costo;
    char tipo_veicolo[50], targa_veicolo[8], nome_file_utente[50];

    while (fscanf(fp, "%d;%d;%d;%d;%d;%49[^;];%7[^;];%49[^;];%f;%d;%d;%d;%d\n",
                  &giorno, &mese, &anno, &ora, &minuto,
                  tipo_veicolo, targa_veicolo, nome_file_utente,
                  &costo, &ora_inizio, &minuto_inizio, &ora_fine, &minuto_fine) == 13) {

        // Alloca e inserisci la prenotazione
        ptr_storico pren = inizia_storico_noleggio(giorno, mese, anno, ora, minuto, tipo_veicolo, targa_veicolo, nome_file_utente, costo, ora_inizio, minuto_inizio, ora_fine, minuto_fine);
        if(pren){
            inserisci_nodo_storico_noleggio(lista, pren);
        }
    }

    fclose(fp);
}


void aggiungi_prenotazione_storico_su_file(
    const char *targa,
    const char *tipo_veicolo,
    const char *nome_utente,
    int ora_inizio,
    int minuto_inizio,
    int ora_fine,
    int minuto_fine,
    float costo
) {
    if (!targa || !tipo_veicolo || !nome_utente) {
        printf("Parametri non validi per la scrittura su file.\n");
        return;
    }

    char nome_file[100];
    snprintf(nome_file, sizeof(nome_file), "%s.txt", nome_utente);

    FILE *fp = fopen(nome_file, "a");  // modalità append
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    int giorno, mese, anno;
    int ora, minuto;
    data_attuale(&giorno, &mese, &anno);
    ottieni_orario_corrente(&ora, &minuto);

    fprintf(fp, "%d;%d;%d;%d;%d;%s;%s;%s;%.2f;%d;%d;%d;%d\n",
            giorno, mese, anno,
            ora, minuto,
            tipo_veicolo,
            targa,
            nome_utente,
            costo,
            ora_inizio,
            minuto_inizio,
            ora_fine,
            minuto_fine);

    fclose(fp);
}






