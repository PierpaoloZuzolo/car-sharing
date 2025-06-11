/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Modello_veicolo/veicolo.h"
#include "ADT_array/array_prenotazione.h"
#include "utile_veicolo.h"
#include "utile_array_prenotazione.h"
#include "ADT_hash/hash_veicoli.h"
#include "ADT_hash/tab_hash.h"
#include "utile.h"


/*
 Funzione: stampa_veicolo
 ------------------------

 Visualizza le informazioni principali del veicolo e gli orari disponibili.

 Implementazione:
    Verifica che il puntatore al veicolo sia valido.
    Stampa marca, modello, targa e posizione del veicolo.
    Mostra gli orari disponibili tramite la funzione `mostra_orari_disponibili`.

 Parametri:
    ve: puntatore alla struttura `veicolo` da stampare

 Pre-condizioni:
    Il puntatore `ve` deve essere valido (non NULL)

 Post-condizioni:
    Nessuna

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Scrive su standard output le informazioni relative al veicolo
    e gli orari disponibili letti dalla struttura delle prenotazioni
 */
void stampa_veicolo(ptr_veicolo ve)
{
    if(ve){
        printf(" %s  %s [%s] \n\tposizione: %s\n", prendi_marca(ve), prendi_modello(ve),
                                                         prendi_targa(ve), prendi_posizione(ve));
        printf("\n\tOrari disponibili:\n");

        mostra_orari_disponibili(prendi_prenotazioni(ve));
        printf("\n");
    }
}



/*
  Funzione: carica_veicoli_da_file
  --------------------------------

  Carica i dati dei veicoli da un file di testo e li inserisce in una tabella hash.

  Implementazione:
     Costruisce il percorso completo del file a partire dal nome file e da un eventuale percorso.
     Apre il file in modalità lettura ("r").
     Per ogni riga ben formattata, legge marca, modello, targa e posizione del veicolo.
     Crea un oggetto veicolo con i dati letti e lo inserisce nella tabella hash tramite `inserisci_veicolo_in_hash`.
     In caso di errore nell’inserimento, libera la memoria allocata per il veicolo.

  Parametri:
     nome_file: nome del file contenente i dati dei veicoli
     h: puntatore alla tabella hash dei veicoli
     percorso_file: percorso opzionale della cartella in cui si trova il file

  Pre-condizioni:
     nome_file e h devono essere non NULL

  Post-condizioni:
     se il file è valido, i veicoli vengono letti e inseriti nella tabella hash;
     le righe mal formattate vengono ignorate, e viene stampato un messaggio d'errore.

  Ritorna:
     1 se il file è stato aperto correttamente (indipendentemente dal contenuto);
     0 se il file non può essere aperto.

  Side-effect:
     apre e legge da un file;
     può allocare memoria dinamicamente per ogni veicolo e inserirlo nella tabella hash;
     stampa su stderr eventuali messaggi d’errore se la creazione o l’inserimento fallisce.
 */

int carica_veicoli_da_file(const char *nome_file, ptr_hash_veicoli h, const char *percorso_file)
{
    char path_completo[100];

    if (percorso_file && strlen(percorso_file) > 0) {
        snprintf(path_completo, sizeof(path_completo), "%s/%s", percorso_file, nome_file);
    } else {
        snprintf(path_completo, sizeof(path_completo), "%s", nome_file);
    }

    FILE *file = fopen(path_completo, "r");
    if (!file) {
        return 0;
    }

    char marca[31], modello[41], targa[9], posizione[61];

    while (fscanf(file, "%30s %40s %8s %60s", marca, modello, targa, posizione) == 4) {
        ptr_veicolo v = inizia_veicolo(marca, modello, targa, posizione);
        if (v) {
            // carica_prenotazioni_da_file(...) ora viene gestito separatamente
            if (!inserisci_veicolo_in_hash(h, v)) {
                fprintf(stderr, "[ERRORE] Inserimento hash fallito per %s\n", targa);
                free(v);
            }
        } else {
            fprintf(stderr, "[ERRORE] Creazione veicolo fallita per %s\n", targa);
        }
    }

    fclose(file);
    return 1;
}




/*
 Funzione: libera_veicolo
 ------------------------

 Libera la memoria allocata per una struttura veicolo, comprese le sue prenotazioni.

 Implementazione:
    Verifica che il puntatore al veicolo sia valido.
    Chiama la funzione `libera_prenotazioni` per liberare la memoria associata alle prenotazioni.
    Libera la memoria occupata dalla struttura veicolo stessa.

 Parametri:
    ve: puntatore alla struttura `veicolo` da liberare

 Pre-condizioni:
    `ve` può essere NULL o un puntatore valido a una struttura `veicolo`.

 Post-condizioni:
    Se `ve` è valido, tutta la memoria allocata per il veicolo e le sue prenotazioni viene liberata.

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Dealloca memoria dinamica per la struttura veicolo e le sue prenotazioni.
 */

void libera_veicolo(ptr_veicolo ve)
{
    if(ve){
        distruggi_array_prenotazioni(prendi_prenotazioni(ve));
        free(ve);
    }
}



/*
  Funzione: aggiorna_stato_veicolo
  --------------------------------

  Aggiorna lo stato attuale di un veicolo in base alla sua disponibilità per il giorno corrente.

  Implementazione:
     Verifica che il puntatore al veicolo sia valido.
     Recupera le prenotazioni associate al veicolo.
     Se il veicolo risulta disponibile oggi (tramite `veicolo_disponibile_oggi`), 
     imposta il suo stato a "disponibile", altrimenti a "NON disponibile".

  Parametri:
     ve: puntatore alla struttura del veicolo da aggiornare

  Pre-condizioni:
     ve != NULL

  Post-condizioni:
     lo stato del veicolo è aggiornato in base alla disponibilità giornaliera

  Ritorna:
     true se l’aggiornamento è stato eseguito con successo;
     false se il puntatore al veicolo è NULL.

  Side-effect:
     modifica il campo "stato" del veicolo.
 */

bool aggiorna_stato_veicolo(ptr_veicolo ve) 
{
    if (!ve) return false;

    if (veicolo_disponibile_oggi(prendi_prenotazioni(ve))) {
        imposta_stato_veicolo(ve, "disponibile");
        return true;
    } else {
        imposta_stato_veicolo(ve, "NON disponibile");
        return true;
    }
}

/*
 Funzione: veicolo_disponibile
 -----------------------------

 Verifica se un veicolo è attualmente disponibile in base al suo stato.

 Implementazione:
    Controlla se il campo `stato` del veicolo è uguale alla stringa "disponibile".
    Se il confronto ha successo, restituisce true, altrimenti false.

 Parametri:
    ve: puntatore a una struttura `veicolo` di cui si vuole verificare la disponibilità.

 Pre-condizioni:
    Il parametro `ve` deve essere un puntatore valido o NULL.

 Post-condizioni:
    Nessuna modifica agli oggetti passati.

 Ritorna:
    `true` se il campo `stato` del veicolo è "disponibile", `false` altrimenti
    (incluso il caso in cui `ve` sia NULL).

 Side-effect:
    Nessuno.
 */
bool veicolo_disponibile(ptr_veicolo ve)
{
  if(!ve) return false;

  if(strcmp(prendi_stato(ve), "disponibile") == 0){
    return true;
  }

  return false;
}





/*
 Funzione: stampa_veicoli_disponibili
 ------------------------------------

 Scansiona la tabella hash dei veicoli e stampa a video tutti i veicoli attualmente disponibili.

 Implementazione:
    - Ottiene tutti i veicoli presenti nella tabella hash tramite `ottieni_valori_hash`.
    - Per ogni veicolo controlla la disponibilità chiamando `veicolo_disponibile`.
    - Se disponibile, stampa i dati del veicolo tramite `stampa_veicolo`.
    - Restituisce il numero di veicoli disponibili stampati.

 Parametri:
    h - puntatore alla tabella hash dei veicoli (ptr_hash_veicoli).

 Pre-condizioni:
    - La tabella hash `h` deve essere inizializzata e valida.
    - Le funzioni `veicolo_disponibile` e `stampa_veicolo` devono essere definite e funzionanti.

 Post-condizioni:
    - Stampa a video i veicoli disponibili.
    - Restituisce il numero totale di veicoli disponibili stampati.
    - Libera la memoria allocata da `ottieni_valori_hash`.

 Ritorna:
    - Il numero di veicoli disponibili stampati.
    - 0 se la tabella hash è vuota o non valida.

 Side-effect:
    - Stampa su stdout le informazioni dei veicoli disponibili.
    - Libera la memoria allocata temporaneamente per la lista dei veicoli.
*/
int stampa_veicoli_disponibili(ptr_hash_veicoli h)
{
    if (!h) return 0;

    int numero_elementi = 0;
    void **valori = ottieni_valori_hash(h, &numero_elementi);

    if (!valori || numero_elementi == 0) {
        if (valori) free(valori);
        return 0;
    }
    int conto = 0;
    for (int i = 0; i < numero_elementi; ++i) {
        ptr_veicolo ve = (ptr_veicolo)valori[i];
        

        if (veicolo_disponibile(ve)) {
            printf("====================================\n");
            stampa_veicolo(ve);
            printf("====================================\n");
            conto++;
        }
    }

    free(valori); // Libera la memoria allocata da ottieni_valori_hash
    return conto;
}

/*
  Funzione: aggiorna_prenotazioni_veicoli
  ---------------------------------------

  Aggiorna le prenotazioni di tutti i veicoli presenti nella tabella hash.

  Implementazione:
     Ottiene tutti i veicoli dalla tabella hash.
     Per ciascun veicolo:
       - verifica se è iniziato un nuovo giorno; in tal caso azzera le celle delle prenotazioni;
       - blocca le celle corrispondenti alle ore già passate;
       - aggiorna lo stato del veicolo in base alla disponibilità attuale.

  Parametri:
     h: puntatore alla tabella hash contenente i veicoli

  Pre-condizioni:
     h != NULL

  Post-condizioni:
     le prenotazioni e lo stato di ogni veicolo sono aggiornati in base alla data e all'ora correnti

  Ritorna:
     1 se l’operazione è stata eseguita correttamente;
     0 in caso di errore (hash NULL o vuota)

  Side-effect:
     modifica le strutture interne di prenotazioni e stato di ogni veicolo;
     libera la memoria dell’array temporaneo ottenuto da `ottieni_valori_hash`.
*/
int aggiorna_prenotazioni_veicoli(ptr_hash_veicoli h)
{
   if (!h) return 0;

   int numero_elementi = 0;
   void **valori = ottieni_valori_hash(h, &numero_elementi);

   if (!valori || numero_elementi == 0) {
      if (valori) free(valori);
      return 0;
   }

   for (int i = 0; i < numero_elementi; i++){
      ptr_veicolo ve = (ptr_veicolo)valori[i];
      ptr_prenotazione pren = prendi_prenotazioni(ve);
      // Se è un nuovo giorno, azzera la struttura  
      if(vedi_se_giorno_nuovo()){
         azzera_celle(pren);  
      }
      //blocca le celle passate
      blocca_celle_passate(pren);
      aggiorna_stato_veicolo(ve);
   }
   free(valori);
   return 1;
}

/*
  Funzione: aggiorna_file_prenotazione_veicoli
  --------------------------------------------

  Salva su file le prenotazioni aggiornate di tutti i veicoli nella tabella hash.

  Implementazione:
     Ottiene tutti i veicoli dalla tabella hash.
     Per ciascun veicolo, salva la sua struttura di prenotazioni su file, 
     utilizzando il percorso e la targa del veicolo.

  Parametri:
     h: puntatore alla tabella hash contenente i veicoli
     percorso_file: percorso della cartella in cui salvare i file delle prenotazioni

  Pre-condizioni:
     h != NULL

  Post-condizioni:
     i file delle prenotazioni dei veicoli sono aggiornati sul disco

  Ritorna:
     1 se l’operazione ha avuto successo;
     0 in caso di errore (hash NULL o vuota)

  Side-effect:
     scrive su file le prenotazioni di ogni veicolo;
     libera la memoria dell’array temporaneo ottenuto da `ottieni_valori_hash`.
*/
int aggiorna_file_prenotazione_veicoli(ptr_hash_veicoli h, const char *percorso_file)
{
   if (!h) return 0;

   int numero_elementi = 0;
   void **valori = ottieni_valori_hash(h, &numero_elementi);

   if (!valori || numero_elementi == 0) {
      if (valori) free(valori);
      return 0;
   }
   for (int i = 0; i < numero_elementi; i++){
      ptr_veicolo ve = (ptr_veicolo)valori[i];
   
      salva_prenotazione_su_file(prendi_prenotazioni(ve), prendi_targa(ve), percorso_file);
      
      
      
   }
   free(valori);
   return 1;
}


/*
  Funzione: carica_prenotazioni_veicoli_da_file
  ---------------------------------------------

  Carica da file le prenotazioni associate a ciascun veicolo nella tabella hash.

  Implementazione:
     Ottiene tutti i veicoli dalla tabella hash.
     Per ciascun veicolo, tenta di caricare la struttura prenotazioni dal file corrispondente.
     In caso di fallimento di caricamento, stampa un messaggio di avviso su stderr.

  Parametri:
     h: puntatore alla tabella hash contenente i veicoli
     percorso_file: percorso della cartella in cui si trovano i file delle prenotazioni

  Pre-condizioni:
     h != NULL

  Post-condizioni:
     le strutture prenotazioni dei veicoli sono caricate con i dati contenuti nei file

  Ritorna:
     1 se l’operazione ha avuto successo almeno parzialmente;
     0 in caso di errore (hash NULL o vuota)

  Side-effect:
     legge da file le prenotazioni di ogni veicolo;
     stampa messaggi di avviso in caso di errori di caricamento;
     libera la memoria dell’array temporaneo ottenuto da `ottieni_valori_hash`.
*/
int carica_prenotazioni_veicoli_da_file(ptr_hash_veicoli h, const char *percorso_file)
{
   
   if (!h) return 0;

   int numero_elementi = 0;
   void **valori = ottieni_valori_hash(h, &numero_elementi);

   if (!valori || numero_elementi == 0) {
      if (valori) free(valori);
      return 0;
   }
   for (int i = 0; i < numero_elementi; i++){
      ptr_veicolo ve = (ptr_veicolo)valori[i];
   
      
   int result = carica_prenotazioni_da_file(prendi_prenotazioni(ve), prendi_targa(ve), percorso_file);
   if (!result) {
      fprintf(stderr, "[ATTENZIONE] Prenotazioni non caricate per il veicolo %s\n", prendi_targa(ve));
}
      
      
   }
   free(valori);
   return 1;
}