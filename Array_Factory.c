#include "Array_Factory.h"

void* New_Array(int typeSize, int Sz){
	void* temp = malloc( typeSize * Sz );
	if(temp){
		Register_Disposable(temp);
		//this may still be a bad idea
		return temp;
	}
	return NULL;
};

bool Extend_Array(void** arrP, int typeSize, int size){
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