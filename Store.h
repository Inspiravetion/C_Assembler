#ifndef ISTORE
#define ISTORE

#include <string.h>
#include "Janitor.h"
#include "Array_Factory.h"

typedef struct _Store_Bundle Store_Bundle;

struct _Store_Bundle{
	const char* key;
    intptr_t val;
};

typedef struct _Store Store;

struct _Store{
	Store_Bundle** table;
	int capacity;
	int usage;
	int sizeIndex;
    bool (*put)(Store* self, const char* key, intptr_t value);
    intptr_t (*get)(Store* self, const char* key);
};

Store* New_Store();

#endif