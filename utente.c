#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utente.h"
#include "hash.h"


struct utente{
    char nome[50];
    char email[100];
};



// funzione per creare e inizializzare una variabile di tipo utente
PtrUtente IniziaUtente(const char *nome, const char *email)
{
    PtrUtente nuovo_utente = malloc(sizeof(struct utente));
    if(nuovo_utente){
        strncpy(nuovo_utente->nome, nome, sizeof(nuovo_utente->nome) - 1);
        nuovo_utente->nome[sizeof(nuovo_utente->nome) - 1] = '\0';
        strncpy(nuovo_utente->email, email, sizeof(nuovo_utente->email) - 1);
        nuovo_utente->email[sizeof(nuovo_utente->email) - 1] = '\0';

    } return nuovo_utente;

   
}

// funzione per restituire la variabile nome dalla struttura utente
char *PrendiNome(PtrUtente ut)
{
    return ut ? ut->nome : NULLITEM; // se utente non è NULL restituisce il nome
}

// funzione per restituire la variabile email dalla struttura utente
char *PrendiEmail(PtrUtente ut)
{
    return ut ? ut->email : NULLITEM;
}


void StampaUtente(PtrUtente ut)
{
    if(ut){
        printf("%s", ut->nome);
    }
}


void SalvaUtenteSuFile(char *nome_file, PtrUtente ut)
{
    FILE *file = fopen(nome_file, "a");
    if (file && ut){ // vede se file e utente sono diversi da NULL
        fprintf(file, "%s %s\n", ut->nome, ut->email);
        fclose(file);
    } else printf("\nErrore salvataggio...");
        
    
}

void CaricaUtentiDaFile(const char *nome_file, PtrHash h)
{
    FILE *file = fopen(nome_file, "r");
    if(!file){
        return;
    }

    char nome[50],
         email[100];
    while(fscanf(file, "%50s %100s", nome, email) == 2){
        InserisciHash(h, IniziaUtente(nome, email));
    }
}


void LiberaUtente(PtrUtente ut)
{
    if(ut){
         free(ut);
    }
   
}