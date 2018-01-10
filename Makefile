jeu: main.o structure.o
	gcc -o jeu main.o structure.o 

main.o: main.c structure.h
	gcc -c main.c -o main.o -Wall
  
structure.o: structure.c structure.h
	gcc -c structure.c -o structure.o -Wall