#ifndef CONFIGH
#define CONFIGH

#include "Sifter.h"
#include "Static.h"
#include "Instruction_t.h"
#include "Multi_Store.h"

#define INSTRUCTION_COUNT 28
#define INT_LENGTH 32
#define DATA_TYPE_COUNT 3
#define DATA_SECTION_BASE_ADDRESS 0x00002000

Sifter** Config_Text_Sifters(Multi_Store* store);
Sifter** Config_Data_Sifters();
const char* DUMMY(Multi_Store* store, const char** args, size_t size);

#define DATA_SECTION_SIFTER New_Sifter(NULL, DATA_SECTION_REGEX, &DUMMY)


#endif