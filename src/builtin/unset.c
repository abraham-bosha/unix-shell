#include <stdio.h>
#include <stdlib.h>

#include "command.h"

int builtin_unset(command_t *cmd)
{
    if (cmd->argc != 2)
    {
        fprintf(stderr, "unset: usage: unset NAME\n");
        return (1);
    }

    if (unsetenv(cmd->argv[1]) < 0)
    {
        perror("unset");
        return (1);
    }

    return (0);
}
