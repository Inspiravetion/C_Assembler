#ifndef INSTRUCTION_TYPES
#define INSTRUCTION_TYPES

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/**
 * Struct for R_Type Instructions
 */
struct _R_Type {
	const char* (*toString)();
	const char* instruction;
	const char* rs;
	const char* rt;
	const char* rd;
};

typedef struct _R_Type R_Type;

/**
 * Struct for I_Type Instructions
 */
struct _I_Type {
	const char* (*toString)()
	const char* instruction;
	const char* rs;
	const char* rt;
	const char* imm_16;
};

typedef struct _I_Type I_Type;

/**
 * Struct for J_Type Instructions
 */
struct _J_Type {
	const char* (*toString)()
	const char* instruction;
	const char* target_26;
};

typedef struct _J_Type J_Type;

/**
 * R_Type Instruction initializer function
 * @param instr the String instruction
 * @param rs    the String rs
 * @param rt    the String rt
 * @param rd    the String rd
 */
void Create_R(const char* instr, const char* rs, const char* rt, const char* rd);

/**
 * I_Type Instruction initializer function
 * @param instr  the String instruction
 * @param rs     the String rs
 * @param rt     the String rt
 * @param imm_16 the String representation of the 16 bit immediate
 */
void Create_I(const char* instr, const char* rs, const char* rt, const char* imm_16);

/**
 * J_Type Instruction initializer function
 * @param instr     the String instruction
 * @param target_26 the String representation of the 26 bit target address
 */
void Create_J(const char* instr, const char* target_26);


#endif