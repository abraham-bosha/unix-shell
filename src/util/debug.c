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
    }
}


