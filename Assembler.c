#include "Assembler.h"

//Still gotta fix the sudo instructions and ones with shifts
//Still gotta figure out how to represent registers with/without ofsetts
//Still gotta deal with the data portion of the document...some type of store
	//->gotta store arrays, addresses, and immediates by name...3 different hashtables i think
//do the symbol table table command
//implement a mechanism for offsets relative to the file in hex

void Store_Data_Section(IO* io, Multi_Store* store){
	io->seek_pattern(io, DATA_SECTION_SIFTER);
	Sifter** sifters = Config_Data_Sifters(store);
	char* result;
	while(result = io->readline(io)){
		int i = 0;
		char* key;
		while(i < DATA_TYPE_COUNT){
			if(key = sifters[i]->Sift(sifters[i], result)){
				//have Sift() return the key...then get the 
				//offset from io and add it to the store here
				printf("%s\n", key);
				break;
			}
			i++;
		}
	}
}


int main(int argc, char* argv[]){
	Sifter** sifters = Config_Text_Sifters();
	IO* io = New_IO("readfile.txt", "r", "writefile.txt", "w");
	Multi_Store* store = New_Multi_Store();
	Store_Data_Section(io, store);



	/*char* instr;
	char* binInstr;
	while(instr = io->readline(io)){
		int i = 0;
		while(i < INSTRUCTION_COUNT){
			if(binInstr = (char*)(sifters[i])->Sift(sifters[i], instr)){
				io->print(io, binInstr);
				break;
			}
			i++;
		}
	}


	int* arr = (int*) New_Array(sizeof(int), 10);
	int i = 0;
	while(i < 10){
		arr[i] = i;
		i++;
	}
	const char* str = "String Arguments";
	int imm = 1234;

	Multi_Store store = *(New_Multi_Store());
	store.add_array(&store, "array", arr, 10);
	store.add_string(&store, "string", str);
	store.add_immediate(&store, "immediate", imm);

	Array_Bundle* arr_result = store.get_array(&store, "array");
	int j = 0;
	while(j < arr_result->length){
		printf("%d : %d\n", j, arr_result->array[j]);
		j++;
	}

	printf("%s\n", store.get_string(&store, "string"));
	printf("%d\n", store.get_immediate(&store, "immediate"));

	printf("this shouldnt work...%s\n", store.get_string(&store, "strdfging"));
	printf("%d\n", store.get_immediate(&store, "immedsfdiate"));*/

	Clean_Up_IO(io);
	Clean_Up();
}
