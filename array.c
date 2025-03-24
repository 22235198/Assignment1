#include "array.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/*
This function takes a text file containing only spaces and integers and 
generates an array of integers, e.g. "1 2 3 4" is converted to {1, 2, 3, 4}.
This function requires the text file to be formatted correctly.
The max size of an array is 200.

Parameters:
char* filename is the name of the text file.
int** array is the address of the int* we will turn into our integer array.
int* size is the address of the int we use to keep track of the array size.

Returns:
A successful execution will return 0.
An unsuccessful execution will return 1.
*/
int generateArray(char* filename, int** array, int* size) {		
                                                          
	FILE* fpointer = fopen(filename, "r");	
	int integer, result, i;
	int arraySize = 0;
	
	if(fpointer == NULL) {
		printf("Failed to open file\n");
		return 1;
	}
	
	/*
	the below while loop itterates through the text file 
	to find how many integers there are, it also 
	checks if text file is formatted correctly.
	*/
	
	while(1) {
		result = fscanf(fpointer, "%d", &integer);
		if(result == 1) {
			arraySize++;
		} else if(result == 0) {
			printf("Text file not formatted correctly\n");
			return 1;
		} else if(result == -1) {
			break;
		}
	}
	
	if(arraySize > 200) {
		printf("Too many integers in the text file\n");
		return 1;
	}
	
	*array = malloc(sizeof(int)*arraySize);
	
	rewind(fpointer);
	
	/*fill our array with the text file values.*/
	for(i = 0; i < arraySize; i++) {
		fscanf(fpointer, "%d", &integer);
		(*array)[i] = integer;
	}
	
	/*keeping track of the array size outside of the function.*/
	*size = arraySize;
	
	return 0;
}

void printArray(int** array, int size) {

	int i;
	
	for(i = 0; i < size; i++) {
		printf("Array[%d]: %d\n", i, (*array)[i]);
	}

}








