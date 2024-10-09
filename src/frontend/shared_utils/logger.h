#ifndef FOX_LOGGER_H_
#define FOX_LOGGER_H_

#include <stdio.h>
#include <stdlib.h>

// TODO: Implement non-fatal logger

#define FATAL_ERR(from, msg)                                         \
    do {                                                             \
        fprintf(stderr, "[%s | in %s]: %s\n", from, __func__, msg);  \
        exit(EXIT_FAILURE);                                          \
    } while(0)                                                       \
    
#define FATAL_ERR_FMT(from, fmt, ...)                                \
    do {                                                             \
        fprintf(stderr, "[%s | in %s]: ", from, __func__);           \
        fprintf(stderr, fmt, ##__VA_ARGS__);                         \
        exit(EXIT_FAILURE);                                          \
    }                                                                \

#endif

