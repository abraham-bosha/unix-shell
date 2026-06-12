#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include "exec.h"
#include "command.h"
#include "redirection.h"
#include "exec_path.h"

extern char **environ;

int decode_exit_status(int status) 
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);

    return (1);
}

void exec_command_or_die(command_t *cmd)
{
    char *path;

    if (apply_redirections(cmd) < 0)
        _exit(1);

    path = resolve_path(cmd->argv[0]);
    if (!path)
    {
        fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
        _exit(127);
    }

    execve(path, cmd->argv, environ);

    perror(path);

    free(path);
    _exit(127);
}

