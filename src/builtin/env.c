#include <stdio.h>

#include "command.h"

extern char **environ;

int builtin_env(command_t *cmd)
{
    (void)cmd;

    for (int i = 0; environ[i] != NULL; i++)
        puts(environ[i]);

    return (0);
}

