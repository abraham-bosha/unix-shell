#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "exec.h"
#include "command.h"
#include "debug.h"

static int execute_multi_command_pipeline(pipeline_t *pipeline) 
{
    pid_t *pids;
    int prev_read;
    size_t i;

    prev_read = -1;

    pids = calloc(pipeline->cmdc, sizeof(*pids));

    if (!pids)
        return (-1);

    for (i = 0; i < pipeline->cmdc; i++)
    {
        bool last;

        last = (i == pipeline->cmdc - 1);
        
        int pipefd[2];

        if (!last)
        {
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                _exit(1);
            }
        }

        pids[i] = fork();

        if (pids[i] < 0)
        {
            perror("fork");
            _exit(1);
        }
        
        if (pids[i] == 0) {
            
            if (prev_read != -1) {
                
                dup2(prev_read, STDIN_FILENO);
                
                close(prev_read);
            }
            
            if (!last) {
                
                dup2(pipefd[1], STDOUT_FILENO);

                close(pipefd[0]);
                close(pipefd[1]);
            }

            exec_command_or_die(&pipeline->commands[i]);
        }

        if (prev_read != -1)
            close(prev_read);

        if (!last)
        {
            prev_read = pipefd[0];
            close(pipefd[1]);
        }
    }

    int last_status = 0;

    for (size_t i = 0; i < pipeline->cmdc; i++)
    {
        waitpid(pids[i], &last_status, 0);
#ifdef DEBUG
        DEBUG_PRINT("child[%zu] pid=%d\n", i, pids[i]);
        debug_status(last_status);
#endif
    }

    free(pids);

    return decode_exit_status(last_status);
}

int execute_pipeline(pipeline_t *pipeline)
{
    if (!pipeline)
        return (-1);

    return execute_multi_command_pipeline(pipeline);
}


