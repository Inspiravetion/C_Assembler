#include "Assembler.h"

//Still gotta fix the sudo instructions and ones with shifts
//Still gotta figure out how to represent registers with/without ofsetts
//implement a mechanism for offsets relative to the file in hex

void Store_Data_Section(IO* io, Multi_Store* store){
	io->seek_pattern(io, DATA_SECTION_SIFTER);
	Sifter** sifters = Config_Data_Sifters(store);
	char* result;
	int begOfLine = io->get_curr_offset(io);
	while(result = io->readline(io)){
		int i = 0;
		char* key;
		while(i < DATA_TYPE_COUNT){
			if(key = sifters[i]->Sift(sifters[i], result)){
				store->add_immediate(store, key, DATA_SECTION_BASE_ADDRESS + begOfLine);
				break;
			}
			i++;
		}
		begOfLine = io->get_curr_offset(io);
	}
	io->in_rewind(io);
};

void display_symbol_table(Multi_Store* store){
	store->display_immediate_table(store);
};


int main(int argc, char* argv[]){
	IO* io = New_IO("readfile.txt", "r", "writefile.txt", "w");
	Multi_Store* store = New_Multi_Store();
	Sifter** sifters = Config_Text_Sifters(store);
	Store_Data_Section(io, store);

	display_symbol_table(store);

	char* instr;
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

	/*
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
