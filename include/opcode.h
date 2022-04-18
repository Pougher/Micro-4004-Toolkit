#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <stdint.h>
#include <stdlib.h>

// Defines

#define OPCODE(asmop) (asmop >> 8)

// Assembly opcode typedef
// First 8 bits -> Integer value in the token
// Last 8 bits -> Token ID
typedef uint16_t AsmOp;

typedef enum {
    TOKEN_LDA = 0,
    TOKEN_LDX,
    TOKEN_LRA,
    TOKEN_LRX,
    TOKEN_STA,
    TOKEN_XOR,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_JMP,
    TOKEN_JC,
    TOKEN_JZ,
    TOKEN_TAX,
    TOKEN_TXA,
    TOKEN_REG_A,
    TOKEN_REG_X,
    TOKEN_INT,
    TOKEN_LABEL_DECL,
    TOKEN_LABEL_REF,
    TOKEN_NEWLINE
} AsmType;

// Function to convert an opcode and an 8 bit
// operand to a single AsmOp (uint16_t) value.
AsmOp new_token(AsmType t, uint8_t data);

#endif
