#include "Janitor.h"

/**
 * Adds a pointer to be free'd at any point later in the program.
 * @param d void pointer to be disposed of
 */
void Register_Disposable(void* d){
	if(!GARBAGE_INITIALIZED){
		GARBAGE_INITIALIZED = true;
		GARBAGE_COUNT = 0;
		GARBAGE_CAPACITY = 10;
		GARBAGE = ((void**) malloc(sizeof(void*) * GARBAGE_CAPACITY));
	}
	if(GARBAGE_COUNT == (GARBAGE_CAPACITY - 1)){
		void* newArr = realloc(GARBAGE, (sizeof(void*) * (GARBAGE_CAPACITY * 2)));
		if(newArr){
			GARBAGE = newArr;
		}
	}
	GARBAGE[GARBAGE_COUNT] = d;
	GARBAGE_COUNT++;
}

//Think about shifting instead of using null here and then decrementing
//garbage_count
void Unregister_Disposable(void* d){
	int i = 0;
	while(i < GARBAGE_COUNT){
		if(GARBAGE[i] == d){
			GARBAGE[i] = NULL;
			return;
		}
	}
};

/**
 * Free's all of the Dynamically allocated Data in the program
 */
void Clean_Up(){
	int i = 0, tempCount = GARBAGE_COUNT;
	while(i < GARBAGE_COUNT){
		if(GARBAGE[i] != NULL){
			free(GARBAGE[i]);
			GARBAGE[i] = NULL;
			tempCount--;
		}
		i++;
	}
	GARBAGE_COUNT = tempCount;
	free(GARBAGE);
	GARBAGE = NULL;
	GARBAGE_INITIALIZED = false;
}
