#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>

typedef struct command
{
    char **argv;
    size_t argc;
} command_t;

#endif
