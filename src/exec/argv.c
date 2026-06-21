#include <stdlib.h>
#include <stddef.h>

#include "command.h"
#include "pipeline.h"

int command_build_argv(command_t *cmd)
{
    cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));

    if (!cmd->argv)
        return (-1);

    for (size_t i = 0; i < cmd->argc; i++)
        cmd->argv[i] = cmd->args[i].value;

    cmd->argv[cmd->argc] = NULL;

    return (0);
}

int pipeline_build_argv(pipeline_t *pipeline)
{
    for (size_t i = 0; i < pipeline->cmdc; i++)
    {
        if (command_build_argv(&pipeline->commands[i]) < 0)
            return (-1);
    }

    return (0);
}
