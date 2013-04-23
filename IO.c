#include "IO.h"

char* readline(IO* io){
	if(io->in){
		char* container = (char*) New_Array(sizeof(char), LINE_MAX);
		if(fgets(container, LINE_MAX, io->in)){
			int end = strlen(container) - 1;
			if(container[end] = '\n'){
				container[end] = '\0';			
			}
			return container;
		}
		else{
			return NULL;
		}
	}
	printf("in FILE* does not exist...\n");
	return NULL;
}

void print(IO* io, char* data){
	if(io->out){
		fprintf(io->out, "%s\n", data);
	}
	else{
		printf("out FILE* does not exist...\n");
	}
}

void Clean_Up_IO(IO* io){
	fclose(io->in);
	fclose(io->out);
}

IO* New_IO(char* fileIn, char* inFlags, char* fileOut, char* outFlags){
	IO* io  = (IO*) malloc(sizeof(IO));
	io->in  = fopen(fileIn, inFlags);
	io->out = fopen(fileOut, outFlags);
	io->readline = &readline;
	io->print = &print;
	Register_Disposable(io);
	return io;
}