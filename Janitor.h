#ifndef JANITOR
#define JANITOR

#include <stdio.h>
#include "Garbage.h"

//Forward Declarations for ARRAY_FACTORY
void* New_Array(int typeSize, int Sz);
bool Extend_Array(void** arrP, int typeSize, int size);


/**
 * Calls free on all the dynamically allocated data that was 
 * registered with it.
 */
void Clean_Up();

/**
 * Adds the pointer to its global array so that they can be 
 * free'd later
 * @param d the disposible pointer to be registered
 */
void Register_Disposable(void* d);

void Unregister_Disposable(void* d);

#endif