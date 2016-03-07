
CFLAGS= -Wall -g
all: main
main: main.o pokemonDB.o 
	gcc $(CFLAGS) main.o pokemonDB.o -o main

main.o:
	gcc $(CFLAGS) -c main.c 

pokemonDB.o:
	gcc $(CFLAGS) -c pokemonDB.c

clean:
	rm *.o
