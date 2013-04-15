#include "Assembler.h"



int main(int argc, char* argv[]){
	Sifter** sifters = Config_Sifters();

	printf("%s\n", (sifters[0])->Sift(sifters[0], "add 1, 2, 3"));
	printf("%s\n", (sifters[1])->Sift(sifters[1], "sub 11111, 22222, 33333"));

	Clean_Up();

}
