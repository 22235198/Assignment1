#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "array.h"

pthread_mutex_t mutex;
pthread_cond_t cond;

/*
ThreadData is a struct used to input parameters into sort(void* arg).
e.g. pthread_create(&t1, NULL, sort, (void*)&<nameOfStruct>);
*/
typedef struct ThreadData {
	
	int* array;
	int size;
	int threadID;
	int* condition;
	int* swaps;
	
} ThreadData;

/*
If para->threadData is equal to 1, execute T1 sorting process.
If para->threadData is equal to 2, execute T2 sorting process.
Any other value is invalid.
*/
void* sort(void* arg) {
	
	struct ThreadData* para = (struct ThreadData*)arg;
	int localSwaps, placeholder, i;
	int index = (para->threadID)-1;
	int length = ((para->size)-1)/2;
	
	pthread_mutex_lock(&mutex);
	
	while((para->condition[0])+(para->condition[1]) != 0) {
		
		localSwaps = 0;
	
		if(para->threadID == 1) {
			
			for(i = 0; i <= length && (2*i + 1 < para->size); i++) {
				
				if(para->array[2*i] > para->array[2*i+1]) {
				
					placeholder = para->array[2*i+1];
					para->array[2*i+1] = para->array[2*i];
					para->array[2*i] = placeholder;
					localSwaps++;
				
				}
			
			}
		
		} else if(para->threadID == 2) {
			
			for(i = 1; i <= length; i++) {
			
				if(para->array[2*i-1] > para->array[2*i]) {
				
					placeholder = para->array[2*i];
					para->array[2*i] = para->array[2*i-1];
					para->array[2*i-1] = placeholder;
					localSwaps++;
				
				}
			
			}
		
		}
		
		*(para->swaps) = *(para->swaps) + localSwaps;
		
		printf("Total swaps: %d. Local Swaps from thread %d: %d.\n", *(para->swaps), para->threadID, localSwaps);
		printArray(para->array, para->size);
		
		if(localSwaps == 0) {
			para->condition[index] = 0;
			pthread_cond_signal(&cond);
			pthread_cond_wait(&cond, &mutex);
		} else {
			para->condition[index] = 1;
			pthread_cond_signal(&cond);
			pthread_cond_wait(&cond, &mutex);
		}
		
	}
	
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}


int main(int argc, char* argv[]) {
	
	/*structs hold the parameters for our thread routine*/
	struct ThreadData para1, para2;
	pthread_t t1, t2;
	int sizeOfArray;
	int* myArray;
	int condition[2] = {1, 1};
	int swaps1 = 0, swaps2 = 0;
	
	/*create mutex and cond*/
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	
	
	/*if generateArray does not execute succesfully, terminate the program.*/
	if(generateArray(argv[1], &myArray, &sizeOfArray) == 1) {
		return 1;
	}
	
	printArray(myArray, sizeOfArray);
	
	/*Initialize structs or thread routine parameteres*/
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
		
	/*create threads*/
	pthread_create(&t1, NULL, sort, (void*)&para1);
	pthread_create(&t2, NULL, sort, (void*)&para2);
	
		
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	free(myArray);
	
	/*destroy mutex and cond*/
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	
	printf("Finished\n");

	return 0;
}







