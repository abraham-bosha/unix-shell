#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "command.h"

static int parse_key_and_value(char *str, char **key, char **value)
{
    char *ptr = strchr(str, '=');

    if (ptr == NULL)
        return (-1);

    *ptr = '\0';

    *key = str;
    *value = ptr + 1;

    return (0);
}

int builtin_export(command_t *cmd)
{
    char *key;
    char *value;
    
    for (size_t i = 1; i < cmd->argc; i++)
    {

        if (parse_key_and_value(cmd->argv[i], &key, &value) < 0)
        {
            fprintf(stderr, "export: invalid assignment\n");
            return (1);
        }

        if (*key == '\0')
        {
            fprintf(stderr, "export: invalid identifier\n");
            return (1);
        }

        if (setenv(key, value, 1) < 0)
        {
            perror("export");
            return (1);
        }
    }

    return (0);
}
