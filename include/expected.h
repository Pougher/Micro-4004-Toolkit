#ifndef __EXPECTED_H__
#define __EXPECTED_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "opcode.h"
#include "util.h"

typedef enum {
    EXPECT_REGISTER_A  = 1,
    EXPECT_REGISTER_B  = 2,
    EXPECT_IMM8        = (1 << 2),
    EXPECT_IMM4        = (1 << 3),
} Expect_t;

typedef struct {
    unsigned int operands;
    unsigned int expect_ptr;
    Expect_t expected[256];
} Expect;

// function to validate the operands of an instruction.
bool validate_expect(Expect* expect, AsmOp op, unsigned int line);

#endif
