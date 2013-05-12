#ifndef GARBAGEH
#define GARBAGEH

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern void** GARBAGE;
extern bool GARBAGE_INITIALIZED;
extern int GARBAGE_CAPACITY;
extern int GARBAGE_COUNT;

#endif