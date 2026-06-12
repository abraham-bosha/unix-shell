#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>

#include "parser_internal.h"
#include "command.h"
#include "redirection.h"

int command_add_argument(command_t *command, char *arg)
{
    char **tmp;
    char *copy;

    copy = strdup(arg);
    if (!copy)
        return (-1);

    tmp = realloc(command->argv, sizeof(*tmp) * (command->argc + 2));

    if (!tmp)
    {
        free(copy);
        return (-1);
    }

    command->argv = tmp;

    command->argv[command->argc] = copy;

    command->argc++;

    command->argv[command->argc] = NULL;

    return (0);
}

void parse_command(command_t *cmd, char *segment)
{
    char *token = segment;
    char *arg;

    while (*token)
    {
        while (*token && isspace((unsigned char)*token))
            token++;

        if (!*token)
            break;
        
        if (*token == '>' || *token == '<')
        {
            parse_redirection(cmd, &token);
            continue;
        }
        
        arg = parse_word(&token);

        if (command_add_argument(cmd, arg) < 0)
            return;
    }
}

void command_destroy(command_t *cmd)
{
    if (!cmd)
        return;

    for (size_t i = 0; i < cmd->argc; i++)
        free(cmd->argv[i]);

    free(cmd->argv);

    redirection_destroy(cmd);
}
