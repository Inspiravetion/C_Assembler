#include "Config.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  External Helpers                                                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

const char* DUMMY(Multi_Store* store, const char** args, size_t size){
	return "";
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  Binary Conversion Sifters and Helpers                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

const char* IS_REG(Multi_Store* store, const char** args, size_t size);
const char* IS_REG_WITH_OFFSET(Multi_Store* store, const char** args, size_t size);
const char* IS_IMM(Multi_Store* store, const char** args, size_t size);

#define REG_SIFTER New_Sifter(NULL, IS_REG_REGEX, &IS_REG)
#define REG_WITH_OFFSET_SIFTER New_Sifter(NULL, IS_REG_WITH_OFFSET_REGEX, &IS_REG_WITH_OFFSET)
#define IMM_SIFTER New_Sifter(NULL, IS_IMM_REGEX, &IS_IMM)

const char* intToBinaryString(int num, int strLen) {
    char* string = (char*) New_Array(sizeof(char), (strLen + 1));
    int mask = 1, i = 0;
    while(i < strLen){
    	string[strLen - 1 - i] = (num & (mask << i)) ? '1' : '0';
    	i++;
    }
    string[strLen] = '\0';
    return string;
}

const char* IS_REG(Multi_Store* store, const char** args, size_t size){
	//convert args[1] to its proper binary register
	return "why yes it is...";
}

const char* IS_REG_WITH_OFFSET(Multi_Store* store, const char** args, size_t size){
	//convert args[2] to its proper binary register plus its immediate args[1]
	return "why yes it is...";
}

const char* IS_IMM(Multi_Store* store, const char** args, size_t size){
	int value = atoi(args[1]);
	return intToBinaryString(value, INT_LENGTH);
}

const char* RESOLVE_EXP(Multi_Store* store, const char* exp, int maxLen){
	const char* result;
	//GOING TO NEED TO CHECK IF THIS EXPRESSION IS IN THE STORE ALREADY
	if(result = REG_WITH_OFFSET_SIFTER->Sift(REG_WITH_OFFSET_SIFTER, exp)){
		//find out if this should return the binary representation of the
		//register number plus the immediate or something else
		printf("%s\n", "is ofset with register");
		return result;
	}
	else if(result = REG_SIFTER->Sift(REG_SIFTER, exp)){
		printf("%s\n", "is register");
		return result;
	}
	else if(result = IMM_SIFTER->Sift(IMM_SIFTER, exp)){
		char* trimmedString = (char*) New_Array(sizeof(char), maxLen + 1);
		strncat(trimmedString, (result + INT_LENGTH - maxLen), maxLen);
		return trimmedString;
	}
	else{
		int address = store->get_immediate(store, exp);
		if(address != -1){
			printf("%08X\n", address);
			return intToBinaryString(address, maxLen);
		}
	}
	return exp;
}

///////////////////////////////////////////////////////////////////////////////
//  Instruction Specific Functions                                           //
//  have to process each argument to see if its                              //
//  a register/register with an offset                                       //
///////////////////////////////////////////////////////////////////////////////

//R_Types----------------------------------------------------------------------
const char* ADD_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		ADD_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		NULL
	);
	return instr->toString(instr);
}

const char* SUB_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		SUB_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* OR_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		OR_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* AND_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		AND_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* SLT_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		SLT_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* SLL_FUNC(Multi_Store* store, const char** args, size_t size){
	//sa may not be Null for this
	R_Type* instr = (R_Type*) New_R_Type(
		SLL_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* SRL_FUNC(Multi_Store* store, const char** args, size_t size){
	//sa may not be Null for this
	R_Type* instr = (R_Type*) New_R_Type(
		SRL_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* JR_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		JR_OPCODE, 
		RESOLVE_EXP(store, args[1], 5),
		"00000", 
		"00000",
		NULL
	);
	return instr->toString(instr);
}

//I_Types----------------------------------------------------------------------
const char* ADDI_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		ADDI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* ADDIU_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		ADDIU_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* ORI_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		ORI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* ANDI_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		ANDI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* SLTI_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		SLTI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BEQ_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BEQ_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BNE_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		ADDI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BLT_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BLT_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BLE_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BLE_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BLEZ_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BLEZ_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		"00000",
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BLTZ_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BLTZ_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		"00000",
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* LUI_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		LUI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5),
		"0000000000000000"
	);
	return instr->toString(instr);
}

const char* LW_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		LW_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* SW_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		SW_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* LA_FUNC(Multi_Store* store, const char** args, size_t size){
	//not right...return the two pseudo instructions i a 64 bit string with a '\n in the middle'
	I_Type* instr = (I_Type*) 
		New_I_Type(LA_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

const char* LI_FUNC(Multi_Store* store, const char** args, size_t size){
	//not right...return the two pseudo instructions i a 64 bit string with a '\n in the middle'
	I_Type* instr = (I_Type*) 
		New_I_Type(LI_OPCODE, args[1], args[2], args[3]);
	return instr->toString(instr);
}

//J_Types----------------------------------------------------------------------
const char* JAL_FUNC(Multi_Store* store, const char** args, size_t size){
	J_Type* instr = (J_Type*) New_J_Type(
		JAL_OPCODE, 
		RESOLVE_EXP(store, args[1], 26)
	);
	return instr->toString(instr);
}

const char* J_FUNC(Multi_Store* store, const char** args, size_t size){
	J_Type* instr = (J_Type*) New_J_Type(
		J_OPCODE, 
		RESOLVE_EXP(store, args[1], 26)
	);
	return instr->toString(instr);
}

//Special Types----------------------------------------------------------------
const char* NOP_FUNC(Multi_Store* store, const char** args, size_t size){
	return "NOOP";
}

const char* SYSCALL_FUNC(Multi_Store* store, const char** args, size_t size){
	return "SYSCALL";
}

/**
 * Creates and returns an array of all the necessary sifters
 * @return Sifter** an array of sifters
 */
Sifter** Config_Text_Sifters(Multi_Store* store){
	Sifter** sifters = (Sifter**) New_Array(sizeof(Sifter*), INSTRUCTION_COUNT);
	int i = 0;

	sifters[i] = New_Sifter(store, ADD_REGEX, &ADD_FUNC);
	i++;

	sifters[i] = New_Sifter(store, SUB_REGEX, &SUB_FUNC);
	i++;

	sifters[i] = New_Sifter(store, OR_REGEX, &OR_FUNC);
	i++;

	sifters[i] = New_Sifter(store, AND_REGEX, &AND_FUNC);
	i++;

	sifters[i] = New_Sifter(store, SLT_REGEX, &SLT_FUNC);
	i++;

	sifters[i] = New_Sifter(store, SLL_REGEX, &SLL_FUNC);
	i++;	

	sifters[i] = New_Sifter(store, SRL_REGEX, &SRL_FUNC);
	i++;

	sifters[i] = New_Sifter(store, JR_REGEX, &JR_FUNC);
	i++;

	sifters[i] = New_Sifter(store, ADDI_REGEX, &ADDI_FUNC);
	i++;

	sifters[i] = New_Sifter(store, ADDIU_REGEX, &ADDIU_FUNC);
	i++;

	sifters[i] = New_Sifter(store, ORI_REGEX, &ORI_FUNC);
	i++;

	sifters[i] = New_Sifter(store, ANDI_REGEX, &ANDI_FUNC);
	i++;

	sifters[i] = New_Sifter(store, SLTI_REGEX, &SLTI_FUNC);
	i++;

	sifters[i] = New_Sifter(store, BEQ_REGEX, &BEQ_FUNC);
	i++;

	sifters[i] = New_Sifter(store, BNE_REGEX, &BNE_FUNC);
	i++;

	sifters[i] = New_Sifter(store, BLT_REGEX, &BLT_FUNC);
	i++;

	sifters[i] = New_Sifter(store, BLE_REGEX, &BLE_FUNC);
	i++;

	sifters[i] = New_Sifter(store, BLEZ_REGEX, &BLEZ_FUNC);
	i++;

	sifters[i] = New_Sifter(store, BLTZ_REGEX, &BLTZ_FUNC);
	i++;

	sifters[i] = New_Sifter(store, LUI_REGEX, &LUI_FUNC);
	i++;

	sifters[i] = New_Sifter(store, LW_REGEX, &LW_FUNC);
	i++;

	sifters[i] = New_Sifter(store, SW_REGEX, &SW_FUNC);
	i++;

	sifters[i] = New_Sifter(store, LA_REGEX, &LA_FUNC);
	i++;

	sifters[i] = New_Sifter(store, JAL_REGEX, &JAL_FUNC);
	i++;

	sifters[i] = New_Sifter(store, J_REGEX, &J_FUNC);
	i++;

	sifters[i] = New_Sifter(store, LI_REGEX, &LI_FUNC);
	i++;

	sifters[i] = New_Sifter(store, NOP_REGEX, &NOP_FUNC);
	i++;

	sifters[i] = New_Sifter(store, SYSCALL_REGEX, &SYSCALL_FUNC);
	i++;

	return sifters;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  Data Section Sifter Setup                                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void STORE_ARRAY_MIDDLEWARE(Multi_Store* store, const char** strArr){
	const char* key = strArr[1];
	int def_val = atoi(strArr[2]);
	int size = atoi(strArr[3]);
	int* value = (int*) New_Array(sizeof(int), size);
	int i = 0;
	while(i < size){
		value[i] = def_val;
		i++;
	}
	store->add_array(store, key, value, size);
}

void STORE_STRING_MIDDLEWARE(Multi_Store* store, const char** strArr){
	store->add_string(store, strArr[1], strArr[2]);
}

void STORE_IMMEDIATE_MIDDLEWARE(Multi_Store* store, const char** strArr){
	printf("Immediate Data\n");
}

const char* RETURN_KEY(Multi_Store* store, const char** args, size_t size){
	return args[1];
}

Sifter** Config_Data_Sifters(){
	Sifter** sifters = (Sifter**) New_Array(sizeof(Sifter*), DATA_TYPE_COUNT);
	int i = 0;

	sifters[i] = New_Sifter(NULL, ARRAY_DATA_REGEX, &RETURN_KEY);
	i++;

	sifters[i] = New_Sifter(NULL, STRING_DATA_REGEX, &RETURN_KEY);
	i++;

	sifters[i] = New_Sifter(NULL, IMMEDIATE_DATA_REGEX, &RETURN_KEY);

	return sifters;
}
