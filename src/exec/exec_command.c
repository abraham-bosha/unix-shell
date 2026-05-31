#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>

#include "exec.h"
#include "command.h"
#include "redirection.h"

void report_status(int status)
{
    if (WIFEXITED(status))
        printf("[exit=%d]\n", WEXITSTATUS(status));
    
    else if(WIFSIGNALED(status))
        printf("[signal=%d]\n", WTERMSIG(status));
    
    else if(WIFSTOPPED(status))
        printf("[stopped=%d]\n", WSTOPSIG(status));

#ifdef WIFCONTINUED
    else if(WIFCONTINUED(status))
        printf("[continued]\n");
#endif
}

int decode_exit_status(int status) 
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);

    return 1;
}

void exec_command_or_die(command_t *cmd) 
{
    if (apply_redirections(cmd) < 0)
        _exit(1);

    execvp(cmd->argv[0], cmd->argv);

    perror(cmd->argv[0]);

    _exit(127);
}

