# Nome eseguibile
TARGET = test.exe

# File oggetto
OBJS = test.o ../ADT_array/array_prenotazione.o ../utili/utile_array_prenotazione.o ../utili/utile.o ../Modello_storico_noleggio/storico_noleggio.o ../ADT_hash/hash_veicoli.o ../Modello_veicolo/veicolo.o ../ADT_hash/hash_utenti.o ../Modello_utente/utente.o ../ADT_array/array.o ../ADT_hash/tab_hash.o ../utili/utile_utente.o ../utili/utile_veicolo.o ../ADT_lista/lista_storico_noleggio.o ../utili/utile_lista_storico_noleggio.o ../ADT_lista/lista.o

# Rileva sistema operativo
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    RM = rm -f
    NULLDEV = /dev/null
else ifeq ($(UNAME_S),Darwin)
    RM = rm -f
    NULLDEV = /dev/null
else ifeq ($(OS),Windows_NT)
    RM = del /Q
    NULLDEV = NUL
else
    # Default a Linux-like
    RM = rm -f
    NULLDEV = /dev/null
endif

# Regola per compilare l'eseguibile
$(TARGET): $(OBJS)
	gcc $(OBJS) -o $(TARGET)

# Compilazione singoli .o
test.o: test.c
	gcc -I.. -c test.c -o test.o

../ADT_array/array_prenotazione.o: ../ADT_array/array_prenotazione.c
	gcc -I.. -c ../ADT_array/array_prenotazione.c -o ../ADT_array/array_prenotazione.o

../utili/utile_array_prenotazione.o: ../utili/utile_array_prenotazione.c
	gcc -I.. -c ../utili/utile_array_prenotazione.c -o ../utili/utile_array_prenotazione.o

../utili/utile.o: ../utili/utile.c
	gcc -I.. -c ../utili/utile.c -o ../utili/utile.o

../Modello_storico_noleggio/storico_noleggio.o: ../Modello_storico_noleggio/storico_noleggio.c
	gcc -I.. -c ../Modello_storico_noleggio/storico_noleggio.c -o ../Modello_storico_noleggio/storico_noleggio.o

../ADT_hash/hash_veicoli.o: ../ADT_hash/hash_veicoli.c
	gcc -I.. -c ../ADT_hash/hash_veicoli.c -o ../ADT_hash/hash_veicoli.o

../Modello_veicolo/veicolo.o: ../Modello_veicolo/veicolo.c
	gcc -I.. -c ../Modello_veicolo/veicolo.c -o ../Modello_veicolo/veicolo.o

../ADT_hash/hash_utenti.o: ../ADT_hash/hash_utenti.c
	gcc -I.. -c ../ADT_hash/hash_utenti.c -o ../ADT_hash/hash_utenti.o

../Modello_utente/utente.o: ../Modello_utente/utente.c
	gcc -I.. -c ../Modello_utente/utente.c -o ../Modello_utente/utente.o

../ADT_array/array.o: ../ADT_array/array.c
	gcc -I.. -c ../ADT_array/array.c -o ../ADT_array/array.o

../ADT_hash/tab_hash.o: ../ADT_hash/tab_hash.c
	gcc -I.. -c ../ADT_hash/tab_hash.c -o ../ADT_hash/tab_hash.o

../utili/utile_utente.o: ../utili/utile_utente.c
	gcc -I.. -c ../utili/utile_utente.c -o ../utili/utile_utente.o

../utili/utile_veicolo.o: ../utili/utile_veicolo.c
	gcc -I.. -c ../utili/utile_veicolo.c -o ../utili/utile_veicolo.o

../ADT_lista/lista_storico_noleggio.o: ../ADT_lista/lista_storico_noleggio.c
	gcc -I.. -c ../ADT_lista/lista_storico_noleggio.c -o ../ADT_lista/lista_storico_noleggio.o

../utili/utile_lista_storico_noleggio.o: ../utili/utile_lista_storico_noleggio.c
	gcc -I.. -c ../utili/utile_lista_storico_noleggio.c -o ../utili/utile_lista_storico_noleggio.o

../ADT_lista/lista.o: ../ADT_lista/lista.c
	gcc -I.. -c ../ADT_lista/lista.c -o ../ADT_lista/lista.o

# Pulizia multi-ambiente
clean:
	-$(RM) *.o *.exe > $(NULLDEV) 2>&1
