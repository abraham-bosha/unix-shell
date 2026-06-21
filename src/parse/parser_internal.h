#ifndef PARSER_INTERNAL_H
#define PARSER_INTERANL_H

#include "command.h"
#include "pipeline.h"
#include "redirection.h"
#include "argument.h"

char *parse_word(char **cursor, quote_type_t *quote);

void parse_command(command_t *cmd, char *segment);

int parse_redirection(command_t *cmd, char **cursor);

bool validate_pipeline_syntax(
    const char *line,
    char *unexpected
);

bool validate_redirection_syntax(
    const char *line,
    char *unexpected
);

#endif
