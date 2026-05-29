#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"
#include "debug.h"

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

static size_t count_args(char *segment)
{
    size_t argc;
    char *p;

    argc = 0;
    p = segment;

    while (*p)
    {
        while (*p && isspace((unsigned char)*p))
            p++;

        if (!*p)
            break;

        argc++;

        while (*p && !isspace((unsigned char)*p))
            p++;
    }

    return (argc);
}

static void parse_command(command_t *cmd, char *segment)
{
    char *p;
    size_t argc;
    size_t i;

    argc = count_args(segment);
    cmd->argc = argc;
    cmd->argv = calloc(argc + 1, sizeof(char *));

    if (!cmd->argv)
        return;

    p = segment;
    i = 0;

    while (*p)
    {
        while (*p && isspace((unsigned char)*p))
            p++;

        if (!*p)
            break;

        cmd->argv[i++] = p;

        while (*p && !isspace((unsigned char)*p))
            p++;

        if (*p)
        {
            *p = '\0';
            p++;
        }
    }
    
    cmd->argv[i] = NULL;
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

static bool validate_pipeline_syntax(const char *line)
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
                return (false);

            expecting_command = true;
            line++;

            continue;
        }

        expecting_command = false;

        while(*line && !isspace((unsigned char)*line) && *line != '0')
            line++;
    }

    return (!expecting_command);
}

pipeline_t *pipeline_create(const char *line)
{
    if (!validate_pipeline_syntax(line))
    {
        fprintf(stderr, "syntax error near pipe\n");
        return (NULL);
    }

    pipeline_t *pipeline;

    pipeline = calloc(1, sizeof(*pipeline));

    if (!pipeline)
        return (NULL);

    pipeline->source = strdup(line);
    pipeline->scratch = strdup(line);

    if (!pipeline->source || !pipeline->scratch)
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
        free(pipeline->commands[i].argv);

    free(pipeline->commands);
    free(pipeline->source);
    free(pipeline->scratch);

    free(pipeline);
}
