#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

// @NOTE: Avoidance of unistd.h is prevelant here, as getopt is not used.
//        This is to ensure that the assembler runs on all platforms.

typedef struct {
    char* out_file;
    char* in_file;
} Arguments;

// Function to parse command line arguments given to the application
Arguments parse_args(int argc, char** argv);

#endif
