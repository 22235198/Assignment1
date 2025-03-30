#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stdio.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t condForChild;

void* threadRoutine(void* arg);
int sorting(int threadID, int* array, int sizeOfArray);

/*
ThreadData is a struct used to input parameters into the function
threadRoutine(void* arg).
e.g. We have a pthread_t variable called t1 and a struct ThreadData
called para1, we can get thread t1 to execute threadRoutine(void* arg)
via the instruction: pthread_create(&t1, NULL, threadRoutine, (void*)&para1);.
*/
typedef struct ThreadData {
	
	int* array;
	int size;
	int threadID;
	int* condition;
	int* swaps;
	
} ThreadData;

#endif
