#include "Store.h"

static int tableSizes[16] = {4,1019, 2027, 4079, 8123, 16267, 32503, 65011, 
	130027, 260111, 520279, 1040387, 2080763, 4161539, 8323151, 16646323};
 
#define LOADFACTOR .7

int hash(const char* key, int sizeIndex){
	int output = 0;
	int length = strlen(key);
	int i = 0;
	while(i < length){
		output = (output << 4) + key[i]; //this may not work
		int hiBits = output & 0xF0000000;
		if(hiBits){
			output ^= hiBits >> 24;
			output &= ~hiBits;
		}
		i++;
	}
	return output %tableSizes[sizeIndex];
};


bool put(Store* self, const char* key, int value){

};

int get(Store* self, const char* key){

};

Store* New_Store(){

};