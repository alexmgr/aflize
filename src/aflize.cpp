#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "aflize.h"

#define AFLIZE_BUF_SIZE 1024*1024

int main(int argc, char **argv) {

    std::vector<char> buffer(AFLIZE_BUF_SIZE + 1);

#ifdef AFLIZE_PERSIST
    while (__AFL_LOOP(1000)) {
        std::fill(buffer.begin(), buffer.end(), 0);
#endif

    std::cin.read(buffer.data(), AFLIZE_BUF_SIZE);
    buffer[std::cin.gcount()] = 0;

    afl_forward(&buffer[0]);

#ifdef AFLIZE_PERSIST
    {
#endif

    exit(EXIT_SUCCESS);
}

