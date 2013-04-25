#ifndef CONFIGH
#define CONFIGH

#include "Sifter.h"
#include "Static.h"
#include "Instruction_t.h"

#define INSTRUCTION_COUNT 28
#define INT_LENGTH 32
#define DATA_TYPE_COUNT 3

Sifter** Config_Text_Sifters();
Sifter** Config_Data_Sifters(Multi_Store* store);
const char* DUMMY(const char** args, size_t size);

#define DATA_SECTION_SIFTER New_Sifter(DATA_SECTION_REGEX, &DUMMY)


#endif