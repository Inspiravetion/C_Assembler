#ifndef ARRAY_FACTORY
#define ARRAY_FACTORY

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Garbage.h"

//Forward Declarations for JANITOR
void Register_Disposable(void* d);
void Unregister_Disposable(void* d);


/**
 * Returns a new array that holds Sz number of objects
 * of typeSize size and registers it to be disposed of
 * at a later time
 * @param typeSize int the size of each individual element 
 * in the array
 * @param Sz int the initial size of the array.
 * @return void** an array that needs to be casted by caller
 */
void* New_Array(int typeSize, int Sz);

/**
 * Takes an array and attempts to extend its length. 
 * Returns true if successful and false otherwise.
 * Also makes sure the right pointer is registerted to 
 * be disposed of later
 * @param  arrP     a pointer to the array that should be
 * elongated
 * @param  typeSize int the size of the elements the array
 * holds
 * @param  size     the number of elements the array should
 * hold
 * @return          true if successful, false otherwise
 */
bool Extend_Array(void** arrP, int typeSize, int size);

#endif