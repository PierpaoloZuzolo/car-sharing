main.exe: main.o tab_hash.o hash_utenti.o hash_veicoli.o array_prenotazione.o utente.o utile_array_prenotazione.o utile_utente.o utile_veicolo.o utile.o veicolo.o storico_noleggio.o lista_storico_noleggio.o lista.o utile_lista_storico_noleggio.o
	gcc main.o tab_hash.o hash_utenti.o hash_veicoli.o array_prenotazione.o utente.o utile_array_prenotazione.o utile_utente.o utile_veicolo.o utile.o veicolo.o storico_noleggio.o lista_storico_noleggio.o lista.o utile_lista_storico_noleggio.o -o main.exe

main.o: main.c
	gcc -c main.c -std=c99 -Wall -Wextra

tab_hash.o: tab_hash.c
	gcc -c tab_hash.c -std=c99 -Wall -Wextra

hash_utenti.o: hash_utenti.c
	gcc -c hash_utenti.c -std=c99 -Wall -Wextra

hash_veicoli.o: hash_veicoli.c
	gcc -c hash_veicoli.c -std=c99 -Wall -Wextra

array_prenotazione.o: array_prenotazione.c
	gcc -c array_prenotazione.c -std=c99 -Wall -Wextra

utente.o: utente.c
	gcc -c utente.c -std=c99 -Wall -Wextra

utile_array_prenotazione.o: utile_array_prenotazione.c
	gcc -c utile_array_prenotazione.c -std=c99 -Wall -Wextra

utile_utente.o: utile_utente.c
	gcc -c utile_utente.c -std=c99 -Wall -Wextra

utile_veicolo.o: utile_veicolo.c
	gcc -c utile_veicolo.c -std=c99 -Wall -Wextra

utile.o: utile.c
	gcc -c utile.c -std=c99 -Wall -Wextra

veicolo.o: veicolo.c
	gcc -c veicolo.c -std=c99 -Wall -Wextra

storico_noleggio.o: storico_noleggio.c
	gcc -c storico_noleggio.c -std=c99 -Wall -Wextra

lista_storico_noleggioi.o: lista_storico_noleggio.c
	gcc -c lista_storico_noleggio.c -std=c99 -Wall -Wextra

lista.o: lista.c
	gcc -c lista.c -std=c99 -Wall -Wextra

utile_lista_storico_noleggio.o: utile_lista_storico_noleggio.c
	gcc -c utile_lista_storico_noleggio.c -std=c99 -Wall -Wextra

clean:
	rm -f *.o main.exe
