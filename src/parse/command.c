#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>

#include "parser_internal.h"
#include "command.h"
#include "redirection.h"
#include "argument.h"

int command_add_argument(command_t *command, const char *value, quote_type_t quote)
{
    argument_t *tmp;
    char *copy;

    copy = strdup(value);
    if (!copy)
        return (-1);

    tmp = realloc(command->args, sizeof(*tmp) * (command->argc + 1));

    if (!tmp)
    {
        free(copy);
        return (-1);
    }

    command->args = tmp;

    command->args[command->argc].value = copy;
    command->args[command->argc].quote = quote;

    command->argc++;

    return (0);
}

void parse_command(command_t *cmd, char *segment)
{
    char *token = segment;
    quote_type_t quote;
    char *arg;

    while (*token)
    {
        while (*token && isspace((unsigned char)*token))
            token++;

        if (!*token)
            break;
        
        if (*token == '>' || *token == '<')
        {
            if (parse_redirection(cmd, &token))
                return;
            continue;
        }
        
        arg = parse_word(&token, &quote);
        if (!arg)
            return;

        if (command_add_argument(cmd, arg, quote) < 0)
        {
            free(arg);
            return;
        }

        free(arg);
    }
}

void command_destroy(command_t *cmd)
{
    if (!cmd)
        return;

    for (size_t i = 0; i < cmd->argc; i++)
        free(cmd->args[i].value);

    free(cmd->argv);

    redirection_destroy(cmd);
}
