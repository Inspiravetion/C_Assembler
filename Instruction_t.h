#ifndef INSTRUCTION_TYPES
#define INSTRUCTION_TYPES

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "Janitor.h"
#include "Static.h"

/**
 * Struct for R_Type Instructions
 */
typedef struct _R_Type R_Type;

struct _R_Type {
	char* (*toString)(R_Type* self);
	const char* opcode;
	const char* rs;
	const char* rt;
	const char* rd;
	const char* sa;
};

/**
 * Struct for I_Type Instructions
 */
typedef struct _I_Type I_Type;

struct _I_Type {
	char* (*toString)(I_Type* self);
	const char* opcode;
	const char* rs;
	const char* rt;
	const char* imm_16;
};

/**
 * Struct for J_Type Instructions
 */
typedef struct _J_Type J_Type;

struct _J_Type {
	char* (*toString)(J_Type* self);
	const char* opcode;
	const char* target_26;
};

/**
 * R_Type Instruction initializer function
 * @param op    the String opcode
 * @param rs    the String rs
 * @param rt    the String rt
 * @param rd    the String rd
 * @return R_Type* the R_Type created 
 */
R_Type* New_R_Type(const char* op, const char* rs, const char* rt, const char* rd);

/**
 * I_Type Instruction initializer function
 * @param op     the String opcode
 * @param rs     the String rs
 * @param rt     the String rt
 * @param imm_16 the String representation of the 16 bit immediate
 * @return I_Type* the I_Type created
 */
I_Type* New_I_Type(const char* op, const char* rs, const char* rt, const char* imm_16);

/**
 * J_Type Instruction initializer function
 * @param op        the String opcode
 * @param target_26 the String representation of the 26 bit target address
 * @return J_Type* the J_Type created
 */
J_Type* New_J_Type(const char* op, const char* target_26);


#endif