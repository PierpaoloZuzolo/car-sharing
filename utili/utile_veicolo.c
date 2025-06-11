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

 Carica i veicoli da un file di testo e li inserisce nella tabella hash dei veicoli.
 Per ogni veicolo letto dal file, viene creata una struttura `veicolo` e caricata la relativa disponibilità prenotazioni.

 Implementazione:
    - Apre il file in modalità lettura.
    - Per ogni riga del file, legge i dati del veicolo (marca, modello, targa, posizione).
    - Crea un nuovo veicolo tramite `inizia_veicolo`.
    - Carica le prenotazioni associate al veicolo tramite `carica_prenotazioni_da_file`.
    - Inserisce il veicolo nella tabella hash dei veicoli.
    - In caso di errore di inserimento nella hash o di allocazione, stampa messaggio d'errore.

 Parametri:
    nome_file - stringa contenente il percorso/nome del file da cui caricare i veicoli.
    h         - puntatore alla tabella hash di veicoli (ptr_hash_veicoli) in cui inserire i veicoli caricati.

 Pre-condizioni:
    - Il puntatore `nome_file` deve essere valido e puntare a un file esistente e accessibile in lettura.
    - La tabella hash `h` deve essere già inizializzata.

 Post-condizioni:
    - Inserisce in `h` tutti i veicoli validi letti dal file.
    - Se il file non esiste o si verifica un errore di apertura, la funzione restituisce 0.
    - Se il caricamento ha successo, restituisce 1.

 Ritorna:
    - 1 se il caricamento è avvenuto con successo.
    - 0 in caso di errore di apertura file.

 Side-effect:
    - Alloca dinamicamente memoria per ciascun veicolo caricato.
    - Inserisce i veicoli nella tabella hash.
    - Stampa messaggi di errore su stderr in caso di problemi.
*/
int carica_veicoli_da_file(const char *nome_file, ptr_hash_veicoli h)
{
    FILE *file = fopen(nome_file, "r");
    if (!file) {
        fprintf(stderr, "[ERRORE] Impossibile aprire il file \"%s\"\n", nome_file);
        return 0;
    }

    char marca[31], modello[41], targa[9], posizione[61];

    while (fscanf(file, "%30s %40s %8s %60s", marca, modello, targa, posizione) == 4) {
        ptr_veicolo v = inizia_veicolo(marca, modello, targa, posizione);
        if (v) {
            carica_prenotazioni_da_file(prendi_prenotazioni(v),prendi_targa(v));
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

 Aggiorna lo stato di disponibilità del veicolo in base alle prenotazioni del giorno corrente.

 Implementazione:
    Verifica se il veicolo è disponibile oggi analizzando le sue prenotazioni.
    Imposta lo stato del veicolo su "disponibile" se è disponibile, altrimenti su "NON disponibile".
    Restituisce true solo se lo stato è stato impostato su "NON disponibile".

 Parametri:
    ve: puntatore alla struttura `veicolo` da aggiornare

 Pre-condizioni:
    `ve` deve essere un puntatore valido a una struttura `veicolo`.

 Post-condizioni:
    Lo stato del veicolo (`ve->stato`) viene aggiornato coerentemente con la sua disponibilità.

 Ritorna:
    `true` se il veicolo è *non disponibile* oggi, `false` se disponibile o se `ve` è NULL.

 Side-effect:
    Modifica il campo `stato` all'interno della struttura `veicolo`.
 */
bool aggiorna_stato_veicolo(ptr_veicolo ve) 
{
    if (!ve) return false;

    if (veicolo_disponibile_oggi(prendi_prenotazioni(ve))) {
        imposta_stato_veicolo(ve, "disponibile");
        return false;
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
 Funzione: aggiorna_prenotazione_veicolo
 ---------------------------------------

 Aggiorna lo stato delle prenotazioni di un veicolo, blocca le celle non più prenotabili 
 in base all'orario corrente, salva le prenotazioni aggiornate su file e aggiorna lo stato 
 del veicolo (disponibile o non disponibile).

 Implementazione:
    - Ottiene il puntatore alla prenotazione associata al veicolo.
    - Blocca le celle delle prenotazioni che non sono più utilizzabili (celle passate).
    - Salva le prenotazioni aggiornate su file, usando la targa del veicolo per il nome file.
    - Aggiorna lo stato del veicolo in base alla disponibilità odierna.

 Parametri:
    ve: puntatore al veicolo di cui aggiornare le prenotazioni e lo stato.

 Pre-condizioni:
    ve deve essere un puntatore valido a un veicolo con prenotazioni valide.

 Post-condizioni:
    Le prenotazioni del veicolo sono aggiornate, salvate su file e lo stato del veicolo è aggiornato.

 Ritorna:
    Nessun valore di ritorno (void).

 Side-effect:
    Modifica le prenotazioni associate al veicolo.
    Scrive su file i dati aggiornati delle prenotazioni.
    Modifica lo stato interno del veicolo.
*/


void aggiorna_prenotazione_veicolo(ptr_veicolo ve)
{
    if (!ve) return;
    ptr_prenotazione pren = prendi_prenotazioni(ve);    // PENSO SIA DA TOGLIERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    blocca_celle_passate(pren);
    salva_prenotazioni_su_file(pren, prendi_targa(ve));
    aggiorna_stato_veicolo(ve);
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

 Aggiorna lo stato delle prenotazioni per tutti i veicoli presenti nella tabella hash.

 Implementazione:
    - Scansiona la tabella hash per ottenere tutti i veicoli.
    - Per ciascun veicolo:
        - Richiama `blocca_celle_passate` per bloccare le prenotazioni relative a intervalli temporali già trascorsi.
        - Aggiorna lo stato del veicolo (disponibile / non disponibile) con `aggiorna_stato_veicolo`.

 Parametri:
    h - puntatore alla tabella hash dei veicoli (ptr_hash_veicoli).

 Pre-condizioni:
    - La tabella hash `h` deve essere valida e inizializzata.
    - Le funzioni `blocca_celle_passate` e `aggiorna_stato_veicolo` devono essere definite e funzionanti.

 Post-condizioni:
    - Le prenotazioni passate vengono bloccate.
    - Lo stato di ogni veicolo viene aggiornato in base alle nuove prenotazioni.

 Ritorna:
    - 1 se l'operazione è andata a buon fine.
    - 0 in caso di errore (es. tabella hash vuota o non valida).

 Side-effect:
    - Modifica le strutture di prenotazione e lo stato dei veicoli nella tabella hash.
    - Libera la memoria temporaneamente allocata da `ottieni_valori_hash`.
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
      blocca_celle_passate(pren);
      aggiorna_stato_veicolo(ve);
   }
   free(valori);
   return 1;
}

/*
 Funzione: aggiorna_file_prenotazione_veicoli
 --------------------------------------------

 Salva su file le prenotazioni aggiornate di tutti i veicoli presenti nella tabella hash.

 Implementazione:
    - Scansiona la tabella hash per ottenere tutti i veicoli.
    - Per ciascun veicolo:
        - Ottiene il puntatore alle prenotazioni tramite `prendi_prenotazioni`.
        - Scrive le prenotazioni aggiornate su file utilizzando `salva_prenotazioni_su_file`.

 Parametri:
    h - puntatore alla tabella hash dei veicoli (ptr_hash_veicoli).

 Pre-condizioni:
    - La tabella hash `h` deve essere valida e inizializzata.
    - La funzione `salva_prenotazioni_su_file` deve essere definita e funzionante.

 Post-condizioni:
    - I file di prenotazione associati a ciascun veicolo sono aggiornati.

 Ritorna:
    - 1 se l'operazione è andata a buon fine.
    - 0 in caso di errore (es. tabella hash vuota o non valida).

 Side-effect:
    - Sovrascrive i file di prenotazione per ciascun veicolo.
    - Libera la memoria temporaneamente allocata da `ottieni_valori_hash`.
*/
int aggiorna_file_prenotazione_veicoli(ptr_hash_veicoli h)
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
   
      salva_prenotazioni_su_file(prendi_prenotazioni(ve), prendi_targa(ve) );
      
      
      
   }
   free(valori);
   return 1;
}