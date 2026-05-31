#include <stdio.h>

#include "parse.h"
#include "pipeline.h"
#include "redirection.h"

pipeline_t *parse_line(const char *line)
{
    char unexpected[256] = {0}; 

    if (!validate_pipeline_syntax(line, unexpected))
    {
        fprintf(stderr, "syntax error near pipe\n");
        return (NULL);
    }

    if (!validate_redirection_syntax(line, unexpected))
    {
        fprintf(stderr, "syntax error near %s", unexpected);
        return (NULL);
    }

    return pipeline_create(line);
}
