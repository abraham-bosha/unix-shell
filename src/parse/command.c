#include <stdlib.h>
#include <ctype.h>

#include "parser_internal.h"
#include "command.h"
#include "redirection.h"

int command_add_argument(command_t *command, char *arg)
{
    char **tmp;

    tmp = realloc(command->argv, sizeof(*tmp) * (command->argc + 2));

    if (!tmp)
        return (-1);

    command->argv = tmp;

    command->argv[command->argc] = arg;

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

        command_add_argument(cmd, arg);
    }
}

void command_destroy(command_t *cmd)
{
    free(cmd->argv);

    free(cmd->redirs);
}
