#ifndef SIFTER
#define SIFTER

#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Static.h"
#include "Instruction_t.h"
#include "Multi_Store.h"

/**
 * Sifter Struct to bundle together a regex_t, an array of regmatch_t's, and 
 * two function pointers 
 */

typedef struct _Sifter Sifter;

struct _Sifter{
    const char* strRegEx; //may not need to keep a reference to this...
    regex_t regEx;
    regmatch_t* captures;
    size_t nGroups;
    Multi_Store* store;
   	const char* (*Custom)(Multi_Store* store, const char** strArr, size_t numGroups);
    const char* (*Sift)(Sifter* self, const char* compStr);
	void (*Store_Middleware)(Multi_Store* store, const char** strArr);
};

/**
 * Creates a new sifter with the given regexp and custom processing function
 * @param exp the string representation of the regular expression
 * @param a processor function that takes the captured groups from the compiled
 * regular expression executed on a given String and outputs the correct 
 * String representation of the 32 bit instruction.
 */
Sifter* New_Sifter(Multi_Store* store, const char* exp, const char*(*func)(Multi_Store* store, const char**, size_t));

#endif