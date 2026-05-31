#include <stdio.h>

#include "debug.h"

void pipeline_dump(const pipeline_t *pipeline)
{
    size_t i;
    size_t j;

    if (!pipeline)
        return;

    printf("cmdc=%zu\n", pipeline->cmdc);

    for (i = 0; i < pipeline->cmdc; i++)
    {
        printf("command[%zu]\n", i);

        for (j = 0; j < pipeline->commands[i].argc; j++)
            printf("argv[%zu] = \"%s\"\n", j, pipeline->commands[i].argv[j]);
        
        printf("\n");
        printf("redirs[%zu]\n", i);

        for (j = 0; j < pipeline->commands[i].redirc; j++)
        {
            printf("path = \"%s\"\n", pipeline->commands[i].redirs[j].path);
            printf("fd = %d\n", pipeline->commands[i].redirs[j].fd);
            printf("type = %d\n", pipeline->commands[i].redirs[j].type);
        }
    }
}


