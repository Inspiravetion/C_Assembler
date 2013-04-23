#ifndef IOH
#define IOH

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Janitor.h"
#include "Array_Factory.h"

typedef struct _IO IO;

struct _IO{
	FILE* in;
	FILE* out;
    char* (*readline)(IO* io);
    void (*print)(IO* io, char* data);
};

void Clean_Up_IO(IO* io);

IO* New_IO(char* fileIn, char* inFlags, char* fileOut, char* outFlags);

#endif