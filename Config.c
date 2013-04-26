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
//  Register Setup                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#define REGISTER_COUNT 32

static char* registers[REGISTER_COUNT] = {"$zero", "$at", "$v0", "$v1", "$a0", 
	"$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0",
	"$k1", "$gp", "$sp", "$s8", "$ra"
};

void store_registers(Multi_Store* store){
	int i = 0;
	while(i < REGISTER_COUNT){
		store->add_register(store, registers[i], i);
		i++;
	}
};


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  Binary Conversion Sifters and Helpers                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

const char* IS_REG(Multi_Store* store, const char** args, size_t size);
const char* IS_REG_WITH_OFFSET(Multi_Store* store, const char** args, size_t size);
const char* IS_IMM(Multi_Store* store, const char** args, size_t size);

Sifter** EXP_SIFTERS = NULL;

void init_exp_sifters(Multi_Store* store){
	Sifter** sifters = (Sifter**) New_Array(sizeof(Sifter*), 3);
	int i = 0;

	sifters[i] = New_Sifter(store, IS_REG_WITH_OFFSET_REGEX, &IS_REG_WITH_OFFSET);
	i++;

	sifters[i] = New_Sifter(store, IS_REG_REGEX, &IS_REG);
	i++;

	sifters[i] = New_Sifter(store, IS_IMM_REGEX, &IS_IMM);

	EXP_SIFTERS = sifters;
}

/*#define REG_SIFTER New_Sifter(NULL, IS_REG_REGEX, &IS_REG)
#define REG_WITH_OFFSET_SIFTER New_Sifter(NULL, IS_REG_WITH_OFFSET_REGEX, &IS_REG_WITH_OFFSET)
#define IMM_SIFTER New_Sifter(NULL, IS_IMM_REGEX, &IS_IMM)*/

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
	// printf("%s\n", args[1]);
	// printf("%s\n", args[2]);
	return args[1];
}

const char* IS_REG_WITH_OFFSET(Multi_Store* store, const char** args, size_t size){
	//convert args[2] to its proper binary register plus its immediate args[1]
	// printf("%s\n", args[1]);
	// printf("%s\n", args[2]);
	return "why yes it is...";
}

const char* IS_IMM(Multi_Store* store, const char** args, size_t size){
	int value = atoi(args[1]);
	return intToBinaryString(value, INT_LENGTH);
}

const char* RESOLVE_EXP(Multi_Store* store, const char* exp, int maxLen){
	const char* result;
	if(result = EXP_SIFTERS[0]->Sift(EXP_SIFTERS[0], exp)){
		//find out if this should return the binary representation of the
		//register number plus the immediate or something else
		printf("%s\n", "is ofset with register");
		return result;
	}
	else if(result = EXP_SIFTERS[1]->Sift(EXP_SIFTERS[1], exp)){
		int address = store->get_register(store, result);
		return intToBinaryString(address, maxLen);
	}
	else if(result = EXP_SIFTERS[2]->Sift(EXP_SIFTERS[2], exp)){
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
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[1], 5), 
		NULL
	);
	return instr->toString(instr);
}

const char* SUB_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		SUB_OPCODE, 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[1], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* OR_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		OR_OPCODE, 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[1], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* AND_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		AND_OPCODE, 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[1], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* SLT_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		SLT_OPCODE, 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[1], 5),
		NULL
	);
	return instr->toString(instr);
}

const char* SLL_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		SLL_OPCODE, 
		NULL,
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[3], 5)
	);
	return instr->toString(instr);
}

const char* SRL_FUNC(Multi_Store* store, const char** args, size_t size){
	R_Type* instr = (R_Type*) New_R_Type(
		SRL_OPCODE, 
		NULL,
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[3], 5)
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
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BNE_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		ADDI_OPCODE, 
		RESOLVE_EXP(store, args[2], 5), 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[3], 16)
	);
	return instr->toString(instr);
}

const char* BLTZ_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BLTZ_OPCODE, 
		NULL,
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 16)
	);
	return instr->toString(instr);
}

//Hardcoded to only take immediate...could be dangerous
const char* BLEZ_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		BLEZ_OPCODE,
		NULL, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[2], 16)
	);
	return instr->toString(instr);
}

const char* BLT_FUNC(Multi_Store* store, const char** args, size_t size){
	const char* rs = args[1];
	const char* rt = args[2];
	const char* offset = args[3];
	char* sudoInstr = (char*) New_Array(sizeof(char), 66);
	const char** subArgs[4] = {
		NULL,
		"$at",
		rs,
		rt
	};
	const char* first_half = SUB_FUNC(store, subArgs, size);
	const char** bltzArgs[3] = {
		NULL,
		"$at",
		offset
	};
	const char* second_half = BLTZ_FUNC(store, bltzArgs, size);
	strcat(sudoInstr, first_half);
	strcat(sudoInstr, "\n");
	strcat(sudoInstr, second_half);
	return sudoInstr;
}

const char* BLE_FUNC(Multi_Store* store, const char** args, size_t size){
	const char* rs = args[1];
	const char* rt = args[2];
	const char* offset = args[3];
	char* sudoInstr = (char*) New_Array(sizeof(char), 66);
	const char** subArgs[4] = {
		NULL,
		"$at",
		rs,
		rt
	};
	const char* first_half = SUB_FUNC(store, subArgs, size);
	const char** bltzArgs[3] = {
		NULL,
		"$at",
		offset
	};
	const char* second_half = BLEZ_FUNC(store, bltzArgs, size);
	strcat(sudoInstr, first_half);
	strcat(sudoInstr, "\n");
	strcat(sudoInstr, second_half);
	return sudoInstr;
}

const char* LUI_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		LUI_OPCODE, 
		RESOLVE_EXP(store, args[1], 5),
		NULL, 
		RESOLVE_EXP(store, args[2], 16)
	);
	return instr->toString(instr);
}

const char* LW_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		LW_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[2], 16)
	);
	return instr->toString(instr);
}

const char* SW_FUNC(Multi_Store* store, const char** args, size_t size){
	I_Type* instr = (I_Type*) New_I_Type(
		SW_OPCODE, 
		RESOLVE_EXP(store, args[1], 5), 
		RESOLVE_EXP(store, args[3], 5), 
		RESOLVE_EXP(store, args[2], 16)
	);
	return instr->toString(instr);
}

const char* LA_FUNC(Multi_Store* store, const char** args, size_t size){
	char* rd = args[1];
	char* label = args[2];
	int address = store->get_immediate(store, label);
	if(address == -1){
		return "label is not indexed and thus could not be resolved...";
	}
	if(address < 0xFFFF){
		const char** addiArgs[4] = {
			NULL, 
			rd, 
			"$zero",
			label
		};
		return ADDI_FUNC(store, addiArgs, size);
	}
	else{
		char* sudoInstr = (char*) New_Array(sizeof(char), 66);
		char topBits[17];
		sprintf(topBits, "%d", (address >> 16));
		const char** luiArgs[3] = {
			NULL,
			rd,
			topBits
		};
		const char** oriArgs[4] = {
			NULL,
			rd,
			rd,
			label
		};
		strcat(sudoInstr, LUI_FUNC(store, luiArgs, size));
		strcat(sudoInstr, "\n");
		strcat(sudoInstr, ORI_FUNC(store, oriArgs, size));
		return sudoInstr;
	}
}

const char* LI_FUNC(Multi_Store* store, const char** args, size_t size){
	char* rd = args[1];
	char* imm = args[2];
	int immediate = atoi(imm);
	char btmBits[17];
	sprintf(btmBits, "%d", immediate);
	if(immediate < 0xFFFF){
		const char** addiArgs[4] = {
			NULL, 
			rd, 
			"$zero",
			btmBits
		};
		return ADDIU_FUNC(store, addiArgs, size);
	}
	else{
		char* sudoInstr = (char*) New_Array(sizeof(char), 66);
		char topBits[17];
		sprintf(topBits, "%d", (immediate >> 16));
		const char** luiArgs[3] = {
			NULL,
			rd,
			topBits
		};
		const char** oriArgs[4] = {
			NULL,
			rd,
			rd,
			btmBits
		};
		strcat(sudoInstr, LUI_FUNC(store, luiArgs, size));
		strcat(sudoInstr, "\n");
		strcat(sudoInstr, ORI_FUNC(store, oriArgs, size));
		return sudoInstr;
	}
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
	return "00000000000000000000000000000000";
}

const char* SYSCALL_FUNC(Multi_Store* store, const char** args, size_t size){
	return "00000000000000000000000000001100";
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
	i++;

	sifters[i] = New_Sifter(NULL, LABEL_REGEX, &RETURN_KEY);	

	return sifters;
}
