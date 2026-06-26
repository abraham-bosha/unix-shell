#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "expand.h"
#include "pipeline.h"
#include "argument.h"
#include "variable.h"

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

static const char *resolve_variable(shell_t *shell, const char *name)
{
    const char *value;

    if (strcmp(name, "?") == 0)
    {
        value = itoa(shell->last_exit_status);
        return value;
    }

    value = shell_get_variable(shell, name);
    
    if (!value)
        value = getenv(name);

    if (!value)
        value = "";

    return strdup(value);
}

static const char *expand_arg(shell_t *shell, const char *arg)
{
    const char *value;

    if (!is_variable(arg))
        return strdup(arg);

    value = arg + 1;

    return resolve_variable(shell, value);
}

static int expand_command(shell_t *shell, command_t *cmd)
{
    const char *expanded;

    for (size_t i = 0; i < cmd->argc; i++)
    {
        argument_t *arg = &cmd->args[i];

        if (arg->quote == QUOTE_SINGLE)
            continue;

        expanded = expand_arg(shell, arg->value);

        if (!expanded)
            return (-1);

        free(arg->value);

        arg->value = (char *)expanded;
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
