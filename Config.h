#ifndef CONFIGH
#define CONFIGH

#include "Sifter.h"
#include "Static.h"
#include "Instruction_t.h"

#define INSTRUCTION_COUNT 28
#define INT_LENGTH 32

Sifter** Config_Sifters();
const char* DUMMY(const char** args, size_t size);

#define DATA_SECTION_SIFTER New_Sifter(DATA_SECTION_REGEX, &DUMMY)


#endif