#include "Store.h"

///////////////////////////////////////////////////////////////////////////////
// 																			 //
// Global Definitions 														 //
// 																			 //
///////////////////////////////////////////////////////////////////////////////

static int tableSizes[16] = {7, 1019, 2027, 4079, 8123, 16267, 32503, 65011, 
	130027, 260111, 520279, 1040387, 2080763, 4161539, 8323151, 16646323};
 
#define LOADFACTOR 0.7f

///////////////////////////////////////////////////////////////////////////////
// 																			 //
// Store_Bundle Functions													 //
// 																			 //
///////////////////////////////////////////////////////////////////////////////

Store_Bundle* New_Store_Bundle(const char* key, intptr_t value){
	Store_Bundle* bundle = (Store_Bundle*) malloc(sizeof(Store_Bundle));
	bundle->key = key;
	bundle->val = value;
	Register_Disposable(bundle);
	return bundle;
};

///////////////////////////////////////////////////////////////////////////////
// 																			 //
// Store Functions															 //
// 																			 //
///////////////////////////////////////////////////////////////////////////////

int hash(const char* key, int sizeIndex){
	int output = 0;
	int length = strlen(key);
	int i = 0;
	while(i < length){
		output = (output << 4) + key[i]; 
		int hiBits = output & 0xF0000000;
		if(hiBits){
			output ^= hiBits >> 24;
			output &= ~hiBits;
		}
		i++;
	}
	return output % tableSizes[sizeIndex];
};

void resize(Store* self){
	self->sizeIndex++;
	Store_Bundle** temp = self->table;
	self->table = (Store_Bundle**) 
		New_Nulled_Array(sizeof(Store_Bundle*), tableSizes[self->sizeIndex]);
	if(self->table){
		int i = 0;
		while(i < tableSizes[self->sizeIndex - 1]){
			if(temp[i]){
				int index = hash(temp[i]->key, self->sizeIndex);
				self->table[index] = temp[i];
			}
			i++;
		}
		self->capacity = tableSizes[self->sizeIndex];
	}
	else{
		printf("resizing store array did not work\n");
	}
};

bool put(Store* self, const char* key, intptr_t value){
	int index     = hash(key, self->sizeIndex);
	bool inserted = false;
	bool finished = false;
	int count     = 0;
	while(!finished){
		if(self->table[index] == NULL){
			self->table[index] = New_Store_Bundle(key, value);
			inserted = true;
			finished = true;
			self->usage++;
		}
		else if(strcmp(self->table[index]->key, key) == 0){ 
			inserted = false;
			finished = true;
		}
		if(!inserted){
			count++;
		}
		index = ((index + (((count * count) + count) / 2))
			% tableSizes[self->sizeIndex]);
	}
	if(inserted && 
		((int) (LOADFACTOR * 100) <= 
		((int) ((float) (((float) self->usage) / 
		tableSizes[self->sizeIndex]) * 100)))){
		resize(self);
	}
	return inserted;
};

intptr_t get(Store* self, const char* key){
	int index = hash(key, self->sizeIndex);
	int count = 0;
	bool finished = false;
	while(!finished){
		if(!(self->table[index])){
			return NULL;
		}
		if(strcmp(self->table[index]->key, key) == 0){
			return self->table[index]->val;
		}
		else{
			count++;
			index = ((index + (((count * count) + count) / 2))
				% tableSizes[self->sizeIndex]);
		}
	}
	return NULL;
};

void display(Store* store){
	int i = 0;
	printf(" %-s       |    %s\n", "Symbol", "Address");
	printf("---------------------------\n");
	while(i < store->capacity){
		if(store->table[i]){
			printf("[%-12s : 0x%08X]\n", store->table[i]->key, ((int*) store->table[i]->val)[0]);
		}
		i++;
	}
}

Store* New_Store(){
	Store* store = (Store*) malloc(sizeof(Store));
	store->sizeIndex = 0;
	store->capacity = tableSizes[store->sizeIndex];
	store->usage = 0;
	store->put = &put;
	store->get = &get;
	store->display = &display;
	store->table = (Store_Bundle**) 
		New_Nulled_Array(sizeof(Store_Bundle*), tableSizes[store->sizeIndex]);
	Register_Disposable(store);
	return store;
};