#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "command.h"
#include "prompt.h"
#include "parse.h"
#include "pipeline.h"
#include "debug.h"
#include "exec.h"

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

        if (pipeline)
        {
            shell->last_status = execute_pipeline(pipeline);
            pipeline_destroy(pipeline);
        }

        free(line);
    }
}
