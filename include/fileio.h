#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to load file data from a file. Returns a malloc'd pointer
// that must be freed after use.
char* load_file(const char* filename);

// Function to write binary data to a file.
void write_binary_file(char* name, unsigned char* data, size_t len);

// Function to read a binary file into a character array.
unsigned char* read_binary_file(char* name);

#endif
