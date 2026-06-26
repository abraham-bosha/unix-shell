#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "command.h"

static int parse_key_and_value(char *str, char **key, char **value)
{
    char *eq = strchr(str, '=');

    if (eq == NULL)
        return (-1);

    *eq = '\0';

    *key = str;
    *value = eq + 1;

    return (0);
}

int builtin_export(command_t *cmd)
{
    char *key;
    char *value;
    char *copy; 

    copy = strdup(cmd->argv[1]);

    if (!copy)
        return (1);

    for (size_t i = 1; i < cmd->argc; i++)
    {
        if (parse_key_and_value(copy, &key, &value) < 0)
        {
            free(copy);
            fprintf(stderr, "export: invalid assignment\n");
            return (1);
        }

        if (*key == '\0')
        {
            free(copy);
            fprintf(stderr, "export: invalid identifier\n");
            return (1);
        }

        if (setenv(key, value, 1) < 0)
        {
            free(copy);
            perror("export");
            return (1);
        }
    }

    free(copy);

    return (0);
}
