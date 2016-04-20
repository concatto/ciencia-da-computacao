#ifndef MIPS_DEFINITIONS
#define MIPS_DEFINITIONS

#define N_REG 32
#define DATA_MEM_SIZE 1024
#define REG_RA 0x1F

//MASKS
#define MASK_5  0x1F
#define MASK_6  0x3F
#define MASK_16 0xFFFF
#define MASK_26 0x3FFFFFF

//OFFSETS
#define OP_OFFSET    26
#define RS_OFFSET    21
#define RT_OFFSET    16
#define RD_OFFSET    11
#define SHAMT_OFFSET 6

/* Instructions decoded
 * General
 * --------------------------------------------------------------
 *   OP      | Instruction | Format |  Addressing Mode  | Note
 * ----------|-------------|--------|-------------------|--------
 *  000000   | R-format    |   R    | Register  (see next table)
 * ----------|-------------|--------|-------------------|--------
 *  000010   | j           |   J    | Pseudodirect      | Jump unconditionally
 *  000011   | jal         |   J    | Pseudodirect      | Jump and link
 *  000100   | beq         |   I    | PC-relative       | Branch if equal
 *  000101   | bne         |   I    | PC-relative       | Branch if not equal
 *  001000   | addi        |   I    | Immediate         | Addition immediate with overflow
 *  001010   | slti        |   I    | Immediate         | Set less than immediate
 *  001100   | andi        |   I    | Immediate         | Bitwise AND immediate
 *  001101   | ori         |   I    | Immediate         | Bitwise OR immediate
 *  001110   | xori        |   I    | Immediate         | Bitwise XOR immediate
 *  001111   | lui         |   I    | Immediate         | Load upper immediate
 *  100011   | lw          |   I    | Base              | Store word
 *  101011   | sw          |   I    | Base              | Load word
 *
 *  R-format (OP: 000000) - Addressing: Register
 * ----------------------------------------------------
 *  Function | Instruction | Note
 *   000000  | sll         | Shift left logical
 *   000010  | srl         | Shift right logival
 *   001000  | jr          | Jump register
 *   100000  | add         | Addition with overflow
 *   100010  | sub         | Subtraction with overflow
 *   100100  | and         | Bitwise AND
 *   100101  | or          | Bitwise OR
 *   100110  | xor         | Bitwise XOR
 *   100111  | nor or (not)| Bitwise NOR (maybe bit inversion)
 *
 */

///// OPCODE /////////////
#define RTYPEOP 0x0
#define ADDI	0x8
#define LW      0x23
#define SW      0x2B
#define LUI		0xF
#define ORI		0xD
///////////////////////////

///// FUNC ////////////////
#define ADD     0x20
#define SUB     0x22
///////////////////////////

struct mips_instruction{
        unsigned int ins;
        unsigned int op_code;
        unsigned int rs;
        unsigned int rt;
        unsigned int rd;
        unsigned int shamt;
        unsigned int funct;
        short immediate_16bits;
        unsigned int immediate_26bits;
};

#endif // MIPS_DEFINITIONS

