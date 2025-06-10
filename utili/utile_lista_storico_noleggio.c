/*
Autore: Carmine Saporoso, Pierpaolo Zuzolo
Data: 07/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Modello_storico_noleggio/storico_noleggio.h"
#include "ADT_lista/lista_storico_noleggio.h"
#include "ADT_lista/lista.h"
#include "utile.h"


/*
 Funzione: inserisci_nodo_storico_noleggio
 -----------------------------------------

 Inserisce un nuovo nodo nella lista dello storico noleggi rispettando la
 distinzione tra nodi eliminabili e non eliminabili.

 Implementazione:
    Se la lista è vuota, inserisce il nodo in testa.
    Se esiste una coda (primo nodo non eliminabile), inserisce il nuovo nodo
    subito dopo la coda e aggiorna la coda solo se il nuovo nodo non è eliminabile.
    Se la coda non esiste, inserisce il nodo in testa e, se non eliminabile, lo imposta come coda.

 Parametri:
    lista: puntatore alla lista dei noleggi
    prenotazione: puntatore allo storico noleggio da inserire nella lista

 Pre-condizioni:
    `lista` e `prenotazione` devono essere puntatori validi e non NULL.

 Post-condizioni:
    Il nodo viene inserito nella lista in posizione corretta,
    la coda viene aggiornata se necessario.

 Ritorna:
    void

 Side-effect:
    Modifica la lista collegata e può aggiornare la coda.
 */
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


/*
 Funzione: stampa_lista_noleggi
 ------------------------------

 Stampa a video l'intero contenuto della lista dei noleggi storici.

 Implementazione:
    Scorre la lista a partire dalla testa,
    stampa i dettagli di ogni elemento storico noleggio con indice progressivo.
    Se la lista è vuota o nulla, stampa un messaggio appropriato.

 Parametri:
    l: puntatore alla lista dei noleggi storici da stampare

 Pre-condizioni:
    l deve essere un puntatore valido o NULL.
    La lista deve contenere nodi validi.

 Post-condizioni:
    Viene stampata la lista dei noleggi a video.

 Ritorna:
    Il numero di elementi stampati più 1 (indice di fine lista),
    oppure 0 se la lista è vuota o nulla.

 Side-effect:
    Effettua stampe su stdout.
 */
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


/*
 Funzione: stampa_dopo_coda
 --------------------------

 Stampa a video gli elementi della lista dei noleggi storici a partire dal nodo successivo
 al nodo puntato come "coda".

 Implementazione:
    Verifica che la lista e il puntatore coda siano validi.
    Recupera il nodo successivo alla coda e stampa gli elementi da quel nodo in avanti.
    Se non ci sono nodi dopo la coda, stampa un messaggio informativo.

 Parametri:
    l: puntatore alla lista dei noleggi storici

 Pre-condizioni:
    l deve essere un puntatore valido.
    La lista deve avere un puntatore coda valido.

 Post-condizioni:
    Viene stampata la porzione di lista che segue la coda.

 Ritorna:
    Il numero di elementi stampati più 1 (indice di fine lista),
    oppure 0 se non ci sono nodi dopo la coda o se input non valido.

 Side-effect:
    Effettua stampe su stdout.
 */
int stampa_dopo_coda(ptr_lista_noleggi l)
{
    if (!l || !prendi_coda(l)) {
        printf("Il puntatore coda e NULL.\n");
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


/*
 Funzione: elimina_nodo_storico_noleggio
 ---------------------------------------

 Permette di eliminare un nodo dalla lista dei noleggi storici, scegliendo tra
 i nodi eliminabili (tutti se la coda è NULL, oppure solo quelli successivi alla coda).

 Implementazione:
    Se la coda è NULL stampa tutta la lista, altrimenti stampa solo i nodi dopo la coda.
    Chiede all’utente quale prenotazione eliminare.
    Rimuove il nodo scelto dalla lista scollegandolo.
    Copia i dati della prenotazione eliminata nei parametri forniti.
    Libera la memoria del nodo eliminato.

 Parametri:
    lista                  : puntatore alla lista dei noleggi storici
    targa_veicolo_eliminato: array di char dove verrà copiata la targa del veicolo eliminato (dimensione minima 8)
    ora_inizio             : puntatore a int per memorizzare l’ora di inizio del noleggio eliminato
    minuto_inizio          : puntatore a int per memorizzare il minuto di inizio
    ora_fine               : puntatore a int per memorizzare l’ora di fine
    minuto_fine            : puntatore a int per memorizzare il minuto di fine

 Pre-condizioni:
    lista deve essere valida e non vuota
    puntatori per copia dati devono essere validi

 Post-condizioni:
    nodo scelto viene eliminato dalla lista e memoria liberata
    dati della prenotazione eliminata copiati nei parametri passati

 Ritorna:
    1 se l’eliminazione è avvenuta con successo
    0 in caso di errore, input non valido o annullamento

 Side-effect:
    stampa messaggi su stdout
    modifica la lista e libera la memoria del nodo eliminato
*/
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



/*
 Funzione: salva_lista_storico_noleggio_su_file
 ----------------------------------------------

 Salva su file il contenuto della lista dei noleggi storici di un utente.

 Implementazione:
    Controlla la validità dei parametri.
    Costruisce il nome del file usando il nome utente con estensione ".txt".
    Apre il file in scrittura.
    Scorre la lista e per ogni elemento scrive su file i campi separati da ";"
    Chiude il file.

 Parametri:
    lista       : puntatore alla lista dei noleggi storici
    nome_utente : stringa con il nome utente usato per il nome del file

 Pre-condizioni:
    lista e nome_utente devono essere validi e non NULL

 Post-condizioni:
    Su file "%s.txt" (dove %s è nome_utente) viene scritto lo storico dei noleggi

 Ritorna:
    void

 Side-effect:
    Scrive su file e produce output su stdout in caso di errore
*/
void salva_lista_storico_noleggio_su_file(ptr_lista_noleggi lista, char *nome_utente)
{
    if (!lista || !nome_utente) {
        printf("Impossibile salvare: lista o nome utente non validi.\n");
        return;
    }

    char nome_file[100];
    snprintf(nome_file, sizeof(nome_file), "txt/Storico_noleggi/%s.txt", nome_utente);

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
                    prendi_ora_noleggiato(s),
                    prendi_minuto_noleggiato(s),
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


/*
 Funzione: carica_lista_storico_noleggio_da_file
 ----------------------------------------------

 Carica da file lo storico dei noleggi di un utente, inserendo le prenotazioni nella lista.

 Implementazione:
    Verifica la validità dei parametri in input.
    Costruisce il nome del file da leggere utilizzando il nome utente con estensione ".txt".
    Apre il file in modalità lettura.
    Legge riga per riga i dati nel formato previsto, parsandoli correttamente.
    Per ogni riga crea un nuovo nodo storico di noleggio con i dati letti.
    Inserisce il nodo nella lista.
    Chiude il file.

 Parametri:
    lista       : puntatore alla lista dei noleggi storici in cui inserire i dati
    nome_utente : stringa contenente il nome utente usato per costruire il nome del file

 Pre-condizioni:
    lista e nome_utente devono essere puntatori validi e non NULL
    il file "%s.txt" (dove %s è nome_utente) deve esistere ed essere leggibile
    il file deve rispettare il formato previsto con 13 campi separati da ';'

 Post-condizioni:
    La lista viene popolata con i nodi storico noleggio corrispondenti alle righe lette dal file

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout in caso di errore apertura file
    Modifica la lista inserendo nuovi nodi
*/
void carica_lista_storico_noleggio_da_file(ptr_lista_noleggi lista, char *nome_utente)
{
    if (!lista || !nome_utente) {
        printf("Lista o nome utente non validi.\n");
        return;
    }

    char nome_file[100];
    snprintf(nome_file, sizeof(nome_file), "txt/Storico_noleggi/%s.txt", nome_utente);

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


/*
 Funzione: aggiungi_prenotazione_storico_su_file
 ----------------------------------------------

 Aggiunge una nuova prenotazione allo storico dell'utente salvandola su file.

 Implementazione:
    Verifica che i parametri di input non siano NULL.
    Costruisce il nome del file a partire dal nome utente con estensione ".txt".
    Apre il file in modalità append per aggiungere i dati alla fine.
    Recupera la data e l'orario corrente.
    Scrive nel file i dati della prenotazione in formato separato da ';'.
    Chiude il file.

 Parametri:
    targa           : stringa con la targa del veicolo prenotato
    tipo_veicolo    : stringa con il tipo del veicolo
    nome_utente     : stringa con il nome utente proprietario dello storico
    ora_inizio      : ora di inizio noleggio
    minuto_inizio   : minuto di inizio noleggio
    ora_fine        : ora di fine noleggio
    minuto_fine     : minuto di fine noleggio
    costo           : costo totale del noleggio

 Pre-condizioni:
    targa, tipo_veicolo e nome_utente devono essere puntatori validi e non NULL
    Le funzioni data_attuale e ottieni_orario_corrente devono essere definite e funzionanti

 Post-condizioni:
    La prenotazione viene aggiunta in fondo al file storico dell'utente

 Ritorna:
    void

 Side-effect:
    Effettua stampe su stdout in caso di errore apertura file
    Modifica il file di testo con l'aggiunta della nuova prenotazione
*/
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
    snprintf(nome_file, sizeof(nome_file), "txt/Storico_noleggi/%s.txt", nome_utente);

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

/*
 Funzione: conta_fino_a_coda
 ---------------------------

 Conta il numero di elementi nella lista dei noleggi, partendo dalla testa fino ad arrivare alla coda inclusa.

 Implementazione:
    - Verifica la validità della lista e dei puntatori a testa e coda.
    - Scorre la lista a partire dalla testa.
    - Incrementa un contatore per ogni nodo visitato fino a raggiungere il nodo di coda.
    - Se la coda non viene trovata (lista mal formata), restituisce 0.

 Parametri:
    l: puntatore a una lista di noleggi (ptr_lista_noleggi)

 Pre-condizioni:
    l deve essere un puntatore valido a una lista non vuota, con testa e coda correttamente impostate.

 Post-condizioni:
    Nessuna modifica alla lista originale.

 Ritorna:
    Un intero che rappresenta il numero di elementi dalla testa alla coda inclusa.
    Se la coda non è raggiungibile dalla testa, restituisce 0.

 Side-effect:
    Nessuno.
*/


int conta_fino_a_coda(ptr_lista_noleggi l) 
{
    if (!l || !prendi_testa(l) || !prendi_coda(l)) {
        // Precondizione violata
        return 0;
    }

    ptr_lista corrente = prendi_testa(l);
    ptr_lista coda = prendi_coda(l);
    int count = 0;

    while (corrente) {
        count++;
        if (corrente == coda) break;
        corrente = prendi_prossimo(corrente);
    }

    
    if (corrente != coda) {// Se non abbiamo trovato la coda, restituiamo 0
        return 0;
    }

    return count;
}
