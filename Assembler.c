#include "Assembler.h"

//Still gotta do ALL IO
//Still gotta fix the sudo instructions and ones with shifts
//Still gotta figure out how to represent registers with/without ofsetts
//Still gotta deal with the data portion of the document...some type of store

int main(int argc, char* argv[]){
	Sifter** sifters = Config_Sifters();
	IO* io = New_IO("readfile.txt", "r", "writefile.txt", "w");

	char* instr;
	char* binInstr;
	while(instr = io->readline(io)){
		printf("%s\n", instr);
		int i = 0;
		while(i < INSTRUCTION_COUNT){
			if(binInstr = (char*)(sifters[i])->Sift(sifters[i], instr)){
				printf("%s\n", binInstr);
				io->print(io, binInstr);
				break;
			}
			i++;
		}
	}

	Clean_Up_IO(io);
	Clean_Up();
}
