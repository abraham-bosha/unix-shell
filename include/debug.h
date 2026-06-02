#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

#define DEBUG_PRINT(...) \
    do { \
        fprintf(stderr, "[DEBUG] %s:%d: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)

#else

#define DEBUG_PRINT(...) \
    do {} while (0)

#endif

#include "command.h"
#include "pipeline.h"

void debug_status(int status);
void debug_pipeline(const pipeline_t *pipeline);

#endif

