#include "Instruction_t.h"

/**
 * Takes an R_Type Instruction and returns a binary string representation of it
 * @param  self R_Type context
 * @return      a binary String version of the instruction
 */
char* R_Type_To_String(R_Type* self){
	char* instruction = (char*) New_Array(sizeof(char), 33);
	strcat(instruction, "000000");
	strcat(instruction, self->rs ? self->rs : "00000");
	strcat(instruction, self->rt);
	strcat(instruction, self->rd);
	strcat(instruction, self->sa ? self->sa : "00000");
	strcat(instruction, self->opcode);
	return instruction;
}

/**
 * Takes an I_Type Instruction and returns a binary string representation of it
 * @param  self I_Type context
 * @return      a binary String version of the instruction
 */
char* I_Type_To_String(I_Type* self){
	char* instruction = (char*) New_Array(sizeof(char), 33);
	strcat(instruction, self->opcode);
	strcat(instruction, self->rs);
	strcat(instruction, self->rt);
	strcat(instruction, self->imm_16);
	return instruction;
}

/**
 * Takes an J_Type Instruction and returns a binary string representation of it
 * @param  self J_Type context
 * @return      a binary String version of the instruction
 */
char* J_Type_To_String(J_Type* self){
	char* instruction = (char*) New_Array(sizeof(char), 33);
	strcat(instruction, self->opcode);
	strcat(instruction, self->target_26);
	return instruction;
}

/**
 * R_Type Instruction initializer function
 * @param op    the String opcode
 * @param rs    the String rs
 * @param rt    the String rt
 * @param rd    the String rd
 * @param sa    the String shift amount
 * @return R_Type* the R_Type created 
 */
R_Type* New_R_Type(const char* op, const char* rs, const char* rt, const char* rd, const char* sa){
	R_Type* r = (R_Type*) malloc(sizeof(R_Type));
	r->opcode = op;
	r->rs = rs;
	r->rt = rt;
	r->rd = rd;
	r->sa = sa;
	r->toString = &R_Type_To_String;
	Register_Disposable(r);
	return r;
}

/**
 * I_Type Instruction initializer function
 * @param op     the String opcode
 * @param rs     the String rs
 * @param rt     the String rt
 * @param imm_16 the String representation of the 16 bit immediate
 * @return I_Type* the I_Type created
 */
I_Type* New_I_Type(const char* op, const char* rs, const char* rt, const char* imm_16){
	I_Type* i = (I_Type*) malloc(sizeof(I_Type));
	i->opcode = op;
	i->rs = rs;
	i->rt = rt;
	i->imm_16 = imm_16;
	i->toString = &I_Type_To_String;
	Register_Disposable(i);
	return i;
}

/**
 * J_Type Instruction initializer function
 * @param op        the String opcode
 * @param target_26 the String representation of the 26 bit target address
 * @return J_Type* the J_Type created
 */
J_Type* New_J_Type(const char* op, const char* target_26){
	J_Type* j = (J_Type*) malloc(sizeof(J_Type));
	j->opcode = op;
	j->target_26 = target_26;
	j->toString = &J_Type_To_String;
	Register_Disposable(j);
	return j;
}


