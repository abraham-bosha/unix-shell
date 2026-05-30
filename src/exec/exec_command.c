#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>

#include "exec.h"

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

void exec_command_or_die(command_t *cmd) 
{
    execvp(cmd->argv[0], cmd->argv);

    perror(cmd->argv[0]);

    _exit(127);
}

int execute_command(command_t *cmd)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }

    if (pid == 0)
        exec_command_or_die(cmd);

    if (waitpid(pid, &status, 0) < 0)
    {
        perror("waitpid");
        return (-1);
    }

    report_status(status);

    return (status);
}

