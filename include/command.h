#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>
#include <stdbool.h>
#include "redirection.h"

typedef struct command
{
    char **argv;

    size_t argc;

    redirection_t *redirs;
    
    size_t redirc;
} command_t;

int command_add_argument(command_t *cmd, char *arg);

void command_destroy(command_t *cmd);

#endif
