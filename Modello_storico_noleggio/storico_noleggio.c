/*
Autore: Roberto Saporoso
Data: 07/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "storico_noleggio.h"
#include "utili/utile.h"


struct storico_noleggio{
    int giorno,
        mese,
        anno,
        ora,
        minuto;
    char tipo_veicolo[50];
    char targa_veicolo[8];
    char nome_utente[50];
    float costo;
    int ora_inizio,
        minuto_inizio,
        ora_fine,
        minuto_fine;
};


/*
 Funzione: inizia_storico_noleggio
 ---------------------------------

 Alloca e inizializza una nuova struttura storico_noleggio con i dati forniti.

 Implementazione:
    Alloca memoria per la struttura, copia le stringhe e imposta tutti i campi con i valori passati.

 Parametri:
    gg: giorno della prenotazione
    mm: mese della prenotazione
    aa: anno della prenotazione
    ora: ora della prenotazione
    minuto: minuto della prenotazione
    tipo_v: stringa che rappresenta il tipo di veicolo
    targa_v: stringa che rappresenta la targa del veicolo
    nome_ut: stringa con il nome dell’utente
    costo: costo totale del noleggio
    inizio_ora: ora di inizio noleggio
    inizio_minuto: minuto di inizio noleggio
    fine_ora: ora di fine noleggio
    fine_minuto: minuto di fine noleggio

 Pre-condizioni:
    Le stringhe tipo_v, targa_v e nome_ut devono essere valide e terminate da '\0'

 Post-condizioni:
    Viene creato un nuovo storico di noleggio con i valori impostati

 Ritorna:
    Puntatore alla struttura storico inizializzata, oppure NULL se fallisce l’allocazione

 Side-effect:
    Alloca memoria dinamicamente
*/
ptr_storico inizia_storico_noleggio( int gg, int mm, int aa, int ora, int minuto ,char *tipo_v, char *targa_v, char *nome_ut, float costo, int inizio_ora, int inizio_minuto, int fine_ora, int fine_minuto)
{
     ptr_storico prenotazione = malloc(sizeof(struct storico_noleggio));
    if(prenotazione){
        strncpy(prenotazione->tipo_veicolo, tipo_v, sizeof(prenotazione->tipo_veicolo) - 1);
        prenotazione->tipo_veicolo[sizeof(prenotazione->tipo_veicolo) - 1] = '\0';

        strncpy(prenotazione->targa_veicolo, targa_v, sizeof(prenotazione->targa_veicolo) - 1);
        prenotazione->targa_veicolo[sizeof(prenotazione->targa_veicolo) - 1] = '\0';

        strncpy(prenotazione->nome_utente, nome_ut, sizeof(prenotazione->nome_utente) - 1);
        prenotazione->nome_utente[sizeof(prenotazione->nome_utente) - 1] = '\0';

        prenotazione->giorno = gg;
        prenotazione->mese = mm;
        prenotazione->anno = aa;
        prenotazione->ora = ora;
        prenotazione->minuto = minuto;

        prenotazione->costo = costo;

        prenotazione->ora_inizio = inizio_ora;
        prenotazione->minuto_inizio = inizio_minuto;
        prenotazione->ora_fine = fine_ora;
        prenotazione->minuto_fine = fine_minuto;


        return prenotazione;

    }

    return NULL;
}


/*
 Funzione: prendi_giorno_noleggiato
 ----------------------------------

 Restituisce il giorno associato al noleggio storico.

 Implementazione:
    Controlla se il puntatore passato non è NULL e ritorna il campo giorno, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il valore intero del giorno se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
*/
int prendi_giorno_noleggiato(ptr_storico pr)
{
    return pr ? pr->giorno : -1;
}


/*
 Funzione: prendi_mese_noleggiato
 -------------------------------

 Restituisce il mese associato al noleggio storico.

 Implementazione:
    Verifica che il puntatore non sia NULL e ritorna il campo mese, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il valore intero del mese se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_mese_noleggiato(ptr_storico pr)
{
    return pr ? pr->mese : -1;
}


/*
 Funzione: prendi_anno_noleggiato
 -------------------------------

 Restituisce l'anno associato al noleggio storico.

 Implementazione:
    Verifica che il puntatore non sia NULL e ritorna il campo anno, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il valore intero dell'anno se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_anno_noleggiato(ptr_storico pr)
{
    return pr ? pr->anno : -1;
}


/*
 Funzione: prendi_ora_noleggiato
 ------------------------------

 Restituisce l'ora associata al noleggio storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo ora, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    L'ora (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_ora_noleggiato(ptr_storico pr)
{
    return pr ? pr->ora : -1;
}

/*
 Funzione: prendi_minuto_noleggiato
 ---------------------------------

 Restituisce il minuto associato al noleggio storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo minuto, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il minuto (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_minuto_noleggiato(ptr_storico pr)
{
    return pr ? pr->minuto : -1;
}

/*
 Funzione: prendi_ora_inizio_noleggiato
 -------------------------------------

 Restituisce l'ora di inizio del noleggio dallo storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo ora_inizio, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    L'ora di inizio (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_ora_inizio_noleggiato(ptr_storico pr)
{
    return pr ? pr->ora_inizio : -1;
}

/*
 Funzione: prendi_minuto_inizio_noleggiato
 ----------------------------------------

 Restituisce il minuto di inizio del noleggio dallo storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo minuto_inizio, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il minuto di inizio (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_minuto_inizio_noleggiato(ptr_storico pr)
{
    return pr ? pr->minuto_inizio : -1;
}


/*
 Funzione: prendi_ora_fine_noleggiato
 -----------------------------------

 Restituisce l'ora di fine del noleggio dallo storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo ora_fine, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    L'ora di fine (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_ora_fine_noleggiato(ptr_storico pr)
{
    return pr ? pr->ora_fine : -1;
}

/*
 Funzione: prendi_minuto_fine_noleggiato
 --------------------------------------

 Restituisce il minuto di fine del noleggio dallo storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo minuto_fine, altrimenti -1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il minuto di fine (intero) se pr è valido, altrimenti -1

 Side-effect:
    Nessuno
 */
int prendi_minuto_fine_noleggiato(ptr_storico pr)
{
    return pr ? pr->minuto_fine : -1;
}

/*
 Funzione: prendi_costo_noleggiato
 --------------------------------

 Restituisce il costo associato al noleggio dallo storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo costo, altrimenti -1.1.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Il costo (float) se pr è valido, altrimenti -1.1

 Side-effect:
    Nessuno
 */
float prendi_costo_noleggiato(ptr_storico pr)
{
    return pr ? pr->costo : -1.1;
}

/*
 Funzione: prendi_targa_veicolo_noleggiato
 ----------------------------------------

 Restituisce la targa del veicolo associato al noleggio dallo storico.

 Implementazione:
    Se il puntatore è valido, ritorna il campo targa_veicolo, altrimenti NULL.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Puntatore a stringa con la targa del veicolo, oppure NULL se pr è NULL

 Side-effect:
    Nessuno
 */
char *prendi_targa_veicolo_noleggiato(ptr_storico pr)
{
    return pr ? pr->targa_veicolo : NULL;
}


/*
 Funzione: prendi_tipo_veicolo_noleggiato
 ---------------------------------------

 Restituisce il tipo di veicolo associato al noleggio dallo storico.

 Implementazione:
    Se il puntatore `pr` è valido, restituisce il campo `tipo_veicolo`, altrimenti NULL.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Puntatore a stringa con il tipo di veicolo, oppure NULL se `pr` è NULL

 Side-effect:
    Nessuno
 */
char *prendi_tipo_veicolo_noleggiato(ptr_storico pr)
{
    return pr ? pr->tipo_veicolo : NULL;
}


/*
 Funzione: prendi_utente_veicolo_noleggiato
 -----------------------------------------

 Restituisce il nome dell'utente associato al noleggio dallo storico.

 Implementazione:
    Se il puntatore `pr` è valido, restituisce il campo `nome_utente`, altrimenti NULL.

 Parametri:
    pr: puntatore a una struttura storico contenente i dati del noleggio

 Pre-condizioni:
    pr può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    Puntatore a stringa con il nome dell'utente, oppure NULL se `pr` è NULL

 Side-effect:
    Nessuno
 */
char *prendi_utente_veicolo_noleggiato(ptr_storico pr)
{
    return pr ? pr->nome_utente : NULL;
}


/*
 Funzione: stampa_storico_noleggio
 --------------------------------

 Stampa su standard output i dettagli di una prenotazione dallo storico noleggi.

 Implementazione:
    Se il puntatore `s` è NULL, stampa un messaggio di errore.
    Altrimenti, stampa data, orario prenotazione, orario utilizzo, tipo e targa veicolo,
    nome utente e costo formattati su più righe.

 Parametri:
    s: puntatore a una struttura `storico_noleggio` contenente i dati della prenotazione

 Pre-condizioni:
    Il puntatore `s` può essere NULL

 Post-condizioni:
    Nessuna modifica allo stato esterno

 Ritorna:
    void

 Side-effect:
    Scrive su standard output (console)
 */
void stampa_storico_noleggio(ptr_storico s)
{
    if (s == NULL) {
        printf("Prenotazione non valida.\n");
        return;
    }
    printf("-------------------------------\n");
    printf("Data: %02d/%02d/%04d\n", s->giorno, s->mese, s->anno);
    printf("Orario prenotazione: %02d:%02d\n", s->ora, s->minuto);
    printf("Orario utilizzo: %d:%d - %d:%d\n", s->ora_inizio, s->minuto_inizio, s->ora_fine, s->minuto_fine);
    printf("Tipo veicolo: %s\n", s->tipo_veicolo);
    printf("Targa veicolo: %s\n", s->targa_veicolo);
    printf("Nome utente: %s\n", s->nome_utente);
    printf("Costo: %.2f Euro\n", s->costo);
    printf("-------------------------------\n\n");
}


//da rivedere!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

bool vedi_se_noleggio_eliminabile(ptr_storico s) 
{
    if (!s) return false;

    int giorno_oggi, mese_oggi, anno_oggi;
    data_attuale(&giorno_oggi, &mese_oggi, &anno_oggi);

    if (prendi_giorno_noleggiato(s) != giorno_oggi ||
        prendi_mese_noleggiato(s) != mese_oggi ||
        prendi_anno_noleggiato(s) != anno_oggi) {
        return false;  // prenotazione non è di oggi
    }

    int ora_corrente, minuto_corrente;
    ottieni_orario_corrente(&ora_corrente, &minuto_corrente);

    int inizio = prendi_ora_inizio_noleggiato(s);
    int minuti_correnti = ora_corrente * 60 + minuto_corrente;
    int minuti_inizio = inizio * 60;

    if ((minuti_inizio - minuti_correnti) < 60) {
        return false;  // meno di un'ora alla prenotazione
    }

    return true;  // è oggi e c'è più di un'ora
}


/*
 Funzione: distruggi_storico_noleggio
 ------------------------------------

 Libera la memoria occupata da una struttura `storico_noleggio`.

 Implementazione:
    Controlla che il puntatore non sia NULL e libera la memoria associata.
    Se in futuro i campi contengono puntatori a memoria dinamica, qui dovrebbero essere liberati.

 Parametri:
    s: puntatore a una struttura `storico_noleggio` da distruggere

 Pre-condizioni:
    s deve essere un puntatore valido o NULL

 Post-condizioni:
    La memoria puntata da s viene liberata

 Ritorna:
    void

 Side-effect:
    Libera memoria dinamica
 */
void distruggi_storico_noleggio(ptr_storico s) 
{
    if (!s) return;
    // se i campi sono statici (char[]), non serve fare altro
    // se in futuro hai char* allocati, li liberi qui
    free(s); // finale: libera la struct
}

