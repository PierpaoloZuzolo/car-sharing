#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"
#include "hash.h"

#define DIM_HASH 200



ptr_utente gestione_utente(ptr_hash h);



int main (){
    ptr_hash hash = nuova_tabella_hash(DIM_HASH);
       if (!hash){
           printf("Errore risorse sistema.");
           exit(1);
       }
    ptr_utente ut = gestione_utente(hash);

    distruggi_hash(hash);


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
            return nuovo;
           } 
           
           
        }


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
                printf("Login effettuato! Benvenuto ");
                stampa_utente(trovato);
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

