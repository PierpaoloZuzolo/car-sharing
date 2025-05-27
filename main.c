#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"
#include "hash.h"
#include "lista_veicoli.h"
#include "veicolo.h"
#include "prenotazione.h"
#include "utile.h"
#include "utile_utente.h"
#include "utile_prenotazione.h"
#include "utile_veicolo.h"

#define DIM_HASH 200



ptr_utente gestione_utente(ptr_hash h);

ptr_veicolo menu_prenotazione(ptr_lista lista);




int main (){
    ptr_hash hash = nuova_tabella_hash(DIM_HASH);
       if (!hash){
           printf("Errore risorse sistema.");
           exit(1);
       }
    ptr_utente ut = gestione_utente(hash);

    distruggi_hash(hash);

    ptr_lista lista = nuova_lista();
       if(!lista){
           printf("Errore risorse sistema.");
           exit(1);
       }

    ptr_veicolo ve = menu_prenotazione(lista);
    if(ve){

    }

    return 0;


}










ptr_utente gestione_utente(ptr_hash h)
{
    char nome[50], email[100];

   

    carica_utente_da_file("utenti.txt", h);

    int scelta;

    while(1){
        printf("\n====MENU====");
        printf("\nCosa vuoi fare?\n1. Registrazione\n2. Login\n0. Esci\nScelta: ");
        scanf("%d", &scelta);

        if(0 == scelta){ //Uscita programma
            

            printf("\nHai scelto di uscire. Programma terminato.\n");
            exit(0);
        }

        if(1 == scelta){ //Registrazione
           printf("\nInserisci nome: ");
           scanf("%49s", nome);
           printf("\nInserisci email: ");
           scanf("%99s", email);
        /*
           if(verifica_duplicati_utenti(h, nome, email)){
            printf("Nome utente o mail non validi, utente già inserito. \n");
            continue;  
           }
           */
           ptr_utente nuovo = inizia_utente(nome, email); //inizializzazione variabile utente
           if (!nuovo){
            printf("\nErrore risorse sistema.");
            exit(1);
           }

           if(inserisci_hash(h, nuovo)){
            salva_utente_su_file("utenti.txt", nuovo);
            printf("\nRegistrazione effettuata");
            printf("Benvenut* ");
                stampa_utente(nuovo);
                printf("\n");
            return nuovo;
           } 
           
           
        }

        //DA FARE: per il login deve essere richiesto solo il nome
        if(2 == scelta){ //Login
            printf("\nInserisci nome: ");
           scanf("%49s", nome);
           printf("\nInserisci email: ");
           scanf("%99s", email);

           ptr_utente temp = inizia_utente(nome, email);
           if(!temp){
            printf("\nErrore risorse sistema.");
            exit(1);
           }
            ptr_utente trovato = cerca_utente(h, temp);
            libera_utente(temp);

            if(trovato){
                printf("Login effettuato! Benvenut* ");
                stampa_utente(trovato);
                printf("\n");
                return trovato;
            } else{
                printf("\nCredenziali non valide.");
            }
           } 
           
           else {
            printf("\nScelta non valida, riformulare.");
         
        }

    }

}



ptr_veicolo menu_prenotazione(ptr_lista lista)
{

    

    carica_veicoli_da_file("veicoli.txt", lista);

    if(vedi_se_giorno_nuovo()){
         int giorno, mese, anno;

        data_attuale(&giorno, &mese, &anno);
    
        FILE *f = fopen("ultimo_avvio.txt", "w");
        if (f) {
         fprintf(f, "%d %d %d", giorno, mese, anno);
         fclose(f);
         
        }
    }




    stampa_lista_veicoli(lista);

    printf("Seleziona l'indice del veicolo da prenotare ( es. 1): ");
    int scelta_veicolo;
    scanf("%d", &scelta_veicolo);

    ptr_veicolo ve = trova_veicolo_lista(scelta_veicolo, lista);
    if(!ve){
        printf("veicolo non trovato.");
        return NULL;
    }

    int inizio = leggi_cella_da_orario("Inserisci orario di inizio");
    int fine = leggi_cella_da_orario("Inserisci orario di fine");

    if(prenota_intervallo(prendi_prenotazioni(ve), inizio, fine)){
        salva_prenotazioni_su_file(prendi_prenotazioni(ve), prendi_targa(ve));
        if(aggiorna_stato_veicolo(ve)){
            rimuovi_veicolo_non_disponibile(lista);
        }

        printf("Prenotazione per veicolo [%s] completata.\n", prendi_targa(ve));
        return ve;
    } else {
        printf("Impossibile effettuare la prenotazione.\n");
        return NULL;
    }


}


