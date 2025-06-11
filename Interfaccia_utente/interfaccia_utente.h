#ifndef INTERFACCIA_UTENTE_H
#define INTERFACCIA_UTENTE_H

#include "ADT_hash/hash_utenti.h"
#include "Modello_utente/utente.h"
#include "ADT_hash/hash_veicoli.h"
#include "Modello_veicolo/veicolo.h"

ptr_utente gestione_utente(ptr_hash_utenti h);

void avvia_menu_principale(ptr_utente utente, ptr_hash_veicoli hash_veicoli);

ptr_veicolo menu_prenotazione(ptr_hash_veicoli hash_veicoli, char *nome_utente);

void gestione_storico_prenotazioni(char *nome_utente, ptr_hash_veicoli hash_veicoli);

#endif
