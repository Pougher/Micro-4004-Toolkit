#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "opcode.h"
#include "util.h"

#define FLAG_C 0x01 // Carry flag
#define FLAG_Z 0x02 // Zero flag

#define uint4_t uint8_t // more descriptive name for 4 bit integers.

typedef struct {
    uint8_t F;
    uint4_t A;
    uint4_t X;
    uint8_t PC;
    uint64_t HZ;
    uint4_t mem[16];
} CPU_t;

// Initialize the CPU.
void cpu_init(CPU_t* cpu);

// Main CPU execution loop
void cpu_exec(CPU_t* cpu, unsigned char* rom, uint64_t cycles);

// Dump function to print out all data in the CPU.
void cpu_dump(CPU_t* cpu);
#endif
