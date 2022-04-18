#include "expected.h"

bool validate_expect(Expect* expect, AsmOp op, uint32_t line)
{
    Expect_t FINAL_TYPE;
    switch (OPCODE(op)) {
        case TOKEN_INT:
            if ((op & 0xff) < 16) {
                FINAL_TYPE = EXPECT_IMM4;
            } else {
                FINAL_TYPE = EXPECT_IMM8;
            }
            break;
        case TOKEN_REG_A:
            FINAL_TYPE = EXPECT_REGISTER_A;
            break;
        case TOKEN_REG_X:
            FINAL_TYPE = EXPECT_REGISTER_B;
            break;
        case TOKEN_LABEL_REF:
            FINAL_TYPE = EXPECT_IMM8;
            break;
        default:
            fprintf(stderr, "Line %d: Error: Unexpected token while parsing: %d\n", line, op);
            exit(1);
            break;
    }

    if (expect->expected[expect->expect_ptr] & FINAL_TYPE) {
        expect->expect_ptr++;
        return true;
    }
    return false;
}
