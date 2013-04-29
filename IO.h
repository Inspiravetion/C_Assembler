#ifndef IOH
#define IOH

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Janitor.h"
#include "Array_Factory.h"
#include "Sifter.h"

typedef struct _IO IO;

struct _IO{
	FILE* in;
	FILE* out;
	int in_offset;
    char* (*readline)(IO* io, Sifter* trimmer);
    void (*print)(IO* io, char* data);
	bool (*in_rewind)(IO* io);
	int (*get_curr_offset)(IO* io);
	bool (*seek_pattern)(IO* io, Sifter* s);
	void (*reset_in_offset)(IO* io);
};

void Clean_Up_IO(IO* io);
bool is_just_space(char* string);

IO* New_IO(char* fileIn, char* inFlags, char* fileOut, char* outFlags);

#endif