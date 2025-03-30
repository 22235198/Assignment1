CFLAGS = -Wall -pedantic -ansi -g -pthread

sss: main.o array.o thread.o
	gcc main.o array.o thread.o -o sss
	
main.o : main.c array.h thread.h
	gcc $(CFLAGS) -c main.c
	
array.o : array.c array.h 
	gcc $(CFLAGS) -c array.c
	
thread.o : thread.c thread.h
	gcc $(CFLAGS) -c thread.c
	
clean : sss main.o array.o
	rm main.o array.o thread.o sss
