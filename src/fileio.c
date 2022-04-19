#include "../include/fileio.h"

char* load_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        if (fseek(file, 0L, SEEK_END) == 0) {
            long bufsize = ftell(file);

            if (bufsize == -1) {
                printf("Error: Failed to read file - returned negative length: '%s'\n", filename);
                fclose(file);
                exit(1);
            }
            char* source = malloc(sizeof(char) * (bufsize + 1));
            if (fseek(file, 0L, SEEK_SET) != 0) {
                fprintf(stderr, "Error: Failed to read file - could not seek to start: '%s'\n", filename);
                fclose(file);
                exit(1);
            }
            
            size_t newLen = fread(source, sizeof(char), bufsize, file);
            if (ferror(file) != 0) {
                fprintf(stderr, "Error: Failed to read file");
            } else {
                source[newLen++] = '\0';
            }
            return source;
        }
    } else {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    return NULL;
}

void write_binary_file(char* name, unsigned char* data, size_t len)
{
    FILE* file = fopen(name, "wb");
    if (file != NULL) {
        fwrite(data, sizeof(unsigned char), len, file);
        fclose(file);
    } else {
        printf("Error: Could not open file %s\n", name);
        exit(1);
    }
}

unsigned char* read_binary_file(char* name)
{
    FILE* file = fopen(name, "rb");
    if (file != NULL) {
        if (fseek(file, 0L, SEEK_END) == 0) {
            long bufsize = ftell(file);

            if (bufsize == -1) {
                printf("Error: Failed to read file - returned negative length: '%s'\n", name);
                fclose(file);
                exit(1);
            }
            unsigned char* source = malloc(sizeof(unsigned char) * (bufsize + 1));
            if (fseek(file, 0L, SEEK_SET) != 0) {
                fprintf(stderr, "Error: Failed to read file - could not seek to start: '%s'\n", name);
                fclose(file);
                exit(1);
            }
            
            size_t newLen = fread(source, sizeof(unsigned char), bufsize, file);
            if (ferror(file) != 0) {
                fprintf(stderr, "Error: Failed to read file");
            } else {
                source[newLen++] = '\0';
            }
            return source;
        }
    } else {
        printf("Error: Could not open file %s\n", name);
        exit(1);
    }
    return NULL;
}

