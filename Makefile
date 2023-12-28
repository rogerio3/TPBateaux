# Makefile pour le TP 1 Bateaux

CC = gcc -Wall --std=c99 -c

bateaux: bateaux.o MachineBateaux.o
	gcc -o bateaux bateaux.o MachineBateaux.o

bateaux.o: bateaux.c MachineBateaux.h
	$(CC) bateaux.c

MachineBateaux.o: MachineBateaux.c MachineBateaux.h
	$(CC) MachineBateaux.c

clean:
	rm -f *~ *.o bateaux
