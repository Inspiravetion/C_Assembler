#include "IO.h"

char* readline(IO* io){
	if(io->in){
		char* container = (char*) New_Array(sizeof(char), LINE_MAX);
		if(fgets(container, LINE_MAX, io->in)){
			int end = strlen(container) - 1;
			if(container[end] = '\n'){
				container[end] = '\0';			
			}
			int step = (((end + 1) * sizeof(char) /*bytes*/) * 8) /*bits*/;
			io->in_offset += step;
			return container;
		}
		else{
			return NULL;
		}
	}
	printf("in FILE* does not exist...\n");
	return NULL;
}

void reset_in_offset(IO* io){
	io->in_offset = 0;
}

int get_curr_offset(IO* io){
	return io->in_offset;
}

bool in_rewind(IO* io){
	reset_in_offset(io);
	return fseek(io->in, 0, SEEK_SET);
};

void print(IO* io, char* data){
	if(io->out){
		fprintf(io->out, "%s\n", data);
	}
	else{
		printf("out FILE* does not exist...\n");
	}
};



void Clean_Up_IO(IO* io){
	fclose(io->in);
	fclose(io->out);
};

IO* New_IO(char* fileIn, char* inFlags, char* fileOut, char* outFlags){
	IO* io  = (IO*) malloc(sizeof(IO));
	io->in  = fopen(fileIn, inFlags);
	io->out = fopen(fileOut, outFlags);
	io->readline = &readline;
	io->print = &print;
	io->in_rewind = &in_rewind;
	io->get_curr_offset = &get_curr_offset;
	io->reset_in_offset = &reset_in_offset;
	io->in_offset = 0;
	Register_Disposable(io);
	return io;
};