#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "exec.h"

static int execute_two_command_pipeline(command_t *left, command_t *right)
{
    int pipefd[2];
    
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        return (-1);
    }

    pid_t left_pid;

    left_pid = fork();

    if (left_pid < 0)
    {
        perror("fork");

        close(pipefd[0]);
        close(pipefd[1]);

        return (-1);
    }
    
    if (left_pid == 0) 
    {
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) 
        {
            perror("dup2");
            _exit(1);
        }
        
        close(pipefd[0]);
        close(pipefd[1]);

        exec_command_or_die(left);
    }

    pid_t right_pid;
    
    right_pid = fork();

    if (right_pid < 0)
    {
        perror("fork");

        close(pipefd[0]);
        close(pipefd[1]);

        return (-1);
    }

    if (right_pid == 0)
    {
        if (dup2(pipefd[0], STDIN_FILENO) < 0)
        {
            perror("dup2");
            _exit(1);
        }
        
        close(pipefd[0]);
        close(pipefd[1]);

        exec_command_or_die(right); 
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status;

    waitpid(left_pid, NULL, 0);

    waitpid(right_pid, &status, 0);

    report_status(status);

    return (status);
}

int execute_pipeline(pipeline_t *pipeline)
{
    if (!pipeline)
        return (-1);

    if (pipeline->cmdc == 1)
        return execute_command(&pipeline->commands[0]);

    if (pipeline->cmdc == 2)
    {
        return execute_two_command_pipeline(&pipeline->commands[0], &pipeline->commands[1]);
    }

    fprintf(stderr, "multi-stage pipeline not implemented");

    return (-1);
}


