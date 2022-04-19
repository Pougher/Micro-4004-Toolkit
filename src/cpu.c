#include "cpu.h"

void cpu_init(CPU_t* cpu)
{
    cpu->F = 0;
    cpu->A = 0;
    cpu->X = 0;
    cpu->PC = 0;
    cpu->HZ = 0;
}

void cpu_exec(CPU_t* cpu, unsigned char* rom, uint64_t cycles)
{
    while (cpu->PC != 0xFF && cycles > 0) {
        uint8_t opcode = rom[cpu->PC] >> 4;
        uint8_t operand = rom[cpu->PC] & 0x0F;
        uint8_t addr;

        // Dump all of RAM, and the CPU registers
        delay(cpu->HZ);
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
        cpu_dump(cpu);

        cpu->PC++;
        switch (opcode) {
            case TOKEN_LDA:
                cpu->A = operand;
                break;
            case TOKEN_LDX:
                cpu->X = operand;
                break;
            case TOKEN_LRA:
                addr = rom[cpu->PC] - 0xf0;
                cpu->A = cpu->mem[addr];
                break;
            case TOKEN_LRX:
                addr = rom[cpu->PC] - 0xf0;
                cpu->X = cpu->mem[addr];
                break;
            case TOKEN_STA:
                addr = rom[cpu->PC] - 0xf0;
                cpu->mem[addr] = cpu->A;
                cpu->PC++;
                break;
            case TOKEN_XOR:
                cpu->A ^= cpu->X;
                break;
            case TOKEN_ADD:
                cpu->A = cpu->A & 0x0f;
                cpu->X = cpu->X & 0x0f;
                cpu->A += cpu->X;
                if (cpu->A > 0x0f) {
                    cpu->F |= FLAG_C;
                }
                break;
            case TOKEN_SUB:
                cpu->A = cpu->A & 0x0f;
                cpu->X = cpu->X & 0x0f;
                cpu->A -= cpu->X;
                if (cpu->A > 0x0f) {
                    cpu->F |= FLAG_C;
                } else if (cpu->A == 0x00) {
                    cpu->F |= FLAG_Z;
                }
                break;
            case TOKEN_AND:
                cpu->A &= cpu->X;
                break;
            case TOKEN_OR:
                cpu->A |= cpu->X;
                break;
            case TOKEN_NOT:
                cpu->A = ~cpu->A;
                break;
            case TOKEN_JMP:
                cpu->PC = rom[cpu->PC];
                break;
            case TOKEN_JC:
                if (cpu->F & FLAG_C) {
                    cpu->PC = rom[cpu->PC];
                } else {
                    cpu->PC++;
                }
                break;
            case TOKEN_JZ: 
                if (cpu->F & FLAG_Z) {
                    cpu->PC = rom[cpu->PC];
                } else {
                    cpu->PC++;
                }
                break;
            case TOKEN_TAX:
                cpu->X = cpu->A;
                break;
            case TOKEN_TXA:
                cpu->A = cpu->X;
                break;
        }
        cycles--;
    }
}

void cpu_dump(CPU_t* cpu)
{
        printf("== REGISTER DUMP: ==\n");
        printf("A: %01x\n", cpu->A & 0x0f);
        printf("X: %01x\n", cpu->X & 0x0f);
        printf("F: %01x\n", cpu->F);
        printf("PC: %02x\n", cpu->PC);

        printf("== MEMORY DUMP: ==\n0:   ");
        for (uint8_t i = 0; i < 16; i++) {
            printf("%02x ", cpu->mem[i]);
            if ((i + 1) % 8 == 0 && i != 15) {
                printf("\n%d:   ", i + 1);
            }
        }
        printf("\n");
}
