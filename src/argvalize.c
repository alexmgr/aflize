#include <stdio.h>
#include <stdlib.h>

#include "aflize.h"


int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Insufficient number of arguments passed to AFL wrapper\n");
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0L, SEEK_END);
    long file_size = ftell(f);
    rewind(f);

    char buf[file_size];
    if (fread(buf, file_size, 1, f) != 1) {
        fclose(f);
        perror("fread");
        exit(EXIT_FAILURE);
    }
    fclose(f);

    afl_forward(buf, (size_t)file_size);

    return EXIT_SUCCESS;
}
