#include <stdio.h>
#include <sys/wait.h>

#include "debug.h"

static void debug_command(const command_t *cmd)
{
    size_t i;

    if (!cmd)
        return;

    DEBUG_PRINT("argc=%zu\n", cmd->argc);

    for (i = 0; i < cmd->argc; i++)
    {
        DEBUG_PRINT("argv[%zu] = \"%s\"\n", 
            i, 
            cmd->argv[i]
        );
    }

    for (i = 0; i < cmd->redirc; i++)
    {
        DEBUG_PRINT("redir[%zu] fd=%d type=%d path=\"%s\"\n", 
            i, 
            cmd->redirs[i].fd, 
            cmd->redirs[i].type, 
            cmd->redirs[i].path
        );
    }
}

void debug_pipeline(const pipeline_t *pipeline)
{
    size_t i;

    if (!pipeline)
        return;

    DEBUG_PRINT("cmdc=%zu\n", pipeline->cmdc);

    for (i = 0; i < pipeline->cmdc; i++)
    {
        DEBUG_PRINT("command[%zu]\n", i);
        
        debug_command(&pipeline->commands[i]);
    }
}

void debug_status(int status)
{
    if (WIFEXITED(status))
        DEBUG_PRINT("[EXIT code=%d]\n", WEXITSTATUS(status));
    
    else if(WIFSIGNALED(status))
        DEBUG_PRINT("[SIGNALED signal=%d]\n", WTERMSIG(status));
    
    else if(WIFSTOPPED(status))
        DEBUG_PRINT("[STOPPED signal=%d]\n", WSTOPSIG(status));

#ifdef WIFCONTINUED
    else if(WIFCONTINUED(status))
        DEBUG_PRINT("[CONTINUED]\n");
#endif
}


