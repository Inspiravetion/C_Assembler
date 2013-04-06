#include "Instruction_t.h"

char* R_Type_To_String(R_Type* self){
	char* instruction = (char*) New_Array(sizeof(char) * 33);
	strcat(instruction, "000000");
	strcat(instruction, self->rs);
	strcat(instruction, self->rt);
	strcat(instruction, self->rd);
	strcat(instruction, self->sa ? self->sa : "00000");
	strcat(instruction, self->opcode);
	return instruction;
}

char* I_Type_To_String(I_Type* self){
	char* instruction = (char*) New_Array(sizeof(char) * 32);

	return instruction;
}

char* J_Type_To_String(J_Type* self){
	char* instruction = (char*) New_Array(sizeof(char) * 32);

	return instruction;
}

R_Type* New_R_Type(const char* op, const char* rs, const char* rt, const char* rd){
	R_Type* r = (R_Type*) malloc(sizeof(R_Type));
	r->opcode = op;
	r->rs = rs;
	r->rt = rt;
	r->rd = rd;
	r->toString = &R_Type_To_String;
	Register_Disposable(r);
	return r;
}

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

J_Type* New_J_Type(const char* op, const char* target_26){
	J_Type* j = (J_Type*) malloc(sizeof(J_Type));
	j->opcode = op;
	j->target_26 = target_26;
	j->toString = &J_Type_To_String;
	Register_Disposable(j);
	return j;
}


