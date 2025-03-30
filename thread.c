#include "thread.h"

pthread_mutex_t mutex;
pthread_cond_t condForChild;

/*
This function is designed to be executed concurrently by 2 threads.
The 2 threads take turns executing the sorting() function on an integer
array, our mutex variable ensures only one thread is executing sorting()
on our array at a time, our condition variable ensures each thread executes
sorting() once before allowing the other thread to do so.
*/
void* threadRoutine(void* arg) {
	
	struct ThreadData* para = (struct ThreadData*)arg;
	int localSwaps;
	int index = (para->threadID)-1;
	
	pthread_mutex_lock(&mutex);
	
	/*
	Threads will continue running until condition[0] and condition[1] are both zero.
	This only occurs when both threads have zero local swaps consecutively.
	*/
	while((para->condition[0])+(para->condition[1]) != 0) {
		
		localSwaps = 0;

		localSwaps = sorting(para->threadID, para->array, para->size);
		
		/*add localSwaps to the total amount of swaps*/
		*(para->swaps) = *(para->swaps) + localSwaps;
		
		if(localSwaps == 0) {
			para->condition[index] = 0;
		} else {
			para->condition[index] = 1;
		}
		
		pthread_cond_signal(&condForChild);
		pthread_cond_wait(&condForChild, &mutex);
		
	}
	
	printf("ThreadID%d: total number of swaps = %d.\n", para->threadID, *(para->swaps));

	pthread_cond_signal(&condForChild);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

/*
This function takes an array of integers and swaps the 
positioning of the integers such that larger integers 
are moved towards the end of the array, and lesser 
integers are moved towards the start of the array. 

Parameters:
int threadID determines how the array is modified.
(threadID should be either 1 or 2).
int* array is our array of ints.
int sizeOfArray is the size of our array.

Returns:
The return value of int swaps is the amount of times
this function has swapped the position of two integers.
*/
int sorting(int threadID, int* array, int sizeOfArray) {

	int i, placeholder, length, swaps;
	length = ((sizeOfArray)-1)/2;
	swaps = 0; 
	
	if(threadID == 1) {
		
		for(i = 0; i <= length && (2*i + 1 < sizeOfArray); i++) {
				
			if(array[2*i] > array[2*i+1]) {
				
				placeholder = array[2*i+1];
				array[2*i+1] = array[2*i];
				array[2*i] = placeholder;
				swaps++;
				
			}
			
		}
		
		} else if(threadID == 2) {
			
			for(i = 1; i <= length; i++) {
			
				if(array[2*i-1] > array[2*i]) {
				
					placeholder = array[2*i];
					array[2*i] = array[2*i-1];
					array[2*i-1] = placeholder;
					swaps++;
				
				}

			}
		
		}
		

	return swaps;
}

