#ifndef AFLIZE_H
#define AFLIZE_H

#define AFLIZE_BUF_SIZE 1024*1024
#define AFLIZE_PERSIST_ITERATIONS 1000

#ifdef __cplusplus
extern "C" {
#endif

void afl_forward(char* buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif //AFLIZE_H

