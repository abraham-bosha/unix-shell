#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>
#include <stdbool.h>

#include "redirection.h"
#include "argument.h"

typedef struct command
{
    argument_t *args;
    size_t argc;

    char **argv;

    redirection_t *redirs;    
    size_t redirc;
} command_t;

int command_add_argument(command_t *cmd, const char *value, quote_type_t quote);

void command_destroy(command_t *cmd);

#endif
