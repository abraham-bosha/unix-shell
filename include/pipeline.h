#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdbool.h>
#include <stddef.h>

#include "command.h"

typedef struct pipeline
{
    char *source;
    char *scratch;

    command_t *commands;
    size_t cmdc;

    bool background;
} pipeline_t;

pipeline_t *pipeline_create(const char *line);

void pipeline_destroy(pipeline_t *pipeline);

#endif
