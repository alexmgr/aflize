#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "aflize.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Insufficient number of arguments passed to AFL wrapper\n";
        std::cerr << "Expecting filename as first argument\n";
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];

#ifdef AFLIZE_PERSIST
    while (__AFL_LOOP(AFLIZE_PERSIST_ITERATIONS))
#endif
    {
        std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type file_size = ifs.tellg();

        if (file_size > 0) {
            std::vector<char> buffer(file_size);

            ifs.seekg(0, std::ios::beg);
            ifs.read(&buffer[0], file_size);

            afl_forward(&buffer[0], file_size);
        } else if (file_size == 0) {
            std::cerr << "Empty file: " << filename << "\n";
            exit(EXIT_FAILURE);
        } else {
            std::cerr << "Unable to access: " << filename << "\n";
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}

