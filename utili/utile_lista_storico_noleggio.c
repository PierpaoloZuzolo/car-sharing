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
 Funzione: dimensione_lista
 --------------------------

 Calcola il numero totale di nodi presenti nella lista dei noleggi.

 Implementazione:
    La funzione itera attraverso la lista a partire dalla testa,
    contando ogni nodo finché non raggiunge la fine (NULL).

 Parametri:
    l: puntatore alla lista dei noleggi

 Pre-condizioni:
    `l` deve essere un puntatore valido a una struttura lista.
    Tuttavia, la funzione gestisce anche il caso in cui `l` sia NULL o vuota.

 Post-condizioni:
    Nessuna modifica alla lista.

 Ritorna:
    Un intero rappresentante il numero di nodi presenti nella lista.
    Restituisce 0 se la lista è NULL o se non ha nodi.

 Side-effect:
    Nessuno.
 */

int dimensione_lista(ptr_lista_noleggi l)
{
    if (!l || !prendi_testa(l)) {
        
        return 0;

    }
    ptr_lista corrente = prendi_testa(l);
    int count = 0;
    while (corrente) {
        count++;
        corrente = prendi_prossimo(corrente);
    }
    return count;
}


void inserisci_nodo_storico_noleggio(ptr_lista_noleggi lista, ptr_storico prenotazione, int eliminabile) 
{
    if (!lista || !prenotazione) return;

    //bool eliminabile = vedi_se_noleggio_eliminabile(prenotazione);

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

    return i - 1;
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
        // printf("Il puntatore coda e NULL.\n");
        return 0;
    }

    ptr_lista corrente = prendi_prossimo(prendi_coda(l));
    if (!corrente) {
        //printf("Non ci sono nodi dopo la coda.\n");
        return 0;
    }
    int i = 1;
    while (corrente) {
       
        ptr_storico s = (ptr_storico) prendi_oggetto(corrente);
        printf("%d) ", i++);
        stampa_storico_noleggio(s);
        corrente = prendi_prossimo(corrente);
    }

    return i-1;
}


/*
 Funzione: elimina_nodo_storico_noleggio
 ---------------------------------------

 Elimina un nodo specifico dalla lista dello storico noleggi, identificato
 tramite una scelta numerica (1-based), e restituisce i dettagli del noleggio
 eliminato attraverso parametri di output.

 Implementazione:
    Se la lista è vuota o la scelta è fuori intervallo, la funzione termina senza modifiche.
    Se esiste una coda (nodo non eliminabile), la navigazione inizia dal nodo successivo alla coda.
    Altrimenti, la navigazione parte dalla testa della lista.
    Il nodo corrispondente alla `scelta` viene scollegato dalla lista e deallocato.
    Prima della distruzione, la funzione salva targa e orari della prenotazione eliminata
    nei parametri passati per riferimento.

 Parametri:
    lista: puntatore alla lista dei noleggi
    targa_veicolo_eliminato: stringa dove viene salvata la targa del veicolo eliminato (lunghezza minima 8)
    ora_inizio, minuto_inizio: puntatori per salvare l'orario di inizio del noleggio eliminato
    ora_fine, minuto_fine: puntatori per salvare l'orario di fine del noleggio eliminato
    scelta: posizione (1-based) del nodo da eliminare

 Pre-condizioni:
    - `lista` deve essere un puntatore valido e inizializzato.
    - `targa_veicolo_eliminato`, `ora_inizio`, `minuto_inizio`, `ora_fine`, `minuto_fine` devono essere puntatori validi.
    - `scelta` deve essere maggiore di 0 e non superiore alla dimensione della lista nella parte eliminabile.

 Post-condizioni:
    - Il nodo selezionato viene rimosso dalla lista.
    - I dati della prenotazione eliminata vengono copiati nei parametri di output.

 Ritorna:
    1 se la rimozione è avvenuta con successo,
    0 in caso di errore (lista vuota, indice non valido o nodo non trovato).

 Side-effect:
    Modifica la lista dei noleggi, deallocando la memoria del nodo rimosso.
 */

int elimina_nodo_storico_noleggio(ptr_lista_noleggi lista, char *targa_veicolo_eliminato,             
                         int *ora_inizio, int *minuto_inizio, int *ora_fine, int *minuto_fine, int scelta) {
    if (!lista || !prendi_testa(lista)) {
       // printf("La lista è vuota.\n");
        return 0;
    }

    int count = dimensione_lista(lista);
    if(scelta > count || scelta <= 0){
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
        // printf("Errore: nodo da eliminare non trovato.\n");
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

    //printf("Prenotazione eliminata con successo.\n");
    return 1;
}



/*
  Funzione: salva_lista_storico_noleggio_su_file
  ----------------------------------------------

  Salva su file lo storico dei noleggi associato a un determinato utente.

  Implementazione:
     Costruisce il nome del file a partire dal nome utente e, se fornito, dal percorso della cartella.
     Apre il file in modalità scrittura ("w").
     Scorre la lista dei noleggi e, per ogni elemento, estrae le informazioni relative allo storico
     e le scrive su file in formato CSV con campo delimitato da ';'.

  Parametri:
     lista: puntatore alla lista contenente i record dello storico noleggi
     nome_utente: stringa identificativa dell'utente
     percorso_cartella: stringa opzionale contenente il percorso in cui salvare il file

  Pre-condizioni:
     lista != NULL
     nome_utente != NULL e non vuota (strlen(nome_utente) > 0)

  Post-condizioni:
     se il file può essere aperto, il contenuto della lista viene salvato nel file specificato;
     ogni elemento della lista viene scritto su una riga in formato CSV;
     se il file non può essere aperto, viene stampato un messaggio di errore e non viene scritto nulla.

  Ritorna:
     Nessun valore di ritorno (funzione `void`)

  Side-effect:
     crea o sovrascrive un file con nome basato sull’utente;
     scrive su file i dati della lista di noleggi;
     stampa messaggi di errore in caso di parametri invalidi o problemi di apertura file.
 */

void salva_lista_storico_noleggio_su_file(ptr_lista_noleggi lista, const char *nome_utente, const char *percorso_cartella) 
{
    if (!lista || !nome_utente || strlen(nome_utente) == 0) {
        printf("Impossibile salvare: lista o nome utente non validi.\n");
        return;
    }

    char nome_file[200];
    if (percorso_cartella && strlen(percorso_cartella) > 0) {
        snprintf(nome_file, sizeof(nome_file), "%s/%s.txt", percorso_cartella, nome_utente);
    } else {
        snprintf(nome_file, sizeof(nome_file), "%s.txt", nome_utente);
    }

    FILE *fp = fopen(nome_file, "w");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    ptr_lista corrente = prendi_testa(lista);
    while (corrente) {
        ptr_storico s = (ptr_storico)prendi_oggetto(corrente);
        if (s) {
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
  -----------------------------------------------

  Carica da file lo storico dei noleggi relativi a un determinato utente e li inserisce nella lista fornita.

  Implementazione:
     Costruisce il nome del file a partire dal nome utente e, se specificato, dal percorso.
     Apre il file in modalità lettura ("r").
     Per ogni riga del file, legge i campi delimitati da punto e virgola (';'), crea un oggetto `ptr_storico`,
     e lo inserisce nella lista.

  Parametri:
     lista: puntatore alla lista in cui caricare gli elementi dello storico
     nome_utente: stringa che identifica l'utente
     percorso_file: stringa opzionale che specifica il percorso della cartella dei file

  Pre-condizioni:
     lista != NULL
     nome_utente != NULL

  Post-condizioni:
     se il file esiste ed è valido, gli elementi vengono letti e inseriti nella lista;
     se il file non esiste, la lista rimane invariata;
     eventuali righe non leggibili o incomplete vengono ignorate.

  Ritorna:
     1 se la lettura ha avuto successo e almeno una riga è stata gestita correttamente;
     2 se il file non esiste (non è considerato un errore critico);
     0 in caso di parametri non validi (lista o nome utente NULL)

  Side-effect:
     apre e legge da un file su disco;
     può modificare il contenuto della lista passata come parametro;
     alloca memoria dinamica per ogni record storico inserito nella lista.
 */

int carica_lista_storico_noleggio_da_file(ptr_lista_noleggi lista, char *nome_utente, const char *percorso_file)
{
    if (!lista || !nome_utente) {
        // printf("Lista o nome utente non validi.\n");
        return 0;
    }

     char nome_file[200];
    if (percorso_file && strlen(percorso_file) > 0) {
        snprintf(nome_file, sizeof(nome_file), "%s/%s.txt", percorso_file, nome_utente);
    } else {
        snprintf(nome_file, sizeof(nome_file), "%s.txt", nome_utente);
    }

    FILE *fp = fopen(nome_file, "r");
    if (!fp) {
        //perror("Errore apertura file");
        return 2; // se il file non esiste non è un errore, ma l'utente non ha prenotazioni
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
            int eliminabile = vedi_se_noleggio_eliminabile(pren);
            inserisci_nodo_storico_noleggio(lista, pren, eliminabile);
        }
    }

    fclose(fp);
    return 1;
}


/*
  Funzione: aggiungi_prenotazione_storico_su_file
  -----------------------------------------------

  Aggiunge una nuova voce di prenotazione allo storico dei noleggi dell’utente, salvandola su file in formato CSV.

  Implementazione:
     Costruisce il nome del file a partire dal nome utente e, se fornito, dal percorso specificato.
     Apre il file in modalità "append" ("a"), così da aggiungere la prenotazione alla fine del file.
     Ottiene la data e l’orario correnti tramite le funzioni `data_attuale` e `ottieni_orario_corrente`.
     Scrive su una nuova riga del file tutti i campi della prenotazione, separati da punto e virgola (';').

  Parametri:
     targa: stringa contenente la targa del veicolo noleggiato
     tipo_veicolo: stringa che identifica la tipologia del veicolo
     nome_utente: stringa che rappresenta l'utente che ha effettuato il noleggio
     ora_inizio: ora di inizio del noleggio
     minuto_inizio: minuti di inizio del noleggio
     ora_fine: ora di fine del noleggio
     minuto_fine: minuti di fine del noleggio
     costo: costo del noleggio (valore float con 2 decimali)
     percorso_file: percorso opzionale della cartella dove salvare il file

  Pre-condizioni:
     targa, tipo_veicolo e nome_utente devono essere stringhe non NULL

  Post-condizioni:
     se il file è accessibile, una nuova riga con i dati della prenotazione viene aggiunta al file;
     altrimenti, nessun dato viene scritto e viene restituito 0.

  Ritorna:
     1 se l’operazione è andata a buon fine;
     0 se si è verificato un errore (es. parametri non validi o apertura file fallita)

  Side-effect:
     apre e scrive su un file su disco in modalità append;
     ottiene la data e ora correnti tramite funzioni di sistema.
 */

int aggiungi_prenotazione_storico_su_file(    
    const char *targa,
    const char *tipo_veicolo,
    const char *nome_utente,
    int ora_inizio,
    int minuto_inizio,
    int ora_fine,
    int minuto_fine,
    float costo,
    const char *percorso_file
) {
    if (!targa || !tipo_veicolo || !nome_utente) {
       // printf("Parametri non validi per la scrittura su file.\n");
        return 0;
    }

   char nome_file[200];
    if (percorso_file && strlen(percorso_file) > 0) {
        snprintf(nome_file, sizeof(nome_file), "%s/%s.txt", percorso_file, nome_utente);
    } else {
        snprintf(nome_file, sizeof(nome_file), "%s.txt", nome_utente);
    }

    FILE *fp = fopen(nome_file, "a");  // modalità append
    if (!fp) {
        perror("Errore apertura file");
        return 0;
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
    return 1;
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



