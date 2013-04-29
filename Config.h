#ifndef CONFIGH
#define CONFIGH

#include "Sifter.h"
#include "Static.h"
#include "Instruction_t.h"
#include "Multi_Store.h"

#define INSTRUCTION_COUNT 28
#define INT_LENGTH 32
#define DATA_TYPE_COUNT 4
#define DOUBLE_INSTRUCTION_COUNT 2
#define DATA_SECTION_BASE_ADDRESS 0x00002000
#define TEXT_SECTION_BASE_ADDRESS 0x00000000

Sifter** Config_Text_Sifters(Multi_Store* store);
Sifter** Config_Data_Sifters();
Sifter** Config_Double_Sifters();
const char* RETURN_KEY(Multi_Store* store, const char** args, size_t size);
const char* DUMMY(Multi_Store* store, const char** args, size_t size);
void store_registers(Multi_Store* store);
void init_exp_sifters(Multi_Store* store);
const char* intToBinaryString(int num, int strLen);


#define DATA_SECTION_SIFTER New_Sifter(NULL, DATA_SECTION_REGEX, &DUMMY)


#endif