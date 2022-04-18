#include "../include/opcode.h"

AsmOp new_token(AsmType t, uint8_t data)
{
    return ((uint16_t)t << 8) | data;
}
