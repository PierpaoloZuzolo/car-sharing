main.exe: main.o hash.o lista_veicoli.o prenotazione.o utente.o utile_prenotazione.o utile_utente.o utile_veicolo.o utile.o veicolo.o
	gcc main.o hash.o lista_veicoli.o prenotazione.o utente.o utile_prenotazione.o utile_utente.o utile_veicolo.o utile.o veicolo.o -o main.exe

main.o: main.c
	gcc -c main.c -std=c99 -Wall -Wextra

hash.o: hash.c
	gcc -c hash.c -std=c99 -Wall -Wextra

lista_veicoli.o: lista_veicoli.c
	gcc -c lista_veicoli.c -std=c99 -Wall -Wextra

prenotazione.o: prenotazione.c
	gcc -c prenotazione.c -std=c99 -Wall -Wextra

utente.o: utente.c
	gcc -c utente.c -std=c99 -Wall -Wextra

utile_prenotazione.o: utile_prenotazione.c
	gcc -c utile_prenotazione.c -std=c99 -Wall -Wextra

utile_utente.o: utile_utente.c
	gcc -c utile_utente.c -std=c99 -Wall -Wextra

utile_veicolo.o: utile_veicolo.c
	gcc -c utile_veicolo.c -std=c99 -Wall -Wextra

utile.o: utile.c
	gcc -c utile.c -std=c99 -Wall -Wextra

veicolo.o: veicolo.c
	gcc -c veicolo.c -std=c99 -Wall -Wextra

clean:
    rm -f *.o main.exe