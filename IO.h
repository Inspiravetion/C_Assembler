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
	int offset;
    char* (*readline)(IO* io);
    void (*print)(IO* io, char* data);
	bool (*in_rewind)(IO* io);
	bool (*seek_pattern)(IO* io, Sifter* s);
	int (*get_curr_offset)(IO* io);
};

void Clean_Up_IO(IO* io);

IO* New_IO(char* fileIn, char* inFlags, char* fileOut, char* outFlags);

#endif