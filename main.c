#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utente.h"
#include "hash.h"

#define DIM_HASH 200



PtrUtente gestione_utente(PtrHash h);



int main (){
    PtrHash hash = NuovaTabellaHash(DIM_HASH);
       if (!hash){
           printf("Errore risorse sistema.");
           exit(1);
       }
    PtrUtente ut = gestione_utente(hash);

    DistruggiHash(hash);


    return 0;
}










PtrUtente gestione_utente(PtrHash h)
{
    char nome[50], email[100];

   

    CaricaUtentiDaFile("utenti.txt", h);

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

           if(verifica_duplicati_utenti(h, nome, email)){
            printf("Nome utente o mail non validi, utente già inserito. \n");
            continue;  
           }

           PtrUtente nuovo = IniziaUtente(nome, email); //inizializzazione variabile utente
           if (!nuovo){
            printf("\nErrore risorse sistema.");
            exit(1);
           }

           if(InserisciHash(h, nuovo)){
            SalvaUtentiSuFile("utenti.txt", nuovo);
            printf("\nRegistrazione effettuata");
            return nuovo;
           } else {
            printf("\nErrore salvataggio...");
           }
           
           
        }


        if(2 == scelta){ //Login
            printf("\nInserisci nome: ");
           scanf("%49s", nome);
           printf("\nInserisci email: ");
           scanf("%99s", email);

           PtrUtente temp = IniziaUtente(nome, email);
           if(!temp){
            printf("\nErrore risorse sistema.");
            exit(1);
           }
            PtrUtente trovato = CercaUtente(h, temp);
            LiberaUtente(temp);

            if(trovato){
                printf("Login effettuato! Benvenuto ");
                StampaUtente(trovato);
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

