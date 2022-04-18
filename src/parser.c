#include "parser.h"

// table of operands for each opcode.
Expect INSTRUCTION_EXPECTS[16] = {
    [TOKEN_LDA] = {
        .operands = 1,
        .expected = { EXPECT_IMM4 },
        .expect_ptr = 0,
    },
    [TOKEN_LDX] = {
        .operands = 1,
        .expected = { EXPECT_IMM4 },
        .expect_ptr = 0,
    },
    [TOKEN_LRA] = {
        .operands = 1,
        .expected = { EXPECT_IMM8 },
        .expect_ptr = 0,
    },
    [TOKEN_LRX] = {
        .operands = 1,
        .expected = { EXPECT_IMM8 },
        .expect_ptr = 0,
    },
    [TOKEN_STA] = {
        .operands = 1,
        .expected = { EXPECT_IMM8 },
        .expect_ptr = 0,
    },
    [TOKEN_XOR] = {
        .operands = 2,
        .expected = { EXPECT_REGISTER_A, EXPECT_REGISTER_B },
        .expect_ptr = 0,
    },
    [TOKEN_ADD] = {
        .operands = 2,
        .expected = { EXPECT_REGISTER_A, EXPECT_REGISTER_B },
        .expect_ptr = 0,
    },
    [TOKEN_SUB] = {
        .operands = 2,
        .expected = { EXPECT_REGISTER_A, EXPECT_REGISTER_B },
        .expect_ptr = 0,
    },
    [TOKEN_AND] = {
        .operands = 2,
        .expected = { EXPECT_REGISTER_A, EXPECT_REGISTER_B },
        .expect_ptr = 0,
    },
    [TOKEN_OR] = {
        .operands = 2,
        .expected = { EXPECT_REGISTER_A, EXPECT_REGISTER_B },
        .expect_ptr = 0,
    },
    [TOKEN_NOT] = {
        .operands = 1,
        .expected = { EXPECT_REGISTER_A },
        .expect_ptr = 0,
    },
    [TOKEN_JMP] = {
        .operands = 1,
        .expected = { EXPECT_IMM8 | EXPECT_IMM4 },
        .expect_ptr = 0,
    },
    [TOKEN_JC] = {
        .operands = 1,
        .expected = { EXPECT_IMM8 | EXPECT_IMM4 },
        .expect_ptr = 0,
    },
    [TOKEN_JZ] = {
        .operands = 1,
        .expected = { EXPECT_IMM8 | EXPECT_IMM4 },
        .expect_ptr = 0,
    },
    [TOKEN_TAX] = {
        .operands = 0,
        .expected = { 0 },
        .expect_ptr = 0,
    },
    [TOKEN_TXA] = {
        .operands = 0,
        .expected = { 0 },
        .expect_ptr = 0,
    },
};

unsigned char* parse(AsmOp* tokens, unsigned int len)
{
    unsigned char* code = (unsigned char*) calloc(256, sizeof(unsigned char)); // 1 byte * 256 = 256 bytes
    unsigned int code_ptr = 0;
    unsigned int line = 0;

    bool expect_on = false;
    Expect expected;

    uint32_t labels[256] = { 0 };

    for (unsigned int i = 0; i < len; i++) {
        uint8_t opcode = OPCODE(tokens[i]);

        if (opcode == TOKEN_NEWLINE) line ++;
        
        switch (opcode) {
            case TOKEN_INT:
                if ((tokens[i] & 0xff) < 16) {
                    code[code_ptr] |= (tokens[i] & 0xff);
                } else {
                    code_ptr++;
                    code[code_ptr] = (tokens[i] & 0xff);
                }
                break;
            case TOKEN_LABEL_DECL:
                labels[tokens[i] & 0xff] = code_ptr;
                break;
            case TOKEN_LABEL_REF:
                code_ptr++;
                code[code_ptr] = labels[tokens[i] & 0xff];
                break;
            default:
                break;
        }
        
        if (!expect_on && opcode != TOKEN_NEWLINE) {
            if (opcode < TOKEN_REG_A) {
                code[code_ptr] = opcode << 4;
                expected = INSTRUCTION_EXPECTS[opcode];
                expect_on = true;
            }
        } else if (opcode != TOKEN_NEWLINE) {
            if (expected.operands == (expected.expect_ptr + 1)) {
                expect_on = false;
                code_ptr++;
            }
            if (!validate_expect(&expected, tokens[i], line)) {
                fprintf(stderr, "Line %d: Error: Unexpected operand while parsing: %d\n", line, tokens[i]);
                exit(1);
            }
        }
    }
    if (code_ptr >= 240) {
        fprintf(stderr, "Error: Program size exceeds 240 bytes.\n");
        exit(1);
    }
    printf("%d byte(s) of code generated. [ALL OK]\n", code_ptr);

    return code;
}
