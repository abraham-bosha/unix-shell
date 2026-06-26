#ifndef VAR_H
#define VAR_H

#include "command.h"
#include <stddef.h>

typedef struct shell shell_t;

typedef struct variable
{
    char *name;
    char *value;
} variable_t;

bool is_assignment(const command_t *cmd);

void execute_assignment(
    shell_t *shell, 
    command_t *cmd);

int shell_set_variable(
    shell_t *shell,
    const char *name,
    const char *value);

const char *shell_get_variable(
    shell_t *shell,
    const char *name);

int shell_unset_variable(
    shell_t *shell,
    const char *name);

void shell_destroy(shell_t *shell);

#endif
