#include "Config.h"

///////////////////////////////////////////////////////////////////////////////
//  Instruction Specific Functions                                           //
//  have to process each argument to see if its                              //
//  a register/register with an offset                                       //
///////////////////////////////////////////////////////////////////////////////

//R_Types----------------------------------------------------------------------
const char* ADD_FUNC(const char** args, size_t size){
	R_Type* instr = (R_Type*) 
		New_R_Type(ADD_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* SUB_FUNC(const char** args, size_t size){
	R_Type* instr = (R_Type*) 
		New_R_Type(SUB_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* OR_FUNC(const char** args, size_t size){
	R_Type* instr = (R_Type*) 
		New_R_Type(OR_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* AND_FUNC(const char** args, size_t size){
	R_Type* instr = (R_Type*) 
		New_R_Type(AND_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* SLT_FUNC(const char** args, size_t size){
	R_Type* instr = (R_Type*) 
		New_R_Type(SLT_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* SLL_FUNC(const char** args, size_t size){
	//sa may not be Null for this
	R_Type* instr = (R_Type*) 
		New_R_Type(SLL_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* SRL_FUNC(const char** args, size_t size){
	//sa may not be Null for this
	R_Type* instr = (R_Type*) 
		New_R_Type(SRL_OPCODE, args[1], args[2], args[3], NULL);
	return instr->toString(instr);
}

const char* JR_FUNC(const char** args, size_t size){
	R_Type* instr = (R_Type*) 
		New_R_Type(JR_OPCODE, args[1], "00000", "00000", NULL);
	return instr->toString(instr);
}

//I_Types----------------------------------------------------------------------
const char* ADDI_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(ADDI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* ADDIU_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(ADDIU_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* ORI_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(ORI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* ANDI_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(ANDI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* SLTI_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(SLTI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* BEQ_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(BEQ_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* BNE_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(ADDI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* BLT_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(BLT_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* BLE_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(BLE_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* BLEZ_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(BLEZ_OPCODE, args[1], "00000", args[3]);
	return instr->toString(instr);
}

const char* BLTZ_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(BLTZ_OPCODE, args[1], "00000", args[3]);
	return instr->toString(instr);
}

const char* LUI_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(LUI_OPCODE, args[1], args[2], "0000000000000000");
	return instr->toString(instr);
}

const char* LW_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(LW_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* SW_FUNC(const char** args, size_t size){
	I_Type* instr = (I_Type*) 
		New_I_Type(SW_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* LA_FUNC(const char** args, size_t size){
	//not right
	I_Type* instr = (I_Type*) 
		New_I_Type(LA_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* LI_FUNC(const char** args, size_t size){
	//not right
	I_Type* instr = (I_Type*) 
		New_I_Type(LI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

//J_Types----------------------------------------------------------------------
const char* JAL_FUNC(const char** args, size_t size){
	J_Type* instr = (J_Type*) New_J_Type(JAL_OPCODE, args[1]);
	return instr->toString(instr);
}

const char* J_FUNC(const char** args, size_t size){
	J_Type* instr = (J_Type*) New_J_Type(J_OPCODE, args[1]);
	return instr->toString(instr);
}
/**
 * Creates and returns an array of all the necessary sifters
 * @return Sifter** an array of sifters
 */
Sifter** Config_Sifters(){
	Sifter** sifters = (Sifter**) New_Array(sizeof(Sifter*), 28);
	int i = 0;

	sifters[i] = New_Sifter(ADD_REGEX, &ADD_FUNC);
	i++;

	sifters[i] = New_Sifter(SUB_REGEX, &SUB_FUNC);
	i++;

	sifters[i] = New_Sifter(OR_REGEX, &OR_FUNC);
	i++;

	sifters[i] = New_Sifter(AND_REGEX, &AND_FUNC);
	i++;

	sifters[i] = New_Sifter(SLT_REGEX, &SLT_FUNC);
	i++;

	sifters[i] = New_Sifter(SLL_REGEX, &SLL_FUNC);
	i++;	

	sifters[i] = New_Sifter(SRL_REGEX, &SRL_FUNC);
	i++;

	sifters[i] = New_Sifter(JR_REGEX, &JR_FUNC);
	i++;

	sifters[i] = New_Sifter(ADDI_REGEX, &ADDI_FUNC);
	i++;

	sifters[i] = New_Sifter(ADDIU_REGEX, &ADDIU_FUNC);
	i++;

	sifters[i] = New_Sifter(ORI_REGEX, &ORI_FUNC);
	i++;

	sifters[i] = New_Sifter(ANDI_REGEX, &ANDI_FUNC);
	i++;

	sifters[i] = New_Sifter(SLTI_REGEX, &SLTI_FUNC);
	i++;

	sifters[i] = New_Sifter(BEQ_REGEX, &BEQ_FUNC);
	i++;

	sifters[i] = New_Sifter(BNE_REGEX, &BNE_FUNC);
	i++;

	sifters[i] = New_Sifter(BLT_REGEX, &BLT_FUNC);
	i++;

	sifters[i] = New_Sifter(BLE_REGEX, &BLE_FUNC);
	i++;

	sifters[i] = New_Sifter(BLEZ_REGEX, &BLEZ_FUNC);
	i++;

	sifters[i] = New_Sifter(BLTZ_REGEX, &BLTZ_FUNC);
	i++;

	sifters[i] = New_Sifter(LUI_REGEX, &LUI_FUNC);
	i++;

	sifters[i] = New_Sifter(LW_REGEX, &LW_FUNC);
	i++;

	sifters[i] = New_Sifter(SW_REGEX, &SW_FUNC);
	i++;

	sifters[i] = New_Sifter(LA_REGEX, &LA_FUNC);
	i++;

	sifters[i] = New_Sifter(LI_REGEX, &LI_FUNC);
	return sifters;
}

