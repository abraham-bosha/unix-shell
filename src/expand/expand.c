#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "expand.h"
#include "pipeline.h"

static bool is_variable(const char *arg)
{
    return (arg && arg[0] == '$' && arg[1] != '\0');
}

static char *itoa(int n)
{
    char status_str[32];

    snprintf(status_str, sizeof(status_str), "%d", n);

    return strdup(status_str);
}

static char *resolve_variable(shell_t *shell, const char *arg)
{
    char *value;

    if (strcmp(arg, "?") == 0)
    {
        value = itoa(shell->last_exit_status);
        return value;
    }

    value = getenv(arg);

    if (!value)
    {
        fprintf(stderr, "warning: undefined variable: %s\n", arg + 1);
        value = "";
    }

    return strdup(value);
}

static char *expand_arg(shell_t *shell, const char *arg)
{
    const char *value;

    if (!is_variable(arg))
        return strdup(arg);

    value = arg + 1;

    return resolve_variable(shell, value);
}

static int expand_command(shell_t *shell, command_t *cmd)
{
    char *expanded;

    for (size_t i = 0; i < cmd->argc; i++)
    {
        expanded = expand_arg(shell, cmd->argv[i]);

        if (!expanded)
            return (-1);

        free(cmd->argv[i]);

        cmd->argv[i] = expanded;
    }

    return (0);
}

int expand_pipeline(shell_t *shell, pipeline_t *pipeline)
{
    for (size_t i = 0; i < pipeline->cmdc; i++)
    {
        if (expand_command(shell, &pipeline->commands[i]) < 0)
            return (-1);
    }

    return (0);
}
