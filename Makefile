CFLAGS = -Wall -pedantic -ansi -g -pthread

program : main.o array.o
	gcc main.o array.o -o program
	
main.o : main.c array.h
	gcc $(CFLAGS) -c main.c
	
array.o : array.c array.h 
	gcc $(CFLAGS) -c array.c
	
clean : program main.o array.o
	rm main.o array.o program
