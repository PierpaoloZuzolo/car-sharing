/*
Autore: Carmine Saporoso
Data: 13/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "veicolo.h"
#include "array_prenotazione.h"
#include "utile_veicolo.h"
#include "utile_array_prenotazione.h"
#include "hash_veicoli.h"


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

 Legge da file le informazioni relative ai veicoli e li inserisce nella tabella hash.

 Implementazione:
    Apre il file indicato dal nome.
    Per ogni riga del file, legge marca, modello, targa e posizione di un veicolo.
    Crea una nuova struttura veicolo con `inizia_veicolo` e la inserisce nella hash table con `inserisci_veicolo_in_hash`.
    Se il file non può essere aperto, stampa un messaggio di errore ed esce dal programma.

 Parametri:
    nome_file: stringa contenente il nome del file da cui leggere i dati dei veicoli
    h: puntatore alla tabella hash in cui inserire i veicoli

 Pre-condizioni:
    `nome_file` deve essere una stringa valida e non NULL.
    `h` deve essere un puntatore valido a una tabella hash inizializzata.

 Post-condizioni:
    Tutti i veicoli letti dal file vengono inseriti nella tabella hash.

 Ritorna:
    Nessun valore di ritorno (void)

 Side-effect:
    Apre un file in lettura.
    Alloca memoria dinamica per ogni veicolo letto.
    In caso di errore nell'apertura del file, termina il programma con `exit(1)`.
 */
void carica_veicoli_da_file(const char *nome_file, ptr_hash_veicoli h)
{
    FILE *file = fopen(nome_file, "r");
    if(!file){
        printf("!!!VEICOLI NON DISPONIBILI!!!");
        exit(1);
    }

    char marca[30], modello[40], targa[8], posizione[60];
    while(fscanf(file, "%30s %40s %8s %60s", marca, modello, targa, posizione) == 4){
        inserisci_veicolo_in_hash(h, inizia_veicolo(marca, modello, targa, posizione));
    }
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
        libera_prenotazioni(prendi_prenotazioni(ve));
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
    ptr_prenotazione pren = prendi_prenotazioni(ve);
    blocca_celle_passate(pren);
    salva_prenotazioni_su_file(pren, prendi_targa(ve));
    aggiorna_stato_veicolo(ve);
}
