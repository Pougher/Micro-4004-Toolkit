#ifndef __PARSER_H__
#define __PARSER_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "dict.h"
#include "opcode.h"
#include "stringx.h"
#include "util.h"
#include "expected.h"

// Parser function
// Converts a list of tokens into a 256 byte array of instructions.
// @NOTE: RAM is shared with ROM, and due to the architecture of the
//        computer, the final 16 bytes of ROM are reserved for the RAM.
//        This means that after address 11110000, the RAM begins.

unsigned char* parse(AsmOp* tokens, unsigned int len);

#endif
