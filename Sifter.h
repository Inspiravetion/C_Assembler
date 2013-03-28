#ifndef SIFTER
#define SIFTER

#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Janitor.h"

/**
 * Sifter Struct to bundle together a regex_t, an array of regmatch_t's, and 
 * two function pointers 
 */

typedef struct _Sifter Sifter;

struct _Sifter{
    const char* strRegEx;
    regex_t regEx;
    regmatch_t* captures;
   	const char* (*Custom)(const char** strArr);
    const char* (*Sift)(Sifter* self, const char* compStr);
};

/**
 * Creates a new sifter with the given regexp and custom processing function
 * @param exp the string representation of the regular expression
 * @param a processor function that takes the captured groups from the compiled
 * regular expression executed on a given String and outputs the correct 
 * String representation of the 32 bit instruction.
 */
Sifter* New_Sifter(const char* exp, const char*(*func)(const char**));

#endif