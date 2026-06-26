#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "command.h"
#include "variable.h"
#include "shell.h"

int builtin_unset(shell_t *shell, command_t *cmd)
{
    if (cmd->argc < 2)
    {
        fprintf(stderr, "unset: usage: unset NAME\n");
        return (1);
    }

    for (size_t i = 1; i < cmd->argc; i++)
    {
        shell_unset_variable(shell, cmd->argv[i]);

        if (unsetenv(cmd->argv[i]) < 0)
        {
            perror("unset");
            return (1);
        }
    }

    return (0);
}
