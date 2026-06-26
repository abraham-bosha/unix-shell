#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser_internal.h"
#include "pipeline.h"
#include "command.h"

static size_t count_commands(const char *s)
{
    size_t count;

    count = 1;

    while (*s)
    {
        if (*s == '|')
            count++;

        s++;
    }
    
    return (count);
}

static void parse_pipeline_commands(pipeline_t *pipeline)
{
    char *cursor;
    char *segment;
    size_t idx;

    cursor = pipeline->scratch;
    idx = 0;

    while (cursor && idx < pipeline->cmdc)
    {
        segment = cursor;

        cursor = strchr(cursor, '|');

        if (cursor)
        {
            *cursor = '\0';
            cursor++;
        }

        parse_command(&pipeline->commands[idx], segment);

        idx++;
    }
}

bool validate_pipeline_syntax(const char *line, char *unexpected)
{
    bool expecting_command;

    expecting_command = true;

    while(*line)
    {
        while(*line && isspace((unsigned char)*line))
            line++;

        if (!*line)
            break;

        if (*line == '|')
        {
            if (expecting_command)
            {
                *unexpected = *line;
                return (false);
            }

            expecting_command = true;
            line++;

            continue;
        }

        expecting_command = false;

        while(*line && !isspace((unsigned char)*line) && *line != '\0')
            line++;
    }

    *unexpected = *line;
    return (!expecting_command);
}

pipeline_t *pipeline_create(const char *line)
{
    pipeline_t *pipeline;

    pipeline = calloc(1, sizeof(*pipeline));

    if (!pipeline)
        return (NULL);

    pipeline->scratch = strdup(line);

    if (!pipeline->scratch)
    {
        pipeline_destroy(pipeline);
        return (NULL);
    }

    pipeline->cmdc = count_commands(pipeline->scratch);

    pipeline->commands = calloc(pipeline->cmdc, sizeof(command_t));
    if (!pipeline->commands)
    {
        pipeline_destroy(pipeline);
        return (NULL);
    }

    parse_pipeline_commands(pipeline);
    
    return (pipeline);
}

void pipeline_destroy(pipeline_t *pipeline)
{
    size_t i;
    if (!pipeline)
        return;

    for (i = 0; i < pipeline->cmdc; i++)
        command_destroy(&pipeline->commands[i]);

    free(pipeline->commands);
    free(pipeline->scratch);

    free(pipeline);
}

