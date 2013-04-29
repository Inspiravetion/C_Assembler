#include "Multi_Store.h"

///////////////////////////////////////////////////////////////////////////////
// 																			 //
// Array_Bundle Functions													 //
// 																			 //
///////////////////////////////////////////////////////////////////////////////

Array_Bundle* New_Array_Bundle(int* arr, int len){
	Array_Bundle* bundle = (Array_Bundle*) malloc(sizeof(Array_Bundle));
	bundle->array  = arr;
	bundle->length = len;
	Register_Disposable(bundle);
	return bundle;
}

Immediate_Bundle* New_Immediate_Bundle(int imm, bool succ){
	Immediate_Bundle* bundle = (Immediate_Bundle*) malloc(sizeof(Immediate_Bundle));
	bundle->value = imm;
	bundle->success = succ;
	Register_Disposable(bundle);
	return bundle;
}

///////////////////////////////////////////////////////////////////////////////
// 																			 //
// Multi_Store Functions													 //
// 																			 //
///////////////////////////////////////////////////////////////////////////////

void add_array(Multi_Store* self, const char* key, int* val, int length){
	Array_Bundle* bundle = New_Array_Bundle(val, length);
	self->array_store->put(self->array_store, key, (intptr_t) bundle);
};

void add_string(Multi_Store* self, const char* key, const char* val){
	self->string_store->put(self->string_store, key, (intptr_t) val);
};

void add_immediate(Multi_Store* self, const char* key, int val){
	int* intptr = (int*) New_Array(sizeof(int), 1);
	intptr[0] = val;
	self->immediate_store->put(self->immediate_store, key, (intptr_t) intptr);
};

void add_register(Multi_Store* self, const char* key, int val){
	int* intptr = (int*) New_Array(sizeof(int), 1);
	intptr[0] = val;
	self->register_store->put(self->register_store, key, (intptr_t) intptr);
};

void add_label(Multi_Store* self, const char* key, int val){
	int* intptr = (int*) New_Array(sizeof(int), 1);
	intptr[0] = val;
	self->label_store->put(self->label_store, key, (intptr_t) intptr);
}

Array_Bundle* get_array(Multi_Store* self, const char* key){
	return (Array_Bundle*) 
		self->array_store->get(self->array_store, key);
};

const char* get_string(Multi_Store* self, const char* key){
	return (const char*)
		self->string_store->get(self->string_store, key);
};

Immediate_Bundle* get_immediate(Multi_Store* self, const char* key){
	int* intptr = (int*) 
		self->immediate_store->get(self->immediate_store, key);
	return intptr ? 
		New_Immediate_Bundle(intptr[0], true): 
		New_Immediate_Bundle(-1, false);
};

int get_register(Multi_Store* self, const char* key){
	int* intptr = (int*) 
		self->register_store->get(self->register_store, key);
	return intptr ? intptr[0] : -1;
}

int get_label(Multi_Store* self, const char* key){
	int* intptr = (int*) 
		self->label_store->get(self->label_store, key);
	return intptr ? intptr[0] : -1;
};

void display_label_table(Multi_Store* self){
	self->label_store->display(self->label_store);
};

void reset_offset(Multi_Store* self){
	self->offset = 0;
}

void increment_offset(Multi_Store* self, int increment){
	self->offset += increment;
}

void add_label_key(Multi_Store* self, char* key){
	if(self->label_keys_usage == self->label_keys_capacity){
		Extend_Array(self->label_keys, sizeof(char*), self->label_keys_capacity* 2);
		self->label_keys_capacity *= 2;
	}
	self->label_keys[self->label_keys_usage] = key;
	self->label_keys_usage++;
}

char** get_label_keys(Multi_Store* self){
	return self->label_keys;
}

Multi_Store* New_Multi_Store(){
	Multi_Store* store      = (Multi_Store*) malloc(sizeof(Multi_Store));
	store->array_store      = New_Store();
	store->string_store     = New_Store();
	store->immediate_store  = New_Store();
	store->register_store   = New_Store();
	store->label_store      = New_Store();
	store->add_array        = &add_array;
	store->add_string       = &add_string;
	store->add_immediate    = &add_immediate;
	store->add_register     = &add_register;
	store->add_label        = &add_label;
	store->get_array        = &get_array;
	store->get_string       = &get_string;
	store->get_immediate    = &get_immediate;
	store->get_register     = &get_register;
	store->get_label        = &get_label;
	store->reset_offset     = &reset_offset;
	store->increment_offset = &increment_offset;
	store->display_label_table      = &display_label_table;
	store->add_label_key            = &add_label_key;
	store->get_label_keys			= &get_label_keys;
	store->offset                   = 0;
	store->label_keys               = (char**) New_Array(sizeof(char*), 10);
	store->label_keys_capacity      = 10;
	store->label_keys_usage         = 0;
	Register_Disposable(store);
	return store;
};
