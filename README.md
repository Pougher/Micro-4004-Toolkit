# Micro 4004 Toolkit

The Micro 4004 is a 4-bit CPU I plan on building, having 2 general-purpose registers and an 8-bit address space.
It was inspired by the 8-bit computer [Ben Eater](https://www.youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU)
built.

### General Specifications
The Micro4004 supports the following:
- An 8 bit address space with 16 bytes of addressable RAM
- 2 General purpose 4 bit registers
- NOT, AND, XOR, OR, ADD and SUB instructions
- Carry and Zero flag
- Up to 240 bytes of code

### Compilation
To compile the Micro 4004 toolkit, only a single command is required:
```
/path/to/repo@user $ make
```

### Assembler

The assembler allows for the compilation of all instructions found in the [architecture file](arch.txt), along with
some comfort features such as macros, defined with the syntax:
```
.macro <NAME>
    ... code ...
.end
```
And can be referenced in code just by writing out the macro name.

The assembler also allows for the `.offset <NAME>` directive, which creates a constant that is offset in RAM (`0xf0` onwards)
that can be referenced by code in much the same way as macros.

To compile on any platform, use `make` in the root directory of this repo.

To assemble files, use
```
./bin/m4004as -i <INPUT FILE> -o <OUTPUT FILE (optional)>
```

### Emulator

The emulator allows for ROM files compiled with the [assembler](#assembler) to be emulated. There are a few commands that the emulator
supports which can be listed with the `help` command. There is no need for you to specify any command flags either, only the ROM file.

To use the emulator in the fastest way possible, the following commands may be used:
```
$ make
$ ./bin/m4004emu <ROM>

> run 50
```
The `run 50` line means run the CPU for 50 cycles, each taking ~1 ms (maximum clock is 1 kHz).
The `dump` command may be used after the `run` command to examine the contents of the internal registers, RAM, etc.
