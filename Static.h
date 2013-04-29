#ifndef STATICH
#define STATICH

///////////////////////////////////////////////////////////////////////////////
// REGULAR EXPRESSION STRINGS                                                //
///////////////////////////////////////////////////////////////////////////////

/**
 * R_Type Instruction RegExps (3 params)
 */
#define ADD_REGEX "add[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define SUB_REGEX "sub[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define OR_REGEX "or[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define AND_REGEX "and[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define SLT_REGEX "slt[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define SLL_REGEX "sll[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define SRL_REGEX "srl[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define JR_REGEX "jr[[:space:]](.*)"//rt, sa, and rd = 00000

// (\\#.*)?
/**
 * I_Type Instruction RegExps (all digits are 16 bit immediates)
 */
#define ADDI_REGEX "addi[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define ADDIU_REGEX "addiu[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define ORI_REGEX "ori[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define ANDI_REGEX "andi[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define SLTI_REGEX "slti[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"

#define BEQ_REGEX "beq[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define BNE_REGEX "bne[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define BLT_REGEX "blt[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define BLE_REGEX "ble[[:space:]](.*),[[:space:]](.*),[[:space:]](.*)"
#define BLEZ_REGEX "blez[[:space:]](.*),[[:space:]](.*)" //rt defaults to 00000
#define BLTZ_REGEX "bltz[[:space:]](.*),[[:space:]](.*)" //rt defaults to 00000

#define LUI_REGEX "lui[[:space:]](.*),[[:space:]](.*)" //rd defaults to 00000
#define LW_REGEX "lw[[:space:]](.*),[[:space:]]([[:digit:]]+)\\((.*)\\)"
#define SW_REGEX "sw[[:space:]](.*),[[:space:]]([[:digit:]]+)\\((.*)\\)"
#define LA_REGEX "la[[:space:]](.*),[[:space:]](.*)"
#define LI_REGEX "li[[:space:]](.*),[[:space:]](.*)"


/**
 * J_Type Instruction RegExps (1 param)
 */
#define JAL_REGEX "jal[[:space:]](.*)"
#define J_REGEX "j[[:space:]](.*)"

/**
 * Special
 */
#define NOP_REGEX "nop"
#define SYSCALL_REGEX "syscall"

/**
 * Processing Helpers
 * [[.-.][:digit:]]+
 */
#define IS_REG_REGEX "(\\$.*)"
#define IS_REG_WITH_OFFSET_REGEX "([[:digit:]]+)\\((\\$.*)\\)"
#define IS_IMM_REGEX "([[.-.][:space:][:digit:]]*)"
#define DATA_SECTION_REGEX "[[:space:]]*\\.data[[:space:]]*"

/**
 * Data Store Helpers
 */
#define ARRAY_DATA_REGEX "[[:space:]]*(.*):[[:space:]]*\\.word[[:space:]]*(.*):(.*)" 
#define STRING_DATA_REGEX "[[:space:]]*(.*):[[:space:]]*\\.asciiz[[:space:]]*\"(.*)\"*"
#define IMMEDIATE_DATA_REGEX "[[:space:]]*(.*):[[:space:]]*\\.word[[:space:]]*(.*)"
#define LABEL_REGEX "[[:space:]]*(.*):[[:space:]]*"
#define HASH_COMMENT_TRIMMER_REGEX "([$(),:.\\\"_[.-.][:space:][:alpha:][:digit:]]*)"
#define BEG_OF_FILE "[[:space:]]*(\\.text)"

///////////////////////////////////////////////////////////////////////////////
// OPCODE STRINGS                                                            //
///////////////////////////////////////////////////////////////////////////////

#define ADD_OPCODE   "100000" 
#define SUB_OPCODE   "100010" 
#define OR_OPCODE    "100101" 
#define AND_OPCODE   "100100" 
#define SLT_OPCODE   "101010" 
#define SLL_OPCODE   "000000" 
#define SRL_OPCODE   "000010" //R_Type opcodes go at end 
#define ADDI_OPCODE  "001000" 
#define ADDIU_OPCODE "001001" 
#define ORI_OPCODE   "001101" 
#define ANDI_OPCODE  "001100" 
#define SLTI_OPCODE  "001010" 
#define BEQ_OPCODE   "000100" 
#define BNE_OPCODE   "000101" 
#define BLT_OPCODE   "" //might have to be figured out with psuedo Instructions
#define BLE_OPCODE   "" //might have to be figured out with psuedo Instructions
#define BLEZ_OPCODE  "000110" 
#define BLTZ_OPCODE  "000001" 
#define LUI_OPCODE   "001111" 
#define LW_OPCODE    "100011" 
#define SW_OPCODE    "101011" 
#define LA_OPCODE    "" //might have to be figured out with psuedo Instructions
#define LI_OPCODE    "" //might have to be figured out with psuedo Instructions
#define JAL_OPCODE   "000011" 
#define JR_OPCODE    "001000" 
#define J_OPCODE     "000010" //J_Type opcodes go at the beginning

#endif