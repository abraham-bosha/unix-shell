#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "command.h"
#include "redirection.h"

int apply_redirections(command_t *cmd)
{
    size_t i;

    for (i = 0; i < cmd->redirc; i++)
    {
        redirection_t *redir = &cmd->redirs[i];

        int fd = - 1;

        if (redir->type == REDIR_INPUT)
        {
            fd = open(redir->path, O_RDONLY);
        }
        else if (redir->type == REDIR_OUTPUT)
        {
            fd = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else if (redir->type == REDIR_APPEND)
        {
            fd = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }

        if (fd < 0) 
        {
            perror(redir->path);
            return (-1);
        }

        if (dup2(fd, redir->fd) < 0)
        {
            perror("dup2");
            close(fd);
            return (-1);
        }

        close(fd);
    }

    return (0);
}

