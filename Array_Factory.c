#include "Array_Factory.h"

void* New_Array(int typeSize, int Sz){
	void* temp = malloc( typeSize * Sz );
	if(temp){
		Register_Disposable(temp);
		return temp;
	}
	return NULL;
};

void* New_Nulled_Array(int typeSize, int Sz){
	void* temp = calloc(typeSize, Sz);
	if(temp){
		Register_Disposable(temp);
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
		return true;
	}
	else{
		Unregister_Disposable(*arrP);
		Register_Disposable(newArr);
		arrP = &newArr;
		return true;
	}
};