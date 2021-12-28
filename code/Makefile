CC=gcc -Ofast -Wall


all: exo1

fonctions_utilitaires.o : fonctions_utilitaires.c 
	$(CC)  -c fonctions_utilitaires.c

algorithmes.o : algorithmes.c algorithmes.h
	$(CC)  -c algorithmes.c

test.o : test.c test.h
	$(CC)  -c test.c

exo1.o : exo1.c fonctions_utilitaires.h algorithmes.h
	$(CC)  -c exo1.c

exo1: exo1.o fonctions_utilitaires.o algorithmes.o test.o
	$(CC) -o exo1 exo1.o test.o fonctions_utilitaires.o algorithmes.o



clean:
	rm -f *.o 
	