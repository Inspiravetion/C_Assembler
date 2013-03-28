#include "Array_Factory.h"

void* New_Array(int typeSize, int Sz){
	printf("In New_Array()...\n");
	void* temp = malloc( typeSize * Sz );
	if(temp){
		Register_Disposable(temp);
		//this may still be a bad idea
		printf("About to return temp*...\n");
		return temp;
	}
	return NULL;
};

bool Extend_Array(void** arrP, int typeSize, int size){
	printf("In Extend_Array()...\n");
	void* newArr = realloc(*arrP, (typeSize * size));
	if(!newArr){
		return false;
	}
	else if(newArr == *arrP){
		//same pointer...
		//DONT re-register...
		return true;
	}
	else{
		//different pointers...
		//unregister old...
		//register new...
		Unregister_Disposable(*arrP);
		Register_Disposable(newArr);
		arrP = &newArr;
		return true;
	}
};