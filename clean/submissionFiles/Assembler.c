#include "Assembler.h"

//figure out of the IS_REG_WITH_OFFSET should be removed
//from RESOLVE_EXP()
//handle command line...test
//recognizing "\0" as a valid string (two null terminators)
//being able to store anything within the "" of a data section
//might have to add 1 instead of sub 1 from positive offset

void Store_Symbols(IO* io, Multi_Store* store, Sifter*  trimmer){
	io->seek_pattern(io, New_Sifter(store, BEG_OF_FILE, &RETURN_KEY));
	Sifter** sifters = Config_Data_Sifters(store);
	Sifter** doubleSifters = Config_Double_Sifters(store);
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
			int j = 0;
			bool twoLines = false;
			while(j < DOUBLE_INSTRUCTION_COUNT){
				if(doubleSifters[j]->Sift(doubleSifters[j], result)){
					twoLines = true;
					break;
				}
				j++;
			}
			if(twoLines){
				store->increment_offset(store, 8);
			}
			else{
				store->increment_offset(store, 4);									
			}
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
		io->print(io, intToBinaryString(bundle->array[i], 32));
		i++;
	}
}

void dump_string(char* string, IO* io){
	int length = strlen(string);
	printf("-%s-\n", string);
	printf("%d\n", length);
	int i = 0;
	int count = 0;
	char** temp_container = (char**) New_Array(sizeof(char*), 4);
	char* line = (char*) New_Array(sizeof(char), 33);
	while(i < length){
		temp_container[i % 4] = intToBinaryString((int) string[i], 8);
		count = (count++ % 4);
		if(count == 4){
			strcat(line, temp_container[3]);
			strcat(line, temp_container[2]);
			strcat(line, temp_container[1]);
			strcat(line, temp_container[0]);
			io->print(io, line);
			line = (char*) New_Array(sizeof(char), 33);
		}
		i++;
	}
	if(length % 4 > 0){
		int j = 0;
		while(j < 4 - (length % 4)){
			temp_container[i % 4] = "00000000";
			i++;
			j++;
		}
		strcat(line, temp_container[3]);
		strcat(line, temp_container[2]);
		strcat(line, temp_container[1]);
		strcat(line, temp_container[0]);
		io->print(io, line);
	}
}

void dump_immediate(int imm, IO* io){
	io->print(io, intToBinaryString(imm, 32));
}

void dump_data_section(Multi_Store* store, IO* io){
	io->print(io, "");
	char** labels = store->get_label_keys(store);
	int i = 0;
	Array_Bundle* arrResult;
	char* strResult;
	Immediate_Bundle* intResult;
	while(i < store->label_keys_usage){
		if(arrResult = store->get_array(store, labels[i])){
			dump_array(arrResult, io);
		}
		else if(strResult = store->get_string(store, labels[i])){
			dump_string(strResult, io);
		}
		else if((intResult = store->get_immediate(store, labels[i]))->success) {
			dump_immediate(intResult->value, io);
		}
		i++;
	}
}

void print_instructions(Multi_Store* store, IO* io, Sifter* trimmer){
	store->reset_offset(store);
	Sifter** sifters = Config_Text_Sifters(store);
	char* instr;
	char* binInstr;
	while(instr = io->readline(io, trimmer)){
		int i = 0;
		while(i < INSTRUCTION_COUNT){
			if(binInstr = (char*)(sifters[i])->Sift(sifters[i], instr)){
				io->print(io, binInstr);
				store->increment_offset(store, (strlen(binInstr) / 8));
				break;
			}
			i++;
		}
	}
}

void assemble(IO* io, Multi_Store* store, Sifter* trimmer){
	store_registers(store);
	init_exp_sifters(store);
	Store_Symbols(io, store, trimmer);
	print_instructions(store, io, trimmer);	
	dump_data_section(store, io);
}

void show_symbols(IO* io, Multi_Store* store, Sifter* trimmer){
	Store_Symbols(io, store, trimmer);
	display_symbol_table(store);
}

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("\n\nIncorrect number of arguments...\nCorrect Syntax:\n%s\nOR\n%s\n\n",
			"assembler <input file> <output file>",
			"assembler -symbols <input file>");
		return 0;
	}
	Multi_Store* store = New_Multi_Store();
	Sifter* trimmer = New_Sifter(store, HASH_COMMENT_TRIMMER_REGEX, &RETURN_KEY);
	if(strcmp(argv[1], "-symbols") == 0){
		printf("should be printing out stuff");
		IO* io = New_IO(argv[2], "r", NULL, "w");
		show_symbols(io, store, trimmer);
		Clean_Up_IO(io);
	}
	else{
		IO* io = New_IO(argv[1], "r", argv[2], "w");
		assemble(io, store, trimmer);
		Clean_Up_IO(io);
	}
	Clean_Up();
	return 0;
}
