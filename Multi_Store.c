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

int get_immediate(Multi_Store* self, const char* key){
	int* intptr = (int*) 
		self->immediate_store->get(self->immediate_store, key);
	return intptr ? intptr[0] : -1;
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

void display_immediate_table(Multi_Store* self){
	self->immediate_store->display(self->immediate_store);
};

void reset_offset(Multi_Store* self){
	self->offset = 0;
}

void increment_offset(Multi_Store* self, int increment){
	self->offset += increment;
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
	store->display_immediate_table = &display_immediate_table;
	Register_Disposable(store);
	return store;
};
