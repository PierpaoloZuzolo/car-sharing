# Nome eseguibile
TARGET = test.exe

# File oggetto
OBJS = test.o ../ADT_array/array_prenotazione.o ../utili/utile_array_prenotazione.o ../utili/utile.o ../Modello_storico_noleggio/storico_noleggio.o

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

# Pulizia multi-ambiente
clean:
	-$(RM) *.o *.exe > $(NULLDEV) 2>&1
