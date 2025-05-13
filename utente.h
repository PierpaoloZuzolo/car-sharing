#ifndef UTENTE_H
#define UTENTE_H

#define NULLITEM NULL

typedef struct utente *PtrUtente;

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT PtrUtente
========================================================================

Specifica Sintattica

L’ADT PtrUtente è definito come un tipo opaco che rappresenta un utente
Vengono definiti i seguenti tipi ed operatori:

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
- PtrUtente
    puntatore opaco a una struttura contenente le informazioni di un utente: 
    - char nome[50] -> nome dell'utente
    - char email[100] -> indirizzo email dell'utente
-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- IniziaUtente     : (const char *nome, const char *email) -> PtrUtente
- PrendiNome   : (PtrUtente) -> char*
- PrendiEmail    : (PtrUtente) -> char*
- StampaUtente : (PtrUtente) -> void
- SalvaUtentiSuFile: (char *nome_file, PtrUtente) -> void
- CaricaUtentiDaFile  : (const char *nome_file, TABELLAHASH) -> void
- LiberaUtente: (PtrUtente) -> void

1. PtrUtente IniziaUtente (const char *nome, const char *email)
   • Descrizione: Crea un nuovo utente con i dati forniti.
   • Specifica: Restituisce un untente 'nuovo_utente' se 'nuovo_utente' è diverso da NULL.

2. char* PrendiNome (PtrUtente ut)
   • Descrizione: Restituisce il nome dell'utente.
   • Specifica:  Se ut != NULL, restituisce ut->nome, altrimenti restituisce NULLITEM.

3- char* PrendiEmail (PtrUtente ut)
   • Descrizione: Restituisce l'email dell'utente.
   • Specifica: Se ut != NULL, restituisce ut->email, altrimenti restituisce NULLITEM. 
   
4. void StampaUtente (PtrUtente ut)
   • Descrizione: Stampa a video il nome dell'utente.
   • Specifica: Se ut != NULL, allora stampa ut->nome in output.

5- void SalvaUtenteSuFile (char *nome_file, PtrUtente ut)
   • Descrizione: Salva i dati dell'utente in un file in modalità append.
   • Specifica: Se 'nome_file' è un nome di file valido e utente != NULL, allora utente->nome 
                e utente->email vengono scritti su file 'nome_file'.

6- void CaricaUtentiDaFile (const char *nome_file, TABELLAHASH h)
   • Descrizione: Legge gli utenti da file e li inserisce nella tabella hash. 
   • Specifica: Per ogni riga del file 'nome_file' contenente una coppia 'nome' 'email', crea un
                utente con IniziaUtente(nome, email) e lo inserisce in 'h' tramite InserisciHash(h, ut);

7- void LiberaUtente (PtrUtente ut)
   • Descrizione: Libera la memoria utilizzata da ut. 
   • Specifica: Se ut != NULL, allora la memoria puntata da 'ut' viene liberata con free.

========================================================================
SPECIFICA SEMANTICA

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
PtrUtente: insieme delle strutture contenenti dati di utente (nome, email)

TABELLAHASH: struttura contenente l'insieme degli utenti indicizzati tramite hash

CHAR*: sequenza di caratteri terminata da \0

BOOLEANO:{vero, falso}
-------------------------------------------------------------
Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:

1.    IniziaUtente(nome, email) = nuovo_utente
            pre: nome ed email devono essere stringhe valide.
            post: nuovo_utente è inizializzato. 

2.   PrendiNome(ut) = ut->nome

            pre: ut != NULL
            post: ut->nome è la stringa contenente il nome di ut.

3.    PrendiMail(ut) = ut->email
            pre: ut != NULL
            post: ut->email è la stringa che contiene l'email di ut.

4.    StampaUtente(ut)
               pre: ut != NULL
               post: stampa il nome di ut in output.

5.    SalvaUtentiSuFile(nome_file, ut)
               pre: nome_file è il nome di un file esistente, ut != NULL.
               post: salva nome ed email di ut nel file di testo specificato.

6.    CaricaUtentiDaFile(nome_file, h)
               pre:  nome_file è il nome di un file leggibile, h è una tabella hash esistente.
               post: tutti gli utenti letti da nome_file sono inseriti nella tabella hash.

7.    LiberaUtente(ut)
               pre: ut != NULL.
               post: libera la memoria associata a ut.

*/

PtrUtente IniziaUtente(const char *nome, const char *email);

char *PrendiNome(PtrUtente ut);

char *PrendiEmail(PtrUtente ut);

void StampaUtente(PtrUtente ut);

void SalvaUtenteSuFile(char *nome_file, PtrUtente ut);

void CaricaUtentiDaFile(const char *nome_file, PtrHash h);

void LiberaUtente(PtrUtente ut);



#endif