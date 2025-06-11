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


#define DIM_HASH_UTENTI 200
#define DIM_HASH_VEICOLI 150

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

    carica_veicoli_da_file("txt/Veicoli/veicoli.txt", hash_veicoli);

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
