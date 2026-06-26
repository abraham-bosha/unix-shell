#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

#include "variable.h"
#include "command.h"
#include "shell.h"

static int parse_name_and_value(
    char *str,
    char **name,
    char **value)
{
    char *eq = strchr(str, '=');

    if (!eq)
        return (-1);

    *eq = '\0';

    *name = str;
    *value = eq + 1;

    return (0);
}

bool is_assignment(const command_t *cmd)
{
    size_t i = 0;
    char *str = cmd->argv[0];

    if (cmd->argc != 1)
        return false;

    if (!str || str[0] == '\0')
        return false;

    if (!isalpha((unsigned char)str[0]) && str[0] != '_')
        return false;

    while (str[i] && str[i] != '=')
    {
        if (!isalnum((unsigned char)str[i]) && str[i] != '_')
            return false;

        i++;
    }

    return str[i] == '=';
}

int shell_set_variable(
    shell_t *shell,
    const char *name,
    const char *value)
{
    variable_t *tmp;

    for (int i = 0; i < shell->varc; i++)
    {
        if (strcmp(shell->vars[i].name, name) == 0)
        {
            char *new_value = strdup(value);

            if (!new_value)
                return (-1);

            free(shell->vars[i].value);

            shell->vars[i].value = new_value;

            return (0);
        }
    }

    tmp = realloc(shell->vars,
                  sizeof(*tmp) * (shell->varc + 1));

    if (!tmp)
        return (-1);

    shell->vars = tmp;

    shell->vars[shell->varc].name = strdup(name);
    shell->vars[shell->varc].value = strdup(value);

    if (!shell->vars[shell->varc].name ||
        !shell->vars[shell->varc].value)
        return (-1);

    shell->varc++;

    return (0);
}

const char *shell_get_variable(shell_t *shell, const char *name)
{
    for (int i = 0; i < shell->varc; i++)
    {
        if (strcmp(shell->vars[i].name, name) == 0)
            return shell->vars[i].value;
    }

    return NULL;
}

int shell_unset_variable(shell_t *shell, const char *name)
{
    int found = -1;

    for (int i = 0; i < shell->varc; i++)
    {
        if (strcmp(shell->vars[i].name, name) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
        return (0);

    free(shell->vars[found].name);
    free(shell->vars[found].value);

    for (int i = found; i < shell->varc - 1; i++)
        shell->vars[i] = shell->vars[i + 1];

    shell->varc--;

    if (shell->varc == 0)
    {
        free(shell->vars);
        shell->vars = NULL;
    }

    return (0);
}

void execute_assignment(shell_t *shell, command_t *cmd)
{
    char *copy;
    char *name;
    char *value;

    copy = strdup(cmd->argv[0]);

    if (!copy)
        return;

    if (parse_name_and_value(copy, &name, &value) == 0)
        shell_set_variable(shell, name, value);

    free(copy);
}

void shell_destroy(shell_t *shell)
{
    if (shell->oldpwd)
        free(shell->oldpwd);

    for (int i = 0; i < shell->varc; i++)
    {
        free(shell->vars[i].name);
        free(shell->vars[i].value);
    }

    if (shell->vars)
        free(shell->vars);
}
