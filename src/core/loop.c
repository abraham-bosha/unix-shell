#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "pipeline.h"
#include "debug.h"
#include "exec.h"
#include "builtin.h"
#include "expand.h"
#include "variable.h"

void shell_loop(shell_t *shell)
{
    char *line;

    while (shell->running)
    {
        line = readline(prompt_build());

        if (line == NULL)
        {
            printf("exit\n");
            break;
        }

        if (*line != '\0')
            add_history(line);

        pipeline_t *pipeline;

        pipeline = parse_line(line);

        if (!pipeline)
        {
            shell->last_exit_status = 1;
            free(line);
            continue;
        }
        
        if (expand_pipeline(shell, pipeline) < 0)
        {
            fprintf(stderr, "unix-shell: expansion failed");

            shell->last_exit_status = 1;

            pipeline_destroy(pipeline);
            
            free(line);
            
            continue;
        }

        if (pipeline_build_argv(pipeline) < 0)
        {
            shell->last_exit_status = 1;

            pipeline_destroy(pipeline);
            
            free(line);
            
            continue;
        }

#ifdef DEBUG
        debug_pipeline(pipeline);
#endif


        if (pipeline->cmdc == 1) 
        {
            if (is_assignment(&pipeline->commands[0]))
            {
                execute_assignment(shell, &pipeline->commands[0]);
                shell->last_exit_status = 0;
            }
            else if (is_builtin(&pipeline->commands[0]))
            {
                shell->last_exit_status = execute_builtin(shell, &pipeline->commands[0]);
            }
            else
            {
                shell->last_exit_status = execute_pipeline(pipeline);
            }
        
        } 
        else 
        {    
            shell->last_exit_status = execute_pipeline(pipeline);
        }

        pipeline_destroy(pipeline);

        free(line);
    }
}
