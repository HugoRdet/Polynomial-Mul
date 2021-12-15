CC=gcc -Ofast -Wall


all: exo1

fonctions_utilitaires.o : fonctions_utilitaires.c 
	$(CC)  -c fonctions_utilitaires.c

algorithmes.o : algorithmes.c fonctions_utilitaires.h
	$(CC)  -c algorithmes.c

exo1.o : exo1.c fonctions_utilitaires.h algorithmes.h
	$(CC)  -c exo1.c

exo1: exo1.o fonctions_utilitaires.o algorithmes.o
	$(CC) -o exo1 exo1.o fonctions_utilitaires.o algorithmes.o



clean:
	rm -f *.o 
	