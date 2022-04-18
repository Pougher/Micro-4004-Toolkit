#include "../include/argument.h"

Arguments parse_args(int argc, char** argv)
{
    Arguments args = {
        .in_file = NULL,
        .out_file = "out.bin"
    };

    uint64_t already_parsed = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && !(already_parsed & 0x1)) {
            args.in_file = malloc_copy(argv[i + 1]);
            already_parsed |= 0x1;
            i++;
        } else if (strcmp(argv[i], "-o") == 0 && !(already_parsed & 0x02)) {
            args.out_file = malloc_copy(argv[i + 1]);
            already_parsed |= 0x02;
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("Usage: %s [-i <input file>] [-o <output file>]\n", argv[0]);
            exit(0);
        } else {
            printf("Error: Unknown or redefined argument: %s\n", argv[i]);
            exit(1);
        }
    }

    return args;
}
