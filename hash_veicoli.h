#ifndef HASH_VEICOLI_H
#define HASH_VEICOLI_H

#include "veicolo.h"
#include <stdbool.h>



typedef struct tab_hash *ptr_hash_veicolo;

unsigned int hash(char *chiave, int dimensione);

ptr_hash_veicolo nuova_tabella_hash(int dimensione);

bool inserisci_hash(ptr_hash_veicolo h, ptr_veicolo ve);

ptr_veicolo cerca_veicolo(ptr_hash_veicolo h, ptr_veicolo ve);

void distruggi_hash(ptr_hash_veicolo h);

int dimensione_hash(ptr_hash_veicolo h);






#endif