#include "Assembler.h"

//figure out of the IS_REG_WITH_OFFSET should be removed
//from RESOLVE_EXP()
//handle command line...test
//be able to dump the .data section...be glad you didn't delete all that other code


void Store_Symbols(IO* io, Multi_Store* store, Sifter*  trimmer){
	io->seek_pattern(io, New_Sifter(store, BEG_OF_FILE, &RETURN_KEY));
	Sifter** sifters = Config_Data_Sifters(store);
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
		io->print(io, intToBinaryString(bundle->array[i], 32));
		i++;
	}
}

void dump_string(char* string, IO* io){
	int length = strlen(string);
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
	Array_Bundle* bundle;
	char* strResult;
	int intResult;
	while(i < store->label_keys_usage){
		if(bundle = store->get_array(store, labels[i])){
			dump_array(bundle, io);
		}
		else if(strResult = store->get_string(store, labels[i])){
			dump_string(strResult, io);
		}
		else if((intResult = store->get_immediate(store, labels[i])) != -1) {
			dump_immediate(intResult, io);
		}
		i++;
	}
}

void print_instructions(Multi_Store* store, IO* io, Sifter* trimmer){
	Sifter** sifters = Config_Text_Sifters(store);
	char* instr;
	char* binInstr;
	while(instr = io->readline(io, trimmer)){
		int i = 0;
		while(i < INSTRUCTION_COUNT){
			if(binInstr = (char*)(sifters[i])->Sift(sifters[i], instr)){
				io->print(io, binInstr);
				break;
			}
			i++;
		}
	}
}


int main(int argc, char* argv[]){
	IO* io = New_IO("adder.txt", "r", "writefile.txt", "w");
	Multi_Store* store = New_Multi_Store();
	Sifter* trimmer = New_Sifter(store, HASH_COMMENT_TRIMMER_REGEX, &RETURN_KEY);
	store_registers(store);
	init_exp_sifters(store);
	Store_Symbols(io, store, trimmer);

	display_symbol_table(store);

	print_instructions(store, io, trimmer);	

	dump_data_section(store, io);

	Clean_Up_IO(io);
	Clean_Up();
}
