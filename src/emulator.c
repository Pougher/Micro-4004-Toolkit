/********************************************/
/* Micro 4004 Macro Emulator v1.0           */
/* Part of the Micro 4004 Toolkit           */
/*                                          */
/* MIT License, redistributable             */
/********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/fileio.h"
#include "../include/cpu.h"


int main(int argc, char** argv)
{
    printf("Micro4004 Emulator [Version 1.0]\n");
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <rom>\n", argv[0]);
        exit(1);
    }
    unsigned char* rom = read_binary_file(argv[1]);
    if (rom == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        exit(1);
    }

    CPU_t cpu;
    bool running = true;

    // initializations
    cpu_init(&cpu);

    // read commands
    //cpu_exec(&cpu, rom, cycles);
    while (running) {
        printf("> ");
        char cmd[16] = { 0 };

        scanf("%15s", cmd);
        if (STRINGEQ(cmd, "run")) {
            printf("Cycles> ");
            uint64_t cyc;
            scanf("%llu", &cyc);

            cpu_exec(&cpu, rom, cyc);
        } else if (STRINGEQ(cmd, "exit") || STRINGEQ(cmd, "quit")) {
            exit(0);
        } else if (STRINGEQ(cmd, "dump")) {
            cpu_dump(&cpu);
        } else if (STRINGEQ(cmd, "clock")) {
            printf("Clock> ");
            uint64_t cyc;
            scanf("%llu", &cyc);

            if (cyc > 1000) {
                printf("Warning: Clock rate is limited to 1000 cycles per second (1 kHz).\n");
                cpu.HZ = 1;
            } else {
                printf("%llu\n", 1000 / cyc);
                cpu.HZ = 1000 / cyc;
            }
        } else if (STRINGEQ(cmd, "reset")) {
            cpu_init(&cpu);
        } else if (STRINGEQ(cmd, "help")) {
            printf("Commands:\n");
            printf("  run <cycles>\t\tRun the CPU for the specified number of cycles.\n");
            printf("  exit/quit  \t\tExit the emulator.\n");
            printf("  dump       \t\tDump the CPU state.\n");
            printf("  clock <speed>\t\tSet the clock speed.\n");
            printf("  reset      \t\tReset the CPU.\n");
            printf("  help       \t\tPrint this help message.\n");
            printf("  clear      \t\tClear the screen.\n");
        } else if (STRINGEQ(cmd, "clear")) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        } else {
            printf("Unknown command: '%s'.\n", cmd);
        }
    }
}
