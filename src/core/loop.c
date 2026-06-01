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

void shell_loop(void)
{
    char *line;
    
    while (true)
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
            continue;
        
#ifdef DEBUG
        pipeline_dump(pipeline);
#endif

        if (pipeline->cmdc == 1 && is_builtin(&pipeline->commands[0]))

            shell->last_status = execute_builtin(&pipeline->commands[0]);
        
        else
            
            shell->last_status = execute_pipeline(pipeline);

        pipeline_destroy(pipeline);

        free(line);
    }
}
