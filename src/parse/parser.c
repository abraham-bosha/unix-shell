#include <stdio.h>

#include "parser_internal.h"
#include "parse.h"
#include "pipeline.h"
#include "redirection.h"

pipeline_t *parse_line(const char *line)
{
    char unexpected = '\0'; 

    if (!validate_pipeline_syntax(line, &unexpected))
    {
        fprintf(stderr, "syntax error near %c\n", unexpected);
        return NULL;
    }

    if (!validate_redirection_syntax(line, &unexpected))
    {
        fprintf(stderr, "syntax error near %c\n", unexpected);
        return NULL;
    }

    return pipeline_create(line);
}
