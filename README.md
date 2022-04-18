# Micro 4004 Assembler

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
For now, there is no emulator, however I will be working on that.
