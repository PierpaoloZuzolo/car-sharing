#ifndef UTENTE_H
#define UTENTE_H

#define NULLITEM NULL

typedef struct utente *ptr_utente;

/*
========================================================================
SPECIFICA SINTATTICA E SEMANTICA - ADT UTENTE
========================================================================

Specifica Sintattica

L’ADT utente è definito come un tipo opaco che rappresenta un utente
Vengono definiti i seguenti tipi ed operatori:

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
- utente
Un record che rappresenta una prenotazione ed è definito come
   - char nome[50] -> nome dell'utente
   - char email[100] -> indirizzo email dell'utente

- ptr_utente
puntatore opaco a una struttura contenente le informazioni di un utente: 

-------------------------------------------------------------
Operatori:
-------------------------------------------------------------
- inizia_utente         : (const char *nome, const char *email) -> ptr_utente
- prendi_nome           : (ptr_utente) -> char*
- prendi_email          : (ptr_utente) -> char*
- stampa_utente         : (ptr_utente) -> void
- salva_utente_su_file  : (char *nome_file, ptr_utente) -> void
- carica_utente_da_file : (const char *nome_file, TABELLAHASH) -> void
- libera_utente         : (ptr_utente) -> void

1. ptr_utente inizia_utente (const char *nome, const char *email)
   • Descrizione: Crea un nuovo utente con i dati forniti.
   • Specifica: Restituisce un untente 'nuovo_utente' se 'nuovo_utente' è diverso da NULL.

2. char *prendi_nome (ptr_utente ut)
   • Descrizione: Restituisce il nome dell'utente.
   • Specifica:  Se ut != NULL, restituisce ut->nome, altrimenti restituisce NULLITEM.

3. char *prendi_email (ptr_utente ut)
   • Descrizione: Restituisce l'email dell'utente.
   • Specifica: Se ut != NULL, restituisce ut->email, altrimenti restituisce NULLITEM. 
   
4. void stampa_utente (ptr_utente ut)
   • Descrizione: Stampa a video il nome dell'utente.
   • Specifica: Se ut != NULL, allora stampa ut->nome in output.

5. void salva_utente_su_file (char *nome_file, ptr_utente ut)
   • Descrizione: Salva i dati dell'utente in un file in modalità modifica.
   • Specifica: Se 'nome_file' è un nome di file valido e utente != NULL, allora utente->nome 
                e utente->email vengono scritti su file 'nome_file'.

6. void carica_utente_da_file (const char *nome_file, TABELLAHASH h)
   • Descrizione: Legge gli utenti da file e li inserisce nella tabella hash. 
   • Specifica: Per ogni riga del file 'nome_file' contenente una coppia 'nome' 'email', crea un
                utente con IniziaUtente(nome, email) e lo inserisce in 'h' tramite InserisciHash(h, ut).

7. void libera_utente (ptr_utente ut)
   • Descrizione: Libera la memoria utilizzata da ut. 
   • Specifica: Se ut != NULL, allora la memoria puntata da 'ut' viene liberata con free.

========================================================================
SPECIFICA SEMANTICA

-------------------------------------------------------------
Tipi:
-------------------------------------------------------------
ptr_utente: insieme delle strutture contenenti dati di utente (nome, email)

tabella_hash: struttura contenente l'insieme degli utenti indicizzati tramite hash

char*: sequenza di caratteri terminata da \0

BOOLEANO:{vero, falso}
-------------------------------------------------------------
Per ogni operazione si definiscono precondizioni, postcondizioni ed effetti:

1.    inizia_utente(nome, email) = nuovo_utente
            pre: nome ed email devono essere stringhe valide.
            post: nuovo_utente è inizializzato. 

2.   prendi_nome(ut) = ut->nome

            pre: ut != NULL.
            post: ut->nome è la stringa contenente il nome di ut.

3.    prendi_email(ut) = ut->email
            pre: ut != NULL.
            post: ut->email è la stringa che contiene l'email di ut.

4.    stampa_utente(ut) = void
               pre: ut != NULL.
               post: stampa il nome di ut in output.

5.    salva_utente_su_file(nome_file, ut) = void
               pre: nome_file è il nome di un file esistente, ut != NULL.
               post: salva nome ed email di ut nel file di testo specificato.

6.    carica_utente_da_file(nome_file, h) = void
               pre:  nome_file è il nome di un file leggibile, h è una tabella hash esistente.
               post: tutti gli utenti letti da nome_file sono inseriti nella tabella hash.

7.    libera_utente(ut) = void
               pre: ut != NULL.
               post: libera la memoria associata a ut.

*/

ptr_utente inizia_utente(const char *nome, const char *email);

char *prendi_nome(ptr_utente ut);

char *prendi_email(ptr_utente ut);

void stampa_utente(ptr_utente ut);

void salva_utente_su_file(char *nome_file, ptr_utente ut);

void carica_utente_da_file(const char *nome_file, ptr_hash h);

void libera_utente(ptr_utente ut);



#endif