#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "shell.h"
#include "command.h"
#include "string.h"

int builtin_exit(shell_t *shell, command_t *cmd)
{
    char *endptr;

    if (cmd->argc > 2)
    {
        fprintf(stderr, "unix-shell: exit: too many arguments\n");
        return (1);
    }

    fprintf(stdout, "exit\n");
    
    if (cmd->argc == 1)
    {
        shell->running = false;

        shell->exit_status = shell->last_exit_status;
        
        return (0);
    }

    errno = 0;
    long value = strtol(cmd->argv[1], &endptr, 10);

    if ((cmd->argv[1] == endptr || *endptr != '\0') || ((value == LONG_MAX || value == LONG_MIN) && errno == ERANGE))
    {   
        fprintf(stderr, "unix-shell: exit: %s: numeric argument required\n", cmd->argv[1]);

        shell->running = false;

        shell->exit_status = 2;

        return (1);
    }

    shell->running = false;
    shell->exit_status = (int)value;

    return (0);
}
