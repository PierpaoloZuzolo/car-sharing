car-sharing: main.o array_prenotazione.o hash_utenti.o hash_veicoli.o tab_hash.o lista_storico_noleggio.o lista.o storico_noleggio.o utente.o veicolo.o utile_array_prenotazione.o utile_lista_storico_noleggio.o utile_utente.o utile_veicolo.o utile.o
	gcc main.o array_prenotazione.o hash_utenti.o hash_veicoli.o tab_hash.o lista_storico_noleggio.o lista.o storico_noleggio.o utente.o veicolo.o utile_array_prenotazione.o utile_lista_storico_noleggio.o utile_utente.o utile_veicolo.o utile.o -o main.exe

main.o: main.c
	gcc -Wall -Wextra -std=c99 -Iinclude -c main.c -o main.o


array_prenotazione.o: ADT_array/array_prenotazione.c ADT_array/array_prenotazione.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c ADT_array/array_prenotazione.c -o array_prenotazione.o

hash_utenti.o: ADT_hash/hash_utenti.c ADT_hash/hash_utenti.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c ADT_hash/hash_utenti.c -o hash_utenti.o

hash_veicoli.o: ADT_hash/hash_veicoli.c ADT_hash/hash_veicoli.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c ADT_hash/hash_veicoli.c -o hash_veicoli.o

tab_hash.o: ADT_hash/tab_hash.c ADT_hash/tab_hash.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c ADT_hash/tab_hash.c -o tab_hash.o

lista_storico_noleggio.o: ADT_lista/lista_storico_noleggio.c ADT_lista/lista_storico_noleggio.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c ADT_lista/lista_storico_noleggio.c -o lista_storico_noleggio.o

lista.o: ADT_lista/lista.c ADT_lista/lista.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c ADT_lista/lista.c -o lista.o

storico_noleggio.o: Modello_storico_noleggio/storico_noleggio.c Modello_storico_noleggio/storico_noleggio.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c src/modelli/storico_noleggio.c -o storico_noleggio.o

utente.o: Modello_utente/utente.c Modello_utente/utente.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c Modello_utente/utente.c -o utente.o

veicolo.o: Modello_veicoli/veicolo.c Modello_veicoli/veicolo.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c Modello_veicoli/veicolo.c -o veicolo.o

utile_array_prenotazione.o: utili/utile_array_prenotazione.c utili/utile_array_prenotazione.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c utili/utile_array_prenotazione.c -o utile_array_prenotazione.o

utile_lista_storico_noleggio.o: utili/utile_lista_storico_noleggio.c utili/utile_lista_storico_noleggio.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c utili/utile_lista_storico_noleggio.c -o utile_lista_storico_noleggio.o

utile_utente.o: utili/utile_utente.c utili/utile_utente.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c utili/utile_utente.c -o utile_utente.o

utile.o: utili/utile.c utili/utile.h
	gcc -Wall -Wextra -std=c99 -Iinclude -c utili/utile.c -o utile.o

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
else
    RM = rm -f
    EXE_EXT =
endif

