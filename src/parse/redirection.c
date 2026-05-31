#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#include "redirection.h"
#include "command.h"

bool validate_redirection_syntax(const char *line, char *unexpected)
{
    while (*line)
    {
        while (*line &&
               isspace((unsigned char)*line))
        {
            line++;
        }

        if (!*line)
            break;

        if (*line == '<')
        {
            line++;

            while (*line &&
                   isspace((unsigned char)*line))
            {
                line++;
            }

            if (!*line || *line == '<' || *line == '>')
            {
                if (unexpected)
                    *unexpected = *line;

                return false;
            }

            continue;
        }

        if (*line == '>')
        {
            line++;

            if (*line == '>')
                line++;

            if (*line == '>')
            {
                if (unexpected)
                    *unexpected = '>';

                return false;
            }

            while (*line &&
                   isspace((unsigned char)*line))
            {
                line++;
            }

            if (!*line || *line == '<' || *line == '>')
            {
                if (unexpected)
                    *unexpected = *line;

                return false;
            }

            continue;
        }

        while (*line &&
               !isspace((unsigned char)*line) &&
               *line != '<' &&
               *line != '>')
        {
            line++;
        }
    }

    return true;
}

int command_add_redirection(command_t *command, int fd, redir_type_t type, const char *path)
{
    redirection_t *tmp;

    tmp = realloc(command->redirs, sizeof(*tmp) * (command->redirc + 1));

    if (!tmp)
        return (-1);

    command->redirs = tmp;

    command->redirs[command->redirc].fd = fd;
    command->redirs[command->redirc].type = type;
    command->redirs[command->redirc].path = path;

    command->redirc++;

    return (0);
}

int parse_redirection(command_t *cmd, char **cursor)
{
    char *p = *cursor;

    const char *path;
    redir_type_t type;
    int fd;

    (*cursor)++;
    if (**cursor == '>')
        (*cursor)++;

    while (**cursor && isspace((unsigned char)**cursor))
        (*cursor)++;

    if (*p == '<')
    {
        path = parse_word(cursor);
        type = REDIR_INPUT;
        fd = STDIN_FILENO;
    }
    else if (*p == '>' && p[1] == '>')
    {
        path = parse_word(cursor);
        type = REDIR_APPEND;
        fd = STDOUT_FILENO;
    }
    else if (*p == '>')
    {
        path = parse_word(cursor);
        type = REDIR_OUTPUT;
        fd = STDOUT_FILENO;
    }

    return command_add_redirection(cmd, fd, type, path);
}

