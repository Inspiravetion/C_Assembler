#ifndef MULTISTOREH
#define MULTISTOREH

#include <string.h>
#include "Janitor.h"
#include "Array_Factory.h"
#include "Store.h"

typedef struct _Array_Bundle Array_Bundle;

struct _Array_Bundle{
	int* array;
	int length;
};

typedef struct _Multi_Store Multi_Store;

struct _Multi_Store{
	Store* array_store;
	Store* string_store;
	Store* immediate_store;
	//for this ure gunna have to make an array bundle to keep the array pointer and size together
    void (*add_array)(Multi_Store* self, const char* key, int* val, int length);
    void (*add_string)(Multi_Store* self, const char* key, const char* val);
    void (*add_immediate)(Multi_Store* self, const char* key, int val);
    Array_Bundle* (*get_array)(Multi_Store* self, const char* key);
    const char* (*get_string)(Multi_Store* self, const char* key);
	int (*get_immediate)(Multi_Store* self, const char* key);
	void (*display_immediate_table)(Multi_Store* self);
};

Multi_Store* New_Multi_Store();

#endif