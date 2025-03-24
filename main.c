#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "array.h"

int main(int argc, char* argv[]) {
	
	int sizeOfArray;
	int* myArray;
	
	/*if generateArray does not execute succesfully, terminate the program.*/
	if(generateArray(argv[1], &myArray, &sizeOfArray) == 1)
		return 1;
	
	printArray(&myArray, sizeOfArray);
	
	free(myArray);

	return 0;
}
