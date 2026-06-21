#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <stdbool.h>

typedef struct command command_t;

typedef enum redir_type
{
    REDIR_INPUT,
    REDIR_OUTPUT,
    REDIR_APPEND,
} redir_type_t;

typedef struct redirection
{
    int fd;

    redir_type_t type;

    char *path;

} redirection_t;

int command_add_redirection(command_t *command, int fd, redir_type_t type, char *path);

int apply_redirections(command_t *cmd);

void redirection_destroy(command_t *cmd);

#endif

