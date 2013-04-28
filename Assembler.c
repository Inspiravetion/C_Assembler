#include "Assembler.h"

//figure out of the IS_REG_WITH_OFFSET should be removed
//from RESOLVE_EXP()
//handle command line...test
//be able to dump the .data section...be glad you didn't delete all that other code


void Store_Symbols(IO* io, Multi_Store* store){
	io->seek_pattern(io, New_Sifter(store, BEG_OF_FILE, &RETURN_KEY));
	Sifter** sifters = Config_Data_Sifters(store);
	Sifter* trimmer = New_Sifter(store, HASH_COMMENT_TRIMMER_REGEX, &RETURN_KEY);
	char* result;
	bool isInstr;
	bool inTextSection = true;
	while(result = io->readline(io, trimmer)){
		if(DATA_SECTION_SIFTER->Sift(DATA_SECTION_SIFTER, result)){
			store->reset_offset(store);
			inTextSection = false;
		}
		isInstr = true;
		int i = 0;
		while(i < DATA_TYPE_COUNT){
			if(sifters[i]->Sift(sifters[i], result)){
				isInstr = false;
				break;
			}
			i++;
		}
		if(inTextSection && isInstr){
			store->increment_offset(store, 4);
		}
	}
	io->in_rewind(io);
};

void display_symbol_table(Multi_Store* store){
	store->display_label_table(store);
};

void dump_array(Array_Bundle* bundle, IO* io){
	int i = 0;
	while(i < bundle->length){
		printf("%s\n", intToBinaryString(bundle->array[i], 32));
		i++;
	}
}

void dump_string(char* string, IO* io){
	int length = strlen(string);
	int i = 0;
	int count = 0;
	char* line = (char*) New_Array(sizeof(char), 33);
	while(i < length){
		strcat(line, intToBinaryString((int) string[i], 8));
		printf("%c\n", string[i]);
		count = (count++ % 4);
		if(count == 4){
			printf("%s\n", line);
			line = (char*) New_Array(sizeof(char), 33);
		}
		i++;
	}
	//do something with length of line for padding 0000
	//should be 4...for 4 - length concatenate 0000 to the end

}

void dump_immediate(int imm, IO* io){

}

void dump_data_section(Multi_Store* store, IO* io){
	char** labels = store->get_label_keys(store);
	int i = 0;
	Array_Bundle* bundle;
	char* result;
	while(i < store->label_keys_usage){
		printf("%d : %s\n", i, labels[i]);
		if(bundle = store->get_array(store, labels[i])){
			dump_array(bundle, io);
		}
		else if(result = store->get_string(store, labels[i])){
			dump_string(result, io);
		}
		i++;
	}
}


int main(int argc, char* argv[]){
	IO* io = New_IO("adder.txt", "r", "writefile.txt", "w");
	Multi_Store* store = New_Multi_Store();
	Sifter** sifters = Config_Text_Sifters(store);
	store_registers(store);
	init_exp_sifters(store);
	Store_Symbols(io, store);

	display_symbol_table(store);
	dump_data_section(store, io);

	char* instr;
	char* binInstr;
	while(instr = io->readline(io, NULL)){
		int i = 0;
		while(i < INSTRUCTION_COUNT){
			if(binInstr = (char*)(sifters[i])->Sift(sifters[i], instr)){
				// printf("%s\n", binInstr);
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
