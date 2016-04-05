#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "aflize.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Insufficient number of arguments passed to AFL wrapper\n");
        exit(EXIT_FAILURE);
    }

    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(file_size + 1);
    if (!file.read(buffer.data(), file_size))
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[file_size] = 0;

    afl_forward(&buffer[0]);

    exit(EXIT_SUCCESS);
}

