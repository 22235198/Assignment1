#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "array.h"
#include "thread.h"

int main(int argc, char* argv[]) {
	
	/*structs hold the parameters for our thread routine*/
	struct ThreadData para1, para2;
	pthread_t t1, t2;
	int sizeOfArray;
	int* myArray;
	/*if condition[2] = {0, 0}, threads t1 and t2 will terminate.*/
	int condition[2] = {1, 1};
	int totalSwaps = 0, swaps1 = 0, swaps2 = 0;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condForChild, NULL);
	
	/*if generateArray does not execute succesfully, terminate the program.*/
	if(generateArray(argv[1], &myArray, &sizeOfArray) == 1) {
		return 1;
	}
	
	/*Initialize thread routine parameteres*/
	para1.array = myArray;
	para1.size = sizeOfArray;
	para1.threadID = 1;
	para1.condition = condition;
	para1.swaps = &swaps1;
	para2.array = myArray;
	para2.size = sizeOfArray;
	para2.threadID = 2;
	para2.condition = condition;
	para2.swaps = &swaps2;
		
	pthread_create(&t1, NULL, threadRoutine, (void*)&para1);
	pthread_create(&t2, NULL, threadRoutine, (void*)&para2);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	totalSwaps = swaps1 + swaps2;
	
	printArray(myArray, sizeOfArray);
	printf("Total number of swaps to sort array: %d.\n", totalSwaps);
	
	free(myArray);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condForChild);

	return 0;
}







