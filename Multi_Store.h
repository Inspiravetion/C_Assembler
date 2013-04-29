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

typedef struct _Immediate_Bundle Immediate_Bundle;

struct _Immediate_Bundle{
	int value;
	bool success;
};

typedef struct _Multi_Store Multi_Store;

struct _Multi_Store{
	int offset;
	Store* array_store;
	Store* string_store;
	Store* immediate_store;
	Store* register_store;
	Store* label_store;
	int label_keys_capacity;
	int label_keys_usage;
	char ** label_keys;
	char** (*get_label_keys)(Multi_Store* self);	
	void (*add_label_key)(Multi_Store* self, char* key);
    void (*add_array)(Multi_Store* self, const char* key, int* val, int length);
    void (*add_label)(Multi_Store* self, const char* key, int val);
    void (*add_string)(Multi_Store* self, const char* key, const char* val);
    void (*add_immediate)(Multi_Store* self, const char* key, int val);
    void (*add_register)(Multi_Store* self, const char* key, int val);
    Array_Bundle* (*get_array)(Multi_Store* self, const char* key);
    const char* (*get_string)(Multi_Store* self, const char* key);
	Immediate_Bundle (*get_immediate)(Multi_Store* self, const char* key);
	int (*get_register)(Multi_Store* self, const char* key);
	int (*get_label)(Multi_Store* self, const char* key);
	void (*reset_offset)(Multi_Store* self);
	void (*increment_offset)(Multi_Store* self, int increment);
	void (*display_label_table)(Multi_Store* self);
};

Multi_Store* New_Multi_Store();

#endif